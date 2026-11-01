# W2｜第 3 章《用户记忆和知识库》实验记录

> 公开版说明：本文件由本地正式实验记录整理入库。原始运行日志、API 回执、环境文件和缓存未提交到公开仓库；文中本地路径用于说明原始证据位置，不代表仓库内可直接访问。

## 1. 实验 3-1 / 3-2：用户记忆

### 1.1 实验目的与方法

实验比较 `notes`、`enhanced_notes`、`json_cards` 和 `advanced_json_cards` 四种记忆表示。Demo 固定使用三条事实输入：姓名与工作、编程与 IDE 偏好、当前移动 App 项目；随后开启新会话询问模型记住了什么。

最初的 demo 将用户写死为 `demo_user`，导致不同模式共用持久化文件。该问题后来修复为使用命令行 `--user`，并为重跑设置独立的记忆目录、对话目录和用户 ID。原始共用用户的数据不用于公平横向比较。

重跑命令形式如下：

~~~powershell
python main.py --mode demo --user rerun_notes `
  --memory-mode notes --provider dashscope

python main.py --mode demo --user rerun_enhanced_notes `
  --memory-mode enhanced_notes --provider dashscope

python main.py --mode demo --user rerun_json_cards `
  --memory-mode json_cards --provider dashscope

python main.py --mode demo --user rerun_advanced_json_cards `
  --memory-mode advanced_json_cards --provider dashscope
~~~

### 1.2 实际结果

| 记忆格式 | 独立运行结果 | 写入行为 | 跨会话召回 | 原始证据 | 判定 |
| --- | --- | --- | --- | --- | --- |
| notes | 落盘 6 条事实记忆 | 姓名、公司与职位、Python、VS Code、深色主题、移动 App 项目分别写成短 note | 最终状态可读取；后续一次流式请求超时 | `W2-第3章-用户记忆重跑\01-notes.log`；`data\memories\rerun_notes_memory.json` | 阶段性成功，记忆文件有效，但整轮不是无错误运行 |
| enhanced_notes | 一次早期独立尝试落盘 4 条扩展 note；最新重跑为 0 条 | 早期结果把事实扩写成带情境的长 note；最新重跑未生成记忆文件 | 最新重跑失败，只留下历史文件 | `W2-第3章-用户记忆重跑\02-enhanced-notes.log`；早期部分产物 `chapter3\user-memory\data\memories\exp_enhanced_notes_memory.json` | 部分成功，不满足公平对比 |
| json_cards | 最新独立尝试为 0 条 | 未生成 `rerun_json_cards_memory.json` | 只形成对话历史，后台提取失败 | `W2-第3章-runs\3-2-memory-json-cards-isolated.log` | 失败 |
| advanced_json_cards | 最新独立尝试为 0 条 | 未生成 `rerun_advanced_json_cards_memory.json` | 只形成对话历史，后台提取和最终回复失败 | `W2-第3章-runs\3-2-memory-advanced-json-cards-isolated.log` | 失败 |

Notes 模式实际保存的 6 条信息均能追溯到输入事实：

1. 用户名为 Alice；
2. 在 TechCorp 担任产品经理；
3. 偏好用 Python 编写脚本；
4. 使用 VS Code；
5. 偏好深色主题；
6. 正在 TechCorp 开发新的移动 App。

Enhanced Notes 的早期部分产物体现了“增强”的同时也暴露了风险。例如原输入只说明用户是产品经理，输出却扩写为负责 PRD、用户故事、验收标准和 Sprint 规划；原输入只说明正在做移动 App，输出又推断用户正在领导项目。它们是合理猜测，但不是对话明确提供的事实，正式长期记忆不应把这类推断当成已证实信息。

### 1.3 失败原因与影响

失败日志的共同特征是：部分请求先返回 `HTTP 200 OK`，随后在流式回复或后台记忆提取时出现 `Request timed out` 或 `Connection error`，最终记录 `Memory update task completed: False`。日志中没有 `401`、`403` 或 `429`，因此现有证据不支持“密钥错误、无权限或明确限流”的判断。

用户记忆 demo 至少包含三轮对话请求和一次独立的后台记忆抽取请求。对话历史可在前几轮成功保存，但只要后面的抽取请求失败，就会出现“有历史文件、没有记忆 JSON、Summary 为 0”的现象。早期同时启动多个模式增加了并发压力；改为顺序执行后仍出现连接错误，说明并发不是唯一原因，DashScope 流式连接稳定性和客户端默认超时/重试策略仍是主要限制。

失败的影响包括：

