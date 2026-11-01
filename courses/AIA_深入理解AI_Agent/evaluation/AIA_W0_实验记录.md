---
title: W0 实验记录
date: 2026-10-04
timezone: Asia/Shanghai
status: 已完成；行为实验，不含任务正确性 rubric
repository: bojieli/ai-agent-book
commit: dbc046eb896ac4e39aa19c7774c8bf49583b89a6
---

# W0 实验记录

> 公开版说明：本文件由本地正式实验记录整理入库。原始运行日志、API 回执、环境文件和缓存未提交到公开仓库；文中本地路径用于说明原始证据位置，不代表仓库内可直接访问。

## 1.上下文消融

在固定模型、固定三项任务和固定工具集合的条件下，分别移除历史、reasoning、工具定义或工具结果，会怎样影响 Agent 的终止行为、迭代次数、工具调用和答案的可依据性？

本实验衡量的是**上下文成分被移除后，Agent 的运行轨迹如何改变**。它不是“模型能力排行榜”，也没有为三项任务提供独立的任务正确性评分器。

## 2. 可复现条件

| 项 | 实际值 |
| --- | --- |
| 源码版本 | `dbc046eb896ac4e39aa19c7774c8bf49583b89a6` |
| 系统 / Python | Windows / Python 3.12.10 |
| Provider / 模型 | DeepSeek / `deepseek-v4-flash` |
| 运行入口 | `chapter1/context/main.py` |
| 命令 | `main.py --mode ablation --provider deepseek --cases 3` |
| 上下文模式 | `full`、`no_history`、`no_reasoning`、`no_tool_calls`、`no_tool_results` |
| 用例 | Currency Conversion、Complex Financial Analysis、Multi-Currency Budget Planning |
| 每组次数 | 3（每个用例一次），共 15 次 |
| 最大迭代数 | 10 |
| 终端设置 | `PYTHONUTF8=1`；仅解决 Windows GBK 打印 emoji 的日志问题，不改变 Agent 行为或 API 请求 |

API Key 只保存在本机 `.env`，未进入本记录和结果文件。

## 3. 原始证据

| 证据 | 文件 |
| --- | --- |
| 15 条机器可读结果 | [ablation_results.json](D:\Agent\实验记录\W0-第1章-context\ablation_results.json) |
| 完整控制台轨迹 | [ablation-console.log](D:\Agent\实验记录\W0-第1章-context\ablation-console.log) |
| 程序自动报告（仅作辅助） | [ablation_study_report.md](D:\Agent\实验记录\W0-第1章-context\ablation_study_report.md) |
| 程序自动图 | [ablation_study_results.png](D:\Agent\实验记录\W0-第1章-context\ablation_study_results.png) |

> 自动报告和自动图中的部分单项数值并非所有 15 条的分组汇总；本记录的表格直接由 `ablation_results.json` 的每组 3 条结果聚合而成，应以原始 JSON 与本表为准。

## 4. 结果

| 模式 | 终止回答数 / 3 | 平均耗时（秒） | 平均迭代 | 平均工具调用 | 可依据性判定 |
| --- | ---: | ---: | ---: | ---: | --- |
| `full` | 3 | 5.43 | 3.00 | 5.00 | `not_assessable` × 3 |
| `no_history` | 0 | 15.58 | 10.00 | 35.00 | `no_answer` × 3 |
| `no_reasoning` | 3 | 5.36 | 3.00 | 4.67 | `not_assessable` × 3 |
| `no_tool_calls` | 3 | 17.05 | 1.00 | 0.00 | `ungrounded` × 3；10 个无依据数值 |
| `no_tool_results` | 3 | 13.41 | 5.67 | 11.00 | `ungrounded` × 3；10 个无依据数值 |

### 4.1 `full`：基线

三项任务均在 3 轮内给出终止回答，平均进行了 5 次工具调用。该套件未给这些输出任务级正确性 rubric，故不能把 `completed=true` 误写成“全部答案被验证正确”。

### 4.2 `no_history`：没有历史，三项任务全都撞到迭代上限

三项任务均运行到 10 轮仍无终止回答，共发生 105 次工具调用（每任务平均 35 次），而基线总计仅 15 次。这是最明确的重复行动证据：Agent 无法看到先前 ReAct 步骤，因而不能知道什么已经做过、得到了什么信息。

### 4.3 `no_reasoning`：本次行为指标几乎未变差

三项任务都终止，平均迭代与基线相同（3.00），平均工具调用略少（4.67 对 5.00）。这只能说明在这三项任务和该模型下，去除历史 `reasoning_content` 后，现有行为指标未显著恶化；**不能**推广为“reasoning 没有价值”，因为本实验没有独立的正确性/质量 rubric，且工具结果和任务文本仍可能重建所需状态。

### 4.4 `no_tool_calls`：有回答，不代表有依据

