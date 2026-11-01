# 第4章 串：合并作业参考答案与解析

整理日期：2026-11-01；资料版本：v0.1.0。来源为同一份第4、5章合并作业，现按主题分章，保留原题号和稳定ID，不重新连续编号。答案为辅助编写并推导核对的学习参考，不是教师提供的标准答案；含题设修正和条件说明。原卷共20道主问题，两章各10道，不重复入库。

## 填空题 原第1题 [DS-CH04-HW45-FI-001]

来源：第4、5章 串、数组和广义表-作业.doc，原件第1页；原卷填空题第1题。

原题：

称为空串；                               称为空白串。

**参考答案**：

长度为0、没有任何字符的串；由一个或多个空格字符组成的串。

**解析与核对说明**：空串记为 ""，长度为0；空白串如 " "、"   "，长度分别为1、3。C字符串结尾的空字符 \0 不计入串长，不能把它当成空格。

**依据**：DS-CH04-S006、S017。

## 填空题 原第2题 [DS-CH04-HW45-FI-002]

来源：第4、5章 串、数组和广义表-作业.doc，原件第1页；原卷填空题第2题。

原题：

设S=“A;/document/Mary.doc”，则strlen(s)=                , “/”的字符定位的位置为          。

**参考答案**：

20；首次出现的位置为3（课程串ADT从1计数）。

**解析与核对说明**：原串是 A;/document/Mary.doc，按原件保留分号，不改成冒号。A、;、/各占1个字符，document占8个，第二个/占1个，Mary占4个，.占1个，doc占3个，共20个。两个/的位置为3、12；字符定位默认取第一次。若用C语言0起始数组下标，则分别为2、11。

**依据**：DS-CH04-S006、S014。

## 填空题 原第3题 [DS-CH04-HW45-FI-003]

来源：第4、5章 串、数组和广义表-作业.doc，原件第1页；原卷填空题第3题。

原题：

子串的定位运算称为串的模式匹配；                   称为目标串，             称为模式。

**参考答案**：

被查找的主串称为目标串；用于匹配的子串（待查字符串）称为模式。

**解析与核对说明**：模式匹配是在目标串S中寻找与模式串T相等的连续字符段，并返回其首次出现的位置。

**依据**：DS-CH04-S034、S035。

## 填空题 原第4题 [DS-CH04-HW45-FI-004]

来源：第4、5章 串、数组和广义表-作业.doc，原件第1页；原卷填空题第4题。

原题：

若n为主串长，m为子串长，则串的古典（朴素）匹配算法最坏的情况下需要比较字符的总次数为
          。

**参考答案**：

按课件的常用最坏成功匹配口径，填 m(n-m+1)；最坏时间复杂度写 O(nm)。

**解析与核对说明**：条件是1≤m≤n，从主串第1位开始，前n-m次尝试都比较到模式最后一位才失配，最后一次完整匹配。例如S=a^(n-1)b，T=a^(m-1)b。共n-m+1次尝试，每次m次比较。课件第52—53页实际解释的是这种查找成功情形。若要求第51页代码在失败查找中的精确全局最大比较次数，不能无条件套此乘积：S="aaaaa"、T="aab"时，该while实现还会比较不足m的尾段，共11次，大于3×3=9；复杂度仍为O(nm)。题目未限定实现和成功/失败时，应说明这一口径。

**依据**：DS-CH04-S051—S053。

## 单选题 原第1题 [DS-CH04-HW45-SC-001]

来源：第4、5章 串、数组和广义表-作业.doc，原件第1页；原卷单选题第1题。

原题：

串是一种特殊的线性表，其特殊性体现在：
   Ａ．可以顺序存储       Ｂ．数据元素是一个字符
Ｃ．可以链式存储        Ｄ．数据元素可以是多个字符

**参考答案**：

B。

**解析与核对说明**：串是数据元素为单个字符的特殊线性表。能否顺序或链式存储不是区分串与一般线性表的关键。

**依据**：DS-CH04-S004、S006、S016。

## 单选题 原第2题 [DS-CH04-HW45-SC-002]

来源：第4、5章 串、数组和广义表-作业.doc，原件第1页；原卷单选题第2题。

原题：

设有两个串p和q，求q在p中首次出现的位置的运算称作：
   Ａ．连接      Ｂ．模式匹配    Ｃ．求子串       Ｄ．求串长

**参考答案**：

B，模式匹配。

**解析与核对说明**：求q在p中首次出现的位置属于Index/模式匹配；Concat是连接，SubString是取给定位置的子串，StrLength是求长度。

**依据**：DS-CH04-S009、S034、S035。

## 单选题 原第3题 [DS-CH04-HW45-SC-003]

来源：第4、5章 串、数组和广义表-作业.doc，原件第1页；原卷单选题第3题。

原题：

设串s1=’ABCDEFG’，s2=’PQRST’，函数con(x,y)返回x和y串的连接串，subs(s, i, j)返回串s的从序号i开始的j个字符组成的子串，len(s)返回串s的长度，则con(subs(s1, 2, len(s2)), subs(s1, len(s2), 2))的结果串是：
   Ａ．BCDEF       Ｂ．BCDEFG     Ｃ．BCPQRST        Ｄ．BCDEFEF