- 不能用当前数据比较四种表示的召回率或优劣；
- `0 added` 在本次实验中表示抽取调用失败，不能解释为“该模式认为没有值得保存的信息”；
- 只有 Notes 的 6 条落盘记忆可作为有效写入样例；
- Enhanced Notes 的 4 条早期结果只能用于分析扩写与误存风险，不能与最新重跑直接比较。

## 2. 实验 3-4：Annoy 与 HNSW 近似最近邻对比

### 2.1 实验设置

本实验使用脚本生成的合成向量，不加载真实语义嵌入模型。固定 5,000 个基础向量、100 个查询、128 维、`top-k=10`、随机种子 42，比较标准参数和高召回参数。

~~~powershell
python cli.py --compare-ann --backend both --ann-base 5000 `
  --ann-queries 100 --ann-dim 128 --annoy-n-trees 10 `
  --hnsw-M 16 --hnsw-ef-search 20 --hnsw-ef-construction 100 `
  --top-k 10 --seed 42 -o 3-4-ann-standard.json

python cli.py --compare-ann --backend both --ann-base 5000 `
  --ann-queries 100 --ann-dim 128 --annoy-n-trees 30 `
  --hnsw-M 32 --hnsw-ef-search 100 --hnsw-ef-construction 200 `
  --top-k 10 --seed 42 -o 3-4-ann-high-recall.json
~~~

### 2.2 结果

| 配置 | 索引 | Recall@10 | 建索引时间 | 平均查询时间 |
| --- | --- | ---: | ---: | ---: |
| 标准 | Annoy，`n_trees=10` | 0.105 | 0.0289 s | 0.0314 ms |
| 标准 | HNSW，`M=16, ef_search=20, ef_construction=100` | 0.442 | 0.3777 s | 0.0402 ms |
| 高召回 | Annoy，`n_trees=30` | 0.250 | 0.0326 s | 0.0600 ms |
| 高召回 | HNSW，`M=32, ef_search=100, ef_construction=200` | 0.968 | 0.6390 s | 0.1201 ms |

提高搜索资源后，两种索引的召回都提高，但查询时间也增加。HNSW 在本次合成数据上由 0.442 提升至 0.968，代价是建索引时间由约 0.378 秒增至 0.639 秒，平均查询时间约增至原来的 3 倍。该结果说明 ANN 参数存在明确的召回—延迟折中，但不能直接外推为真实中文知识库的语义检索质量。

原始证据：`3-4-ann-standard.json`、`3-4-ann-high-recall.json` 及同名日志。

## 3. 实验 3-5：BM25 稀疏检索

### 3.1 实验设置

使用仓库内置小语料和标注集，`top-k=5`，运行 BM25 评测与 `model distillation` 的逐词解释。

### 3.2 结果

| 查询 | Recall@5 | Precision@5 | RR | 观察 |
| --- | ---: | ---: | ---: | --- |
| `model distillation` | 1.0 | 1.0 | 1.0 | 命中 `doc_3`、`doc_4` |
| `HTTP 404 error` | 1.0 | 0.5 | 1.0 | 召回正确文档，但有额外返回 |
| `XK9-2B4-7Q1` | 1.0 | 1.0 | 1.0 | 精确编号检索有效 |
| `BM25 ranking function` | 1.0 | 1.0 | 1.0 | 专有术语检索有效 |
| `cat` | 0.0 | 0.0 | 0.0 | 未命中，体现词汇不匹配弱点 |
| 宏平均 | 0.8 | 0.7 | 0.8 | Miss rate@5 为 0.2 |

解释结果中，`Model Distillation` 得分 3.1216，`Knowledge Distillation` 得分 2.2197，两篇文档都明确匹配 `model` 与 `distillation`。BM25 对编号、错误码和精确术语表现稳定，但无法自行理解没有词面重合的同义表达；`cat` 的零命中是本次数据中的直接反例。

原始证据：`3-5-bm25-evaluation.json`、`3-5-bm25-explanation.json` 及同名日志。

## 4. 实验 3-8：Non-Agentic 与 Agentic RAG 离线检索对比

### 4.1 实验设置

本实验运行 `compare_offline.py`，使用 `evaluation\offline_qa.json`、`laws` 语料与 `top-k=5`。这是离线检索对照，不调用 LLM，评价的是问题分解和多次检索能否覆盖标注法条，不评价最终自然语言回答质量。

数据集 SHA-256：`0B6C0B69A11372C95AE8C420B65A56DF985EE693B74D5B6D77FBF818E21FE0E1`。

### 4.2 结果