工具定义被移除后，三个任务都在首轮给出文本，但工具调用数为 0。三个结果均被记录为 `ungrounded`，合计出现 10 个没有工具观测支撑的数值。这是“语言流畅、答案看似完整”与“任务通过外部观察完成”必须分开的直接例子。

### 4.5 `no_tool_results`：工具实际执行，但观察没有反馈给模型

三个任务均有终止回答，但平均工具调用从基线的 5.00 增至 11.00（约 2.2×），平均迭代从 3.00 增至 5.67，平均耗时从 5.43 秒增至 13.41 秒（约 2.5×）。所有三条都被标记 `ungrounded`，并合计含 10 个无依据数值。结论是：**执行工具不等于模型获得了观测；不把结果写回上下文，闭环就断了。**

## 5. 结论与边界

在本次 DeepSeek `deepseek-v4-flash`、三项任务、每组一次的条件下：

1. 历史轨迹对多步骤任务的连贯推进最关键；移除它导致持续重复与不终止。
2. 工具定义决定 Agent 能否与外部世界交互；没有定义时仍可写答案，但答案没有外部依据。
3. 工具结果是闭环观察；隐藏结果会增加调用和耗时，并产生无依据的数字。
4. 历史 reasoning 是否可移除依赖于任务和模型；本小样本不支持任何强泛化结论。

结果只说明上述固定条件下的行为趋势。模型版本、任务、温度、工具接口或隐藏结果的方式改变后，都应重新运行。特别是 `no_tool_results` 本次采用标准的空 tool content；若改为可见的 `marker` 占位符，模型会多得到“结果被隐藏”的信号，那是另一项实验。

## 6. 对 科研 Agent 的迁移

科研 Agent 的每次预处理、训练或统计检验都应将“可追溯结果摘要”写回轨迹：数据版本、参数、随机种子、指标、错误状态与产物路径。否则 Agent 即使真实启动过实验，也会像本实验的 `no_tool_results` 一样看不到观察，重复运行或用参数记忆补出未经证实的结论。任何覆盖原始数据、提交训练任务或发布结果的工具还应由 Harness 做权限、参数和结果验证。

## 7. 1-2 Web Search Agent 离线演示

### 目的与运行方式

按照第 1 章 README 的推荐顺序，在正式做上下文消融前，先运行：

```text
python main.py --provider offline-demo --output web-search-agent-offline-demo.json
```

该模式不调用 Kimi、不联网、也不消耗模型配额；它回放一条预先写好的 ReAct 示例轨迹。

### 观察到的流程

针对“Moonshot AI 的 Context Caching 是什么技术？”这一示例，轨迹依次呈现：

1. 思考：先查定义；
2. 调用 `web_search`；
3. 观察：得到“复用固定上下文前缀可减少重复计算”的示例结果；
4. 再次搜索适用场景；
5. 基于两次观察组织最终回答。

原始输出见 [web-search-agent-offline-demo.json](D:\Agent\实验记录\W0-第1章-context\web-search-agent-offline-demo.json)。它证明的是**程序中 ReAct 消息如何流动**，不证明真实网络搜索已经可用；真实联网搜索需要另外配置 Moonshot / Kimi Key。

## 8. 个人总结与心得

这周我对 Agent 的理解，从“模型会调用工具”变成了“模型只有在**看到工具结果**后，才真正形成了基于观察的下一步决策”。此前我更容易把最终答案是否正确，当作 Agent 是否完成任务的唯一标准；这次消融实验让我看到，这个判断并不可靠。

在 `full` 组中，Agent 能看到前面的行动和工具返回结果，因此三个任务都在较少轮次内结束。移除历史后，Agent 连续重复工具调用并全部撞到 10 轮上限；移除工具定义或工具结果后，它仍会生成看似完整的文字答案，但实验记录把这些答案标为 `ungrounded`。这让我认识到：**“有回答”不等于“有证据”，`completed` 也不等于“任务正确完成”。**

我对 `no_reasoning` 组的结果也有一个重要体会。本次三个任务没有明显变差，并不能说明 reasoning 不重要，而是因为当前任务的关键信息还能从任务文本和工具结果中重建。以后分析 Agent要考虑某个组件承载的信息能不能被其他地方替代？

结合我后续想做的 BCI，我会把“数据版本、被试与 session、预处理参数、随机种子、评价指标、错误信息、产物路径”视为工具结果的一部分，必须写回轨迹和实验记录。否则 Agent 即使实际启动过训练或预处理，也可能不知道结果是什么，进而重复运行，甚至在缺少证据时给出结论。

这次实验还让我形成了一个工程习惯：先跑最小对照，再扩大实验；原始 JSON、控制台日志和总结报告要一起保存；结论必须写清模型、任务、版本和样本范围。以后我会把高风险操作（覆盖原始数据、提交大量训练任务、发布科研结果）交给 Harness 做参数校验、权限限制和人工确认，而不是只依赖模型的文字判断。