**参考答案**：

D，BCDEFEF。

**解析与核对说明**：len(s2)=5；subs(s1,2,5)="BCDEF"；subs(s1,5,2)="EF"；连接得到"BCDEFEF"。两段都来自s1，不是把s2本身拼接进去。序号从1开始。

**依据**：DS-CH04-S011、S013。

## 计算题 原第1题 [DS-CH04-HW45-CAL-001]

来源：第4、5章 串、数组和广义表-作业.doc，原件第2页；原卷计算题第1题。

原题：

设s=’I AM A STUDENT’, t=’GOOD’, q=’WORKER’,
求Replace (s,’STUDENT’, q) 和Concat (SubString (s,6,2), Concat (t, SubString (s,7,8)))。

**参考答案**：

Replace结果为 "I AM A WORKER"；若两个表达式各从题设原始s求值，Concat结果为 "A GOOD STUDENT"。

**解析与核对说明**：原始s="I AM A STUDENT"长14，位置1:I、2:空格、3:A、4:M、5:空格、6:A、7:空格、8:S，后续为TUDENT。SubString(s,6,2)="A "；SubString(s,7,8)=" STUDENT"；先连接t得"GOOD STUDENT"，再连接得"A GOOD STUDENT"，空格两侧各1个。这里Replace与Concat分别从原始s求值。若把Replace(&s,...)当成有副作用的语句先执行，s将缩为13个字符，此时SubString(s,7,8)越界，应报参数错误，不能静默截断。

**依据**：DS-CH04-S012、S013、S018。

## 算法设计题 原第1题 [DS-CH04-HW45-ALG-001]

来源：第4、5章 串、数组和广义表-作业.doc，原件第3页；原卷算法设计题第1题。

原题：

编写一个实现串的置换操作Replace (&S, T, V)的算法。

**参考答案**：

```cpp
#include <string>
#include <utility>

// Replace non-overlapping occurrences in the original S, from left to right.
// Do not rescan text inserted from V. T and V may alias S.
inline bool Replace(std::string& S, const std::string& T, const std::string& V) {
    if (T.empty()) return false;
    std::string result;
    std::size_t i = 0;
    while (i < S.size()) {
        if (T.size() <= S.size() - i && S.compare(i, T.size(), T) == 0) {
            result.append(V);
            i += T.size();
        } else {
            result.push_back(S[i]);
            ++i;
        }
    }
    S.swap(result);
    return true;
}
```

**解析与核对说明**：采用C++17的std::string作顺序串，容量动态增长。T必须非空，V允许为空。按原串从左向右扫描，每次匹配成功将V写入新结果并跳过原串中这段T；新插入的V不再参与匹配，所以T="a"、V="aa"不会无限循环，重叠出现也不会重复替换。构造完毕后才swap回S，允许T或V引用S；分配异常会抛出，S保留原值。设n=|S|、m=|T|、L为结果长，直接比较的最坏时间O(nm+L)，辅助空间O(L)，需要处理空串、无匹配、相邻匹配、重叠、删除、增长及别名。这里处理单字节字符或字节串；不能据此声称UTF-8汉字按字节反序或任意字符切分也安全。代码已按C++17编译并通过实际随机和边界检查。

**依据**：DS-CH04-S012；第25—30页顺序串与动态空间思路。

## 算法设计题 原第2题 [DS-CH04-HW45-ALG-002]

来源：第4、5章 串、数组和广义表-作业.doc，原件第3页；原卷算法设计题第2题。

原题：

写出将字符串反序的递推或递归算法，例如字符串为“abcsxw”，反序为“wxscba”

**参考答案**：

答案要点：reverseRecursive递归交换首尾，时间Θ(n)、递归栈O(n)；reverseIterative迭代交换，时间Θ(n)、辅助空间O(1)。空串直接返回，例abcsxw反序为wxscba。

```cpp
#include <string>
#include <utility>

inline void reverseRange(std::string& S, std::size_t left, std::size_t right) {
    if (left >= right) return;
    std::swap(S[left], S[right]);
    reverseRange(S, left + 1, right - 1);
}

inline void reverseRecursive(std::string& S) {
    if (!S.empty()) reverseRange(S, 0, S.size() - 1);
}

inline void reverseIterative(std::string& S) {
    std::size_t left = 0, end = S.size();
    while (left < end) {
        --end;
        if (left >= end) break;
        std::swap(S[left], S[end]);
        ++left;
    }
}
```

**解析与核对说明**：递归思想：交换当前首尾字符，再处理内部子串；left≥right停止。空串需先判断，以免size()-1发生无符号下溢。递归关系T(n)=T(n-2)+O(1)，时间Θ(n)，递归栈O(n)；同时提供迭代版本，时间Θ(n)、辅助空间O(1)。两种算法均原地操作，单字符保持不变。例"abcsxw"→"wxscba"。代码对std::string的字节进行交换，适合本题ASCII字符，不适合直接按字节反转UTF-8多字节文本。两种实现均已实际测试。

**依据**：合并作业原件第3页算法设计第2题；本题自行推导。