| 难度 | 问题数 | Non-Agentic Recall | Agentic Recall | 平均检索次数（Non-Agentic / Agentic） |
| --- | ---: | ---: | ---: | ---: |
| Easy | 3 | 1.000 | 1.000 | 1.0 / 1.0 |
| Hard | 4 | 0.083 | 1.000 | 1.0 / 1.5 |
| Overall | 7 | 0.476 | 1.000 | 1.0 / 1.286 |

三个简单问题中，两种方法都一次命中目标法条。三个单法条困难问题中，直接检索均未覆盖标注法条，而 Agentic 变体通过查询改写覆盖目标。最复杂的问题“醉酒过失致人重伤且有盗窃前科，应如何量刑？”需要三个法条：直接检索只覆盖 `第二百三十五条`，Recall 为 1/3；Agentic 进行 3 次检索，覆盖 `第二百三十五条`、`第一百三十三条之一` 和 `第六十五条`，Recall 为 1.0。

本结果支持的结论是：在这 7 道固定离线题中，问题分解提高了标注法条覆盖率，尤其适合包含多个法律要件的复合问题。它不证明 Agentic RAG 在所有知识库上都更好，也没有测量 LLM 回答正确率、引用真实性或端到端延迟。

原始证据：`3-8-agentic-rag-offline.json` 与 `3-8-agentic-rag-offline.log`。

## 5. 个人 Wiki 最小混合 RAG

### 5.1 实验设置与索引结果

个人 Wiki 语料路径为 `D:\Agent\papernote`。本实验启动 BGE-M3 Dense 服务（HNSW，1024 维）、BM25 Sparse 服务和带 BGE-Reranker-v2-M3 的混合检索流水线。切分参数为 `chunk-size=2048`、`max-chunk-size=1024`、`overlap=200`。

初次索引暴露了两个实际问题。第一，三个本地端口请求受系统代理影响而返回 502，给服务进程设置 `NO_PROXY=localhost,127.0.0.1` 后恢复。第二，`chunking.py` 给同一文件的所有 chunk 复用了父文档 ID，导致 Dense 和本地存储反复覆盖同一条，而 BM25 保留重复条目。将索引请求中的 ID 改为唯一的 `chunk_id` 后清空无效索引并重跑。

最终成功索引 5 个 Markdown，0 个错误，共 64 个 chunk：

| 文件 | chunk 数 |
| --- | ---: |
| `BCI_IV_2a_DeepConvNet_ShallowConvNet_复现总结_结构化注释增强版.md` | 38 |
| `DBConformer笔记.md` | 6 |
| `EEGNet_Transformer_学习收获.md` | 4 |
| `EEGNet_评估指标笔记.md` | 3 |
| `EEGNet总结.md` | 13 |

索引完成后，Dense、Sparse 和 Pipeline 的文档计数均为 64，证明三处索引一致。原始证据为 `wiki-indexing-final.log`、`wiki-dense-server.log`、`wiki-sparse-server-clean.err.log` 和 `wiki-retrieval-pipeline-clean.err.log`。

### 5.2 三道真实问题

固定问题为：

1. EEGNet 常用的评估指标有哪些，各自反映了什么性能？
2. DeepConvNet 和 ShallowConvNet 在网络结构与特征提取机制上有什么区别？
3. EEGNet 与 Transformer 结合时，Transformer 主要解决什么问题？

两种模式均使用 DashScope `qwen3.8-flash`、混合检索和 `top-k=5`。Non-Agentic 对每题直接检索一次；Agentic 允许模型规划、改写查询并多次检索。

### 5.3 实际回答对比

| 问题 | Non-Agentic | Agentic | 判定 |
| --- | --- | --- | --- |
| EEGNet 评估指标 | 检索到结构类片段，却漏掉专门的评估指标笔记，回答称上下文没有指标信息 | 找到 `EEGNet_评估指标笔记` 和 `EEGNet总结`，回答 AUC、Accuracy、Precision、Recall、F1 及类别不平衡影响 | Agentic 明显更完整，直接检索发生漏召回 |
| DeepConvNet 与 ShallowConvNet | 只找全 ShallowConvNet 的 Square、Mean Pooling 和特征形状，称 DeepConvNet 信息不足 | 找到复现总结，给出两者逐层结构、卷积块数量、激活与池化差异 | Agentic 补足关键证据 |
| EEGNet + Transformer | 命中无关或信息不足片段，无法回答 Transformer 的作用 | 找到 DBConformer 和 Transformer 笔记，说明全局时间依赖、跨电极交互、动态加权和上下文化 | Agentic 补足关键证据 |

Non-Agentic 共执行 3 次本地检索和 3 次 LLM 请求，约 42 秒完成；Agentic 共执行 14 次本地检索和 16 次 LLM 请求，约 125 秒完成。Agentic 在三题上获得了更好的证据覆盖，但检索次数约为 4.7 倍，LLM 请求约为 5.3 倍，端到端时间约为 3 倍。这说明其收益来自查询规划和多轮补检，不是同一次混合检索自然产生的提升。

