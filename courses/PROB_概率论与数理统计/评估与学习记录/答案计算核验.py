"""Portable, offline calculation checks for the independently authored exercises.

Uses only Python's standard library. Finite numerical checks are not proofs of
every formula and do not evaluate a model, a textbook, or a student's mastery.
"""
from __future__ import annotations

import itertools
import json
import math
from fractions import Fraction as F
from pathlib import Path
from statistics import NormalDist

records = []


def close(a, b, tol):
    if isinstance(b, dict):
        return isinstance(a, dict) and a.keys() == b.keys() and all(close(a[k], b[k], tol) for k in b)
    if isinstance(b, (list, tuple)):
        return len(a) == len(b) and all(close(x, y, tol) for x, y in zip(a, b))
    if isinstance(b, bool):
        return a is b
    if isinstance(b, (int, float, F)):
        return math.isfinite(float(a)) and abs(float(a) - float(b)) <= tol
    return a == b


def serialize(v):
    if isinstance(v, F):
        return {'fraction': str(v), 'decimal': float(v)}
    if isinstance(v, dict):
        return {str(k): serialize(x) for k, x in v.items()}
    if isinstance(v, (list, tuple)):
        return [serialize(x) for x in v]
    return v


def check(ch, n, method, actual, expected, tol=1e-8, kind='EX'):
    ident = f'PROB-CH{ch:02d}-EX-GEN-{n:03d}' if kind == 'EX' else f'PROB-CH{ch:02d}-L{n:02d}'
    records.append({'id': ident, 'method': method, 'actual': serialize(actual), 'expected': serialize(expected),
                    'tolerance': tol, 'passed': close(actual, expected, tol), 'kind': kind})


def integral(f, a, b, n=4000):
    assert n % 2 == 0
    h = (b-a)/n
    return h/3 * (f(a) + f(b) + sum((4 if k % 2 else 2)*f(a+k*h) for k in range(1,n)))


def weighted_bits(n, p):
    for bits in itertools.product([0,1], repeat=n):
        weight = math.prod(p if b else 1-p for b in bits)
        yield bits, weight


