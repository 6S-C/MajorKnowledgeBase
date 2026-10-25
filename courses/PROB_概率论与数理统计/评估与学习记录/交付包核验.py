"""Read-only verifier for the standard course delivery package. No network."""
from __future__ import annotations

import argparse
import csv
import hashlib
import json
import re
import sys
from pathlib import Path


def main(root):
    results=[]
    def check(name,value):
        results.append({'check':name,'passed':bool(value)})
    def load(path):
        with path.open(encoding='utf-8-sig',newline='') as f:
            return list(csv.DictReader(f))
    def sha(path):
        return hashlib.sha256(path.read_bytes()).hexdigest()
    def local(base,relative):
        p=(base/relative).resolve()
        assert p.is_relative_to(root), 'path escapes package: '+relative
        assert p.is_file(), 'missing file: '+relative
        return p
    root=root.resolve()
    course=root/'课程资料'
    for directory in ['课程资料','评估与学习记录','源码分析']:
        check(directory+'目录存在',(root/directory).is_dir())
    for name in ['交付说明.md','管理员接收与重建说明.md','提交前检查表.md','课程分工表.csv','文件哈希清单.csv']:
        check(name+'存在',(root/name).is_file())
    check('无重复的仅入库Markdown副本',not (root/'仅入库Markdown').exists())
    hashes=load(root/'文件哈希清单.csv')
    for row in hashes:
        p=local(root,row['相对路径'])
        check(row['相对路径']+'全包哈希',sha(p)==row['SHA256'] and p.stat().st_size==int(row['字节数']))
    actual={p.relative_to(root).as_posix() for p in root.rglob('*') if p.is_file() and p.name!='文件哈希清单.csv'}
    check('哈希清单覆盖全部交付文件',actual=={r['相对路径'] for r in hashes})
    materials=load(course/'资料清单.csv')
    docs={r['文档ID']:r for r in materials}
    check('资料文档ID无重复',len(docs)==len(materials))
    for row in materials:
        src=local(course,row['原件相对路径'])
        target=local(course,row['整理稿相对路径'])
        check(row['文档ID']+'原稿与整理稿哈希',sha(src)==row['原件SHA256'] and sha(target)==row['整理稿SHA256'])
    items=load(course/'题目索引.csv')
    check('45道主问题且ID唯一',len(items)==len({r['题目ID'] for r in items})==45)
    check('65个显式小问且变式为零',sum(int(r['小问数']) for r in items)==65 and sum(int(r['变式数']) for r in items)==0)
    for ch in [1,2,3]:
        cdir=next(course.glob(f'第{ch}章_*'))
        for sub in ['00_原始资料','01_课件','02_题目','03_答案与解析','04_入库资料','05_提取与核对']:
            check(cdir.name+'/'+sub+'目录存在',(cdir/sub).is_dir())
        subset=[r for r in items if r['章节ID']==f'CH{ch:02d}']
        check(f'CH{ch:02d}题号连续且共15道',[r['题目ID'] for r in subset]==[f'PROB-CH{ch:02d}-EX-GEN-{i:03d}' for i in range(1,16)])
    for row in items:
        doc=docs[row['文档ID']]
        source=json.loads(local(course,doc['原件相对路径']).read_text(encoding='utf-8'))
        q=next(q for q in source if q['id']==row['题目ID'])
        answer=local(course,row['答案文件']).read_text(encoding='utf-8')
        body=answer.split('## '+row['题目ID']+' ',1)[1].split('\n## ',1)[0]
        check(row['题目ID']+'来源、答案与核对字段',q['answer'] in body and all(x in body for x in ['答案状态：','参考答案与解析：','依据：','校正说明：']))
        locator,fragment=row['原件定位'].split('#',1)
        check(row['题目ID']+'原稿定位',local(course,locator)==local(course,doc['原件相对路径']) and fragment==q['id'])
    imports=load(course/'导入清单.csv')
    check('12项正式入库文件且无重复',len(imports)==len({r['入库文件相对路径'] for r in imports})==12)
    for row in imports:
        p=local(course,row['入库文件相对路径'])
        check(p.name+'入库路径与哈希',p.parent.name=='04_入库资料' and sha(p)==row['文件SHA256'] and row['资料包版本']=='v1.0.2')
    resource=load(course/'网络资源清单.csv')
    check('15项网络资源仅作来源登记',len(resource)==15 and all(r['是否正文已入库']=='否' for r in resource))
    calc=json.loads((root/'评估与学习记录'/'答案计算核验.json').read_text(encoding='utf-8'))
    check('计算核验51项记录存在且通过',calc['total']==calc['passed']==51)
    prohibited=[]
    for p in root.rglob('*'):
        if not p.is_file():
            continue
        name=p.name.lower()
        if name.startswith('.env') or p.suffix.lower() in ['.db','.sqlite','.sqlite3','.key','.pem','.log']:
            prohibited.append(str(p.relative_to(root)))
    check('无私有配置与运行文件',not prohibited)
    check('无点名册PDF',not any(p.name in ['1.pdf','2.pdf','3.pdf','4.pdf'] for p in root.rglob('*')))
    register=load(root/'课程分工表.csv')
    check('负责人和范围登记',register[0]['负责人']=='朱家鹏' and '部分交付' in register[0]['状态'])
    return {'version':'v1.0.2','checks':len(results),'passed':sum(r['passed'] for r in results),
            'all_passed':all(r['passed'] for r in results),'results':results,
            'not_executed':['模型配置','DeepTutor导入与检索','教材逐页比对','独立互测']}


if __name__=='__main__':
    sys.stdout.reconfigure(encoding='utf-8')
    parser=argparse.ArgumentParser()
    parser.add_argument('--root',type=Path,default=Path(__file__).resolve().parents[1])
    args=parser.parse_args()
    result=main(args.root)
    print(json.dumps(result,ensure_ascii=False,indent=2))
    raise SystemExit(0 if result['all_passed'] else 1)