Agentic 三条回答均生成成功并写入 JSON，但输出在较长答案处停在句子或表格中间，表现为生成长度上限截断。因此本次可以评价“证据覆盖和回答方向”，不应把这些截断答案直接作为最终交付文本。原始结果为 `wiki-non-agentic-results.json`、`wiki-agentic-results.json` 及同名 `*-final.log`。

## 6. 本周个人总结与心得

这周学习第 3 章后，我对 Agent 的“记忆”和“检索”有了更具体的理解。以前我容易把记忆理解为把聊天记录保存下来，把检索理解为“搜到几篇文档再交给模型”。实际运行后我发现，两者都需要主动管理：记忆要提取什么、以什么结构保存、什么时候更新；检索要如何切分文档、怎样给片段编号、先召回哪些证据、是否值得继续追问。这些环节中的一个小错误，都可能让后面模型的回答看起来正常、实际上却没有可靠依据。

用户记忆实验让我认识到，长期记忆不是越丰富越好。Notes 模式确实留下了姓名、工作、编程偏好和项目等 6 条可追溯的事实；而 Enhanced Notes 的早期结果虽然更完整，却把“产品经理”扩写成负责 PRD、验收和 Sprint 等未经明确说明的内容。这个对比让我意识到，记忆中应该区分用户直接提供的事实、模型推断和待确认的信息。后续如果用于实验助手或 BCI 助手，我会给每条记忆保留来源、时间和置信度，避免把“可能原因”误存为实验事实。

ANN 和 BM25 实验让我更直观看到了检索并不是一个固定功能。HNSW 提高搜索参数后，Recall@10 从 0.442 提升到 0.968，但建索引和查询时间也随之增加；BM25 对错误码、编号和精确术语很有效，却无法靠词面匹配理解 `cat` 这类没有重合词的查询。因此，Dense、Sparse 和重排序不是可以彼此替代的模块，而是要根据任务互补使用。以后处理 EEG/BCI 笔记时，我会用 BM25 定位模型缩写、通道名和报错，用 Dense 检索相近方法或实验现象，再让混合排序决定最终证据。

个人 Wiki 实验给我的印象最深的是：索引正确比“模型能跑起来”更重要。第一次运行时，本地请求被系统代理转发而出现 502；修复后又发现同一文档的全部 chunk 使用了相同 ID，Dense 索引不断覆盖前面的片段，而 BM25 却留下重复条目。只有改为每个 chunk 使用唯一 ID、重新建立索引后，三个服务的计数才一致为 64。这让我以后不会只看终端显示“indexed successfully”，还会检查每一层的文档数、ID 是否唯一、日志是否有覆盖或重复，以及查询结果是否真的能回到预期的原文片段。

Non-Agentic 与 Agentic RAG 的对照也让我对“多步推理一定更好”保持谨慎。直接检索在三道问题上漏掉了评估指标、DeepConvNet 结构和 Transformer 作用的关键证据；Agentic 模式通过改写与补检找到了对应笔记，回答更完整。但它为 3 道题执行了 14 次检索和 16 次 LLM 请求，耗时约 125 秒，而 Non-Agentic 只进行了 3 次检索和 3 次 LLM 请求，约 42 秒。这个结果说明多轮检索可以改善证据覆盖，却不等于在所有问题上都值得使用；下一步应先提高首轮检索质量，再只对证据不足的复杂问题启用 Agentic 分解。

这周还让我形成了一个更具体的实验习惯：先做可复查的小对照，再扩展到完整实验；把原始 JSON、服务日志和最终记录一起保存；结论中同时写清模型、任务、样本量与限制。Notes 以外的部分记忆模式在本轮出现连接超时，Agentic 长回答也有输出截断，这些结果都不能为了让实验“完整”而当成成功。以后涉及修改原始数据、重建索引、提交训练任务或对外发送结果时，我会把路径检查、参数校验、权限确认和人工复核放在 Harness 与工具层，而不只相信模型生成的一段文字。

结合后续的 EEG/BCI 方向，我会把数据版本、被试与 session、通道与采样率、预处理参数、数据划分、随机种子、评价指标、错误状态和产物路径视为需要被持续管理的上下文。稳定不变的实验协议可以作为固定规则保存，训练进度和本轮指标作为动态状态追加，原始 EEG、长日志和外部论文则按需检索并标明来源。这样既能减少遗漏关键条件，也能避免把大量原始内容一次性塞给模型。