def run():
    bits3 = list(itertools.product([0,1], repeat=3))
    check(1,1,'枚举8个等可能有序序列',F(sum(sum(x)==2 for x in bits3),8),F(3,8))
    a,b={2,4,6,8},{6,7,8}
    check(1,2,'集合并集枚举',F(len(a|b),8),F(5,8))
    pa,pb,pab=F(11,20),F(2,5),F(1,5)
    check(1,3,'精确分数计算并集、差集和补事件',[pa+pb-pab,pa-pab,1-pa-pb+pab],[F(3,4),F(7,20),F(1,4)])
    balls=list(itertools.combinations(range(8),3))
    check(1,4,'枚举56个球组，前5个球为白球',F(sum(sum(i<5 for i in c)==2 for c in balls),len(balls)),F(15,28))
    jobs=list(itertools.permutations(range(8),3))
    check(1,5,'枚举不同岗位的所有有序分配',[len(jobs),F(sum(0 in p for p in jobs),len(jobs))],[336,F(3,8)])
    check(1,6,'两个方向的条件概率',[F(3,10)/F(1,2),F(3,10)/F(2,5)],[F(3,5),F(3,4)])
    draws=list(itertools.permutations(range(6),2))
    check(1,7,'枚举30个无放回有序抽取，前2个为红球',[F(sum(x<2 and y<2 for x,y in draws),30),F(sum(y<2 for x,y in draws),30)],[F(1,15),F(1,3)])
    pd=F(3,10)*F(2,100)+F(7,10)*F(5,100)
    check(1,8,'供货来源加权',pd,F(41,1000))
    check(1,9,'不合格产品的来源归一化',F(7,10)*F(5,100)/pd,F(35,41))
    check(1,10,'枚举8种部件状态加权',sum(w for bs,w in weighted_bits(3,F(9,10)) if sum(bs)>=2),F(243,250))
    w={(x,y):(F(2,5) if x else F(3,5))*(F(3,10) if y else F(7,10)) for x,y in itertools.product([0,1], repeat=2)}
    check(1,11,'独立二事件的完整联合表',[sum(p for (x,y),p in w.items() if x or y),w[0,0]],[F(29,50),F(21,50)])
    check(1,12,'比较互斥交概率与乘积',[F(0)==F(1,5)*F(3,10),F(1,5)*F(3,10)],[False,F(3,50)])
    states=list(itertools.product([0,1],repeat=2))
    es=[lambda x:x[0]==1,lambda x:x[1]==1,lambda x:x[0]==x[1]]
    pairs=[F(sum(es[i](s) and es[j](s) for s in states),4) for i,j in [(0,1),(0,2),(1,2)]]
    check(1,13,'枚举三事件两两交与三重交',[pairs,F(sum(all(e(s) for e in es) for s in states),4),F(1,2)**3],[[F(1,4)]*3,F(1,4),F(1,8)])
    likelihood=[math.comb(120,72)*p**72*(1-p)**48 for p in [.5,.6]]
    check(1,14,'计算频率，并给出两个不同p下均可出现的有限样本',[F(72,120),all(v>0 for v in likelihood)],[F(3,5),True])
    check(1,15,'枚举32种失败状态',sum(w for bs,w in weighted_bits(5,F(1,10)) if any(bs)),F(40951,100000))

    check(2,1,'枚举三次投掷并按正面数聚合',[F(sum(sum(s)==k for s in bits3),8) for k in range(4)],[F(1,8),F(3,8),F(3,8),F(1,8)])
    c=F(1,sum([1,2,3]))
    check(2,2,'概率表归一化',[c,2*c+3*c],[F(1,6),F(5,6)])
    wb=list(weighted_bits(6,F(1,5)))
    check(2,3,'枚举64种伯努利状态',[sum(w for bs,w in wb if sum(bs)==2),sum(w for bs,w in wb if sum(bs)>=1)],[F(768,3125),F(11529,15625)])
    check(2,4,'前三次指定路径与四次全失败',[F(3,4)**2*F(1,4),F(3,4)**4],[F(9,64),F(81,256)])
    poisson=lambda k:math.exp(-2)*2**k/math.factorial(k)
    check(2,5,'泊松质量逐项求和',[poisson(0),sum(poisson(k) for k in range(3))],[math.exp(-2),5*math.exp(-2)])
    masses={0:F(1,4),1:F(1,2),2:F(1,4)}
    check(2,6,'从CDF跳跃对应的质量表按端点求和',[sum(v for x,v in masses.items() if 0<x<=1),masses[1],sum(v for x,v in masses.items() if x<1)],[F(1,2),F(1,2),F(1,4)])
    check(2,7,'构造负的区间概率',.6-.7,-.1)
    check(2,8,'密度数值积分及区间积分',[integral(lambda x:x/2,0,2),integral(lambda x:x/2,1,1.5)],[1,F(5,16)])
    check(2,9,'均匀区间长度及CDF反解',[integral(lambda x:.25,0,2),-1+.75*4],[.5,2])
    check(2,10,'指数生存函数与条件比值',[math.exp(-2),math.exp(-6)/math.exp(-4)],[.1353352832366127,.1353352832366127])
    normal=NormalDist(10,2)
    check(2,11,'标准库正态CDF与反函数',[normal.cdf(12)-normal.cdf(8),normal.inv_cdf(.975)],[.6826894921370859,13.919927969080108])
    grid=[-1+(i+.5)*2/10000 for i in range(10000)]
    probs=[sum(x*x<=y for x in grid)/len(grid) for y in [.04,.25,.81]]
    derivative=(math.sqrt(.25+1e-6)-math.sqrt(.25-1e-6))/(2e-6)
    check(2,12,'确定性均匀网格验证平方CDF三点，并差分检查一处密度',[probs,derivative],[[.2,.5,.9],1],tol=1e-6)
    density=lambda y:.5*math.exp((y-1)/2)
    check(2,13,'递减变换密度积分；截断尾部误差小于2e-9',[integral(density,-40,1,8000),integral(density,-40,-1,8000)],[1,math.exp(-1)],tol=1e-7)
    transformed={0:F(0),1:F(0)}
    for x,p in [(-1,F(1,5)),(0,F(1,2)),(1,F(3,10))]:
        transformed[x*x]+=p
    check(2,14,'按函数值聚合离散概率',transformed,{0:F(1,2),1:F(1,2)})
    check(2,15,'点质量与连续部分分别计算',[.3+integral(lambda x:.35,0,2),.3,integral(lambda x:.35,0,1)],[1,.3,.35])

    joint={(0,0):F(1,10),(0,1):F(1,5),(1,0):F(3,10),(1,1):F(2,5)}
    mx=[sum(p for (x,y),p in joint.items() if x==i) for i in [0,1]]
    my=[sum(p for (x,y),p in joint.items() if y==i) for i in [0,1]]
    check(3,1,'联合表逐行逐列汇总',[mx,my,sum(p for (x,y),p in joint.items() if x+y>=1)],[[F(3,10),F(7,10)],[F(2,5),F(3,5)],F(9,10)])
    check(3,2,'逐项检验独立乘积',all(p==mx[x]*my[y] for (x,y),p in joint.items()),False)
    check(3,3,'联合表条件化',[joint[1,0]/my[0],joint[1,1]/mx[1]],[F(3,4),F(4,7)])
    marginal_x=lambda x:integral(lambda y:2,x,1)
    marginal_y=lambda y:integral(lambda x:2,0,y)
    check(3,4,'按三角区域数值积分及边缘点值',[integral(lambda y:2*y,0,1),marginal_x(.25),marginal_y(.25)],[1,1.5,.5])
    conds=[[integral(lambda x:1/y,0,y),integral(lambda x:1/y,0,y/2)] for y in [.2,.5,.9]]
    check(3,5,'三个正条件值下的归一化和半区间概率',conds,[[1,.5]]*3)
    check(3,6,'支持域与事件域交集的截面面积积分',integral(lambda x:2*(1-2*x),0,.5),.5)
    check(3,7,'边缘积分、乘积检验与矩形概率',[integral(lambda y:4*.3*y,0,1),integral(lambda x:4*x*.4,0,1),4*.3*.4,(integral(lambda x:2*x,0,.5))**2],[.6,.8,.48,F(1,16)])
    check(3,8,'矛盾事件交集为零，两个边缘事件均为正',[0,integral(lambda x:2*(1-x),.5,1)*integral(lambda y:2*y,0,.5)],[0,F(1,16)])
    conv=lambda z:max(0,min(1,z)-max(0,z-1))
    check(3,9,'卷积有效区间与三角区域面积',[[conv(z) for z in [.25,.75,1.25,1.75]],integral(lambda x:.5-x,0,.5)],[[.25,.75,.75,.25],F(1,8)])
    check(3,10,'直接卷积和尾部数值积分',[integral(lambda x:math.exp(-x)*math.exp(-(2-x)),0,2),integral(lambda z:z*math.exp(-z),2,40,8000)],[2*math.exp(-2),3*math.exp(-2)],tol=1e-8)
    grid2=[(i+.5)/200 for i in range(200)]
    check(3,11,'单位正方形确定性网格计数',[sum(max(x,y)<=.8 for x in grid2 for y in grid2)/40000,sum(min(x,y)>.2 for x in grid2 for y in grid2)/40000],[.64,.64])
    pm=[F(0),F(0),F(0)]
    for x,y in itertools.product([0,1],repeat=2):
        pm[x+y]+=(F(3,10) if x else F(7,10))*(F(2,5) if y else F(3,5))
    check(3,12,'枚举不同成功率的二点变量',pm,[F(21,50),F(23,50),F(3,25)])
    nx,ny,nz=NormalDist(1,2),NormalDist(-2,3),NormalDist(-1,math.sqrt(13))
    convcdf=[integral(lambda x:nx.pdf(x)*ny.cdf(z-x),-30,30,6000) for z in [-1,2]]
    check(3,13,'数值卷积CDF与目标正态CDF的两个点比较',convcdf,[.5,nz.cdf(2)],tol=1e-8)
    ratio=[integral(lambda y:min(1,z*y),0,1) for z in [.5,1,2]]
    check(3,14,'在单位正方形上直接积分商事件面积',ratio,[.25,.5,.75])
    z=.25
    product_cdf=z+integral(lambda x:z/x,z,1)
    check(3,15,'积事件直接分区积分',product_cdf,(1+math.log(4))/4)

    check(1,1,'讲义例题：枚举球对',F(3*2,math.comb(5,2)),F(3,5),kind='L')
    check(1,2,'讲义例题：湿路面贝叶斯归一化',F(1,5)*F(9,10)/(F(1,5)*F(9,10)+F(4,5)*F(1,10)),F(9,13),kind='L')
    check(2,1,'讲义例题：正态CDF',NormalDist(20,3).cdf(23)-NormalDist(20,3).cdf(17),.6826894921370859,kind='L')
    check(2,2,'讲义例题：U(0,2)平方在y=1处的CDF',F(1,2),.5,kind='L')
    check(3,1,'讲义例题：联合表边缘与条件',[[.2+.3,.1+.4],[.2+.1,.3+.4],.4/(.3+.4)],[[.5,.5],[.3,.7],F(4,7)],kind='L')
    check(3,2,'讲义例题：不等长均匀分布卷积的三段面积',[integral(lambda z:z/2,0,1),integral(lambda z:.5,1,2),integral(lambda z:(3-z)/2,2,3)],[.25,.5,.25],kind='L')


if __name__ == '__main__':
    run()
    out=Path(__file__).resolve().parent
    exercises=[r for r in records if r['kind']=='EX']
    assert len(exercises)==45 and len({r['id'] for r in exercises})==45
    result={'date':'2026-10-25','python_standard_library_only':True,'exercise_checks':45,'lecture_example_checks':6,'passed':sum(r['passed'] for r in records),'total':len(records),'checks':records}
    (out/'答案计算核验.json').write_text(json.dumps(result,ensure_ascii=False,indent=2)+'\n',encoding='utf-8')
    lines=['# 答案计算核验记录','','日期：2026-10-25。执行环境：Python标准库，无网络、无模型调用。',f'原创练习核验45项，讲义例题核验6项，共{len(records)}项，其中{result["passed"]}项通过。',
           '', '## 检查范围与局限', '', '核验对象是本包独立编写的参考解，不是教材原书答案。离散题以完整有限枚举或精确分数计算核验；连续题以数值积分、分布函数和固定网格检查部分结论。概念题通过有限反例或必要条件检查。',
           '这些检查不证明所有一般公式、所有连续参数或整份文字解析均无误。完整推导保留在参考解中，仍需独立互测。网格检查只覆盖所列阈值，数值积分按记录容差比较。没有执行DeepTutor检索或真实模型问答。',
           '', '| 题目ID | 方法与范围 | 结果 |', '|---|---|---|']
    for r in records:
        lines.append(f'| {r["id"]} | {r["method"]} | {"通过" if r["passed"] else "失败"} |')
    lines+=['', '详细实际值、预期值、容差和每项状态见同目录答案计算核验.json。重跑方法：在本目录执行 `python 答案计算核验.py`。']
    (out/'答案计算核验.md').write_text('\n'.join(lines)+'\n',encoding='utf-8')
    print(json.dumps({'exercise_checks':45,'lecture_checks':6,'passed':result['passed'],'total':result['total']}))
    raise SystemExit(0 if all(r['passed'] for r in records) else 1)
