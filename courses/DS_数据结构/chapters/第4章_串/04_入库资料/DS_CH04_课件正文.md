# 数据结构 第4章 串 课件正文

## 核对补充：引用本节结论时请保留适用条件

本节为整理时依据原题和代码推导的校正说明，原PPTX未修改。

- [DS-CH04-S006-CHECK] C语言空字符写作 `\0`，不是原课件部分位置的 `/0`；它不同于空指针NULL，也不计入strlen的长度。空白串至少包含一个空格。
- [DS-CH04-S018-CHECK] 从原始s="I AM A STUDENT"分别计算，Replace得到"I AM A WORKER"，Concat表达式得到"A GOOD STUDENT"，其中空格要按原字符逐个计数。若先执行有副作用的Replace，再算原Concat，则SubString(s,7,8)越界。
- [DS-CH04-S051-CHECK] m(n-m+1)是课件讨论的最坏成功匹配次数或只尝试完整窗口的BF口径；第51页while实现失败时可能继续比较不足m的尾段，例如S="aaaaa"、T="aab"共11次，不能把9次当此实现所有情形的上界。BF最坏时间复杂度仍为O(nm)。
- [DS-CH04-S057-CHECK] 示例成功匹配的起始位置是6，函数返回i-m；退出时扫描指针i不是起始位置6。不要把返回值与退出时i混淆。
- [DS-CH04-S074-CHECK] KMP搜索时间O(n)，加上线性预处理为O(n+m)，辅助空间O(m)；这不表示精确字符比较次数永远只有n或n+m。失配时i不回溯，但同一S[i]可能与多个T[j]比较。BF“平均近似O(n+m)”也需要输入分布等假设，不能当无条件平均复杂度结论。


来源：第4章 串（共4学时）.pptx；共76页。保留原页码；上标、下标分别记为^{…}、_{…}。文字提取不保证完整表达图片、箭头和动画。

## 原课件第 1 页 [DS-CH04-S001]

第四章 串

## 原课件第 2 页 [DS-CH04-S002]

数据结构
插入运算、删除运算、修改运算
查找运算、排序运算
逻辑结构
物理结构
（存储）
数据运算
线性结构(线性表、栈、队列、串、数组)
非线性结构(树、图)
顺序结构
链式结构
索引结构
散列结构
数据结构课程的内容
逻辑结构唯一
存储结构不唯一
运算的实现依赖于存储结构

## 原课件第 3 页 [DS-CH04-S003]

第1学时

## 原课件第 4 页 [DS-CH04-S004]

三种特殊的线性表——栈、队列、串
从数据结构角度看，栈和队列是操作受限的线性表，它们的逻辑结构相同。
串是重要的非数值处理对象，它是以字符作为数据元素的线性表。
第4章   串（String）

## 原课件第 5 页 [DS-CH04-S005]

第4章   串（String）
4.2  串的表示和实现
4.3  串的模式匹配算法
1. 定义
2. 逻辑结构
3. 存储结构
4. 运算规则
5. 实现方式
4.1  串类型的定义

## 原课件第 6 页 [DS-CH04-S006]

记为：      s =‘a_{1} , a_{2} , …….. , a_{n’}   (n≥0 )
串名
串值（用‘’括起来）
串：即字符串，是由零个或多个字符组成的有限序列,
是数据元素为单个字符的特殊线性表。
4.1  串类型的定义
若干术语：
串长:串中字符个数（n≥0）. n=0 时称为空串  。
空白串:由一个或多个空格符组成的串。
字符位置:字符在串中的序号（从1开始）。
串相等:串长度相等，且对应位置上字符相等。
隐含结束符‘/0’ ，即ASCII码NULL

## 原课件第 7 页 [DS-CH04-S007]

S1="ab12cd "
S2="b12"
S3="b13“
串的术语：
子串：串中任意个连续的字符组成的子序列。
主串：包含子串的串。
子串的位置：子串的第一个字符在主串中的序号。
4.1  串类型的定义
S2是S1的子串吗？
S3是S1的子串吗？
S2在S1中的位置是？
2

## 原课件第 8 页 [DS-CH04-S008]

ADT String {
数据对象：
D＝{ a_{i} |a_{i}∈CharacterSet,
i=1,2,...,n,       n≥0 }
数据关系：
R_{1}＝{ < a_{i-1}, a_{i} > | a_{i-1}, a_{i} ∈D,
i=2,...,n }
4.1  串类型的定义

## 原课件第 9 页 [DS-CH04-S009]

基本操作：
StrAssign (&T, chars)
StrCopy (&T, S)
DestroyString (&S)
StrEmpty (S)
StrCompare (S, T)
StrLength (S)
Concat (&T, S1, S2)
SubString (&Sub, S, pos, len)
ClearString (&S)
Replace (&S, T, V)
Index (S, T, pos)
StrInsert (&S, pos, T)
StrDelete (&S, pos, len)
} ADT String
4.1  串类型的定义

## 原课件第 10 页 [DS-CH04-S010]

StrInsert (&S, pos, T)	(插入)
初始条件：串 S 和 T 均存在，1≤pos≤StrLength(S)＋1。
操作结果：在串 S 的第 pos 个字符之前插入串T。
例如：S = chater,T = rac,则执行 StrInsert (S, 4, T)
得到 S = character
StrDelete (&S, pos, len)	(删除)
初始条件：串 S 存在，且1≤pos≤StrLength(S)-len+1。
操作结果：从串 S 中删除第 pos 个字符起长度为len的子串。
例如：S=character，执行StrDelete (S, 3, 4) ，得到S= chter。
基本操作：
4.1  串类型的定义

## 原课件第 11 页 [DS-CH04-S011]

StrAssign (&T, chars)	(串赋值)
初始条件：chars 是字符串常量。
操作结果：把 chars 赋为 T 的值。
StrCopy (&T, S)	(串复制)
初始条件：串 S 存在。
操作结果：由串 S 复制得串 T。
基本操作：
4.1  串类型的定义
Concat (&T, S1, S2)	(串联接)
初始条件：串 S1 和 S2 存在。
操作结果： T 为由串 S1 和串 S2 连接所得的串。
例如： Concat( T, man, kind)
求得  T = mankind

## 原课件第 12 页 [DS-CH04-S012]

Replace ( S, T, V)	(串置换)
初始条件：
串 S, T 和 V 均已存在，且 T 是非空串。
操作结果：
用 V 替换主串 S 中出现的所有与（模式串）T 相等的不重叠的子串。
假设 S = abcaabcaaabca,  T = bca 
若 V = x , 则经置换后得到 S = axaxaax 
基本操作：
4.1  串类型的定义

## 原课件第 13 页 [DS-CH04-S013]

SubString (&Sub, S, pos, len)	(求子串)
初始条件：
操作结果: 以 Sub 返回串 S 中第 pos 个字符起长度为 len 的子串。
串 S 存在，1≤pos≤StrLength(S)
且  0≤len≤StrLength(S)-pos+1。
SubString ( sub, commander , 4, 3)
sub = man 
SubString( sub, commander  , 1, 9)
SubString( sub, commander , 9, 1)
sub = r 
sub = commander 
基本操作：
4.1  串类型的定义
SubString(sub,student, 5, 0) sub =?
sub = 

## 原课件第 14 页 [DS-CH04-S014]

Index ( S, T, pos)	(定位函数)
初始条件：串 S 和 T 存在，且 T 是非空串，  1≤pos≤StrLength(S)。
操作结果：若主串 S 中存在和串 T 值相同的子串，则返回它在主串 S 中第 pos个字符之后第一次出现的位置; 否则函数值为0。
基本操作：
4.1  串类型的定义
假设 S = abcaabcaaabc ,  T = bca 
Index(S, T, 1)
= 2;
Index(S, T, 3)
= 6;
Index(S, T, 8)
= 0;

## 原课件第 15 页 [DS-CH04-S015]

在上述抽象数据类型定义的13种操作中，
串赋值 StrAssign
串比较 StrCompare、求串长 StrLength、
串联接 Concat 以及求子串 SubString
等5种操作构成串类型的最小操作子集。
思考：StrDelete (&S, pos, len)	(删除)怎么用上面的操作实现？
先SubString，再 Concat 。
基本操作：
4.1  串类型的定义

## 原课件第 16 页 [DS-CH04-S016]

串的逻辑结构和线性表极为相似，区别仅在于串的数据对象约束为字符集。
在线性表的基本操作中，大多以“单个元素”作为操作对象；
而在串的基本操作中，通常以“串的整体”作为操作对象。
串的基本操作和线性表有很大差别：
串和线性表的比较：
4.1  串类型的定义

## 原课件第 17 页 [DS-CH04-S017]

练1：串是由              字符组成的序列，一般记为              。
练2：现有以下4个字符串：
a =‘BEI’ 	b =‘JING’    c = ‘BEIJING’     d = ‘BEI JING’
问：① 他们各自的长度？
② a是哪个串的子串？在主串中的位置是多少？
a =3，b =4，c = 7，d=8
a是c和d的子串，在c和d中的位置都是1
练3：空串和空白串有无区别？
答：有区别。空串(Null String)是指长度为零的串；
而空白串(Blank  String),是指包含一个或多个空白字符‘  ’(空格键)的字符串.
0个或多个
S=’a_{1}a_{2}……a_{n}’
练习：
4.1  串类型的定义

## 原课件第 18 页 [DS-CH04-S018]

练习4：设 s =‘I AM A STUDENT’, t =‘GOOD’, q=‘WORKER’。
StrLength(s) ＝
StrLength(t) ＝
SubString(s, 8, 7)=
SubString(t, 2, 1)=
Index(s, ‘A’)=
Index(s, t,3)=
Replace(s, ‘STUDENT’,q)=
14
4
‘STUDENT’
‘O’
3
0       （ s中没有t！）
’I AM A WORKER’
练习5：Concat(SubString(s,6,2), Concat(t,SubString(s,7,8))) ＝？
‘A  GOOD  STUDENT’
练习：
4.1  串类型的定义

## 原课件第 19 页 [DS-CH04-S019]

4.2	串的表示和实现
定长顺序存储表示
——用一组地址连续的存储单元存储串值的字符序列。 --静态数组
堆分配存储表示
——用一组地址连续的存储单元存储串值的字符序列,但存储空间是在程序执行过程中动态分配而得。--动态数组
串的块链存储表示
——链式方式存储
串有三种机内表示方法：
顺序
存储
链式存储

## 原课件第 20 页 [DS-CH04-S020]

特点：用一组连续的存储单元来存放串，直接使用定长的字符数组来定义，数组的上界预先给出，故称为静态存储分配。
例如：#define Maxstrlen 255    //用户可用的最大串长
typedef unsigned char SString[ Maxstrlen＋1 ] ;
SString s;   //s是一个可容纳255个字符的顺序串。
注：
一般用SString[0]来存放串长信息； SString[0]的类型是字节，一个字节表示数字长度时，最大值是255，所以上述字符串最长是255 。
若字符串超过Maxstrlen 则自动截断（因为静态数组存不 进去）。
4.2	串的表示和实现
1.定长顺序存储

## 原课件第 21 页 [DS-CH04-S021]

Status Concat ( Sstring &T, Sstring S1 ,Sstring S2)
{  if ( S1[0] +S2[0] <= MAXSTRLEN)  //未截断
{  T[1..S1[0]] = S1[ 1..S1[0]];
T[ S1[0]+1 .. S1[0]+S2[0] ] = S2[ 1 .. S2[0] ];
T[0] = S1[0] + S2[0];   uncut = TRUE;
}
else  if ( S1[0] < MAXSTRSIZE )      // 截断，先存放S1，再存放S2的一部分
{  T[ 1..S1[0] ] = S1[ 1..S1[0] ];
T[ S1[0] +1 .. MAXSTRLEN ] = S2[ 1.. MAXSTRLEN- S1[0]];
T[0] = MAXSTRLEN;   uncut = FALSE;
}
else   {   T[ 0.. MAXSTRLEN ] = S1[0.. MAXSTRLEN ];  // 截取（仅取S1）
uncut = FALSE;
}
return  uncut;
}  // Concat
4.2	串的表示和实现
1.定长顺序存储：串连接

## 原课件第 22 页 [DS-CH04-S022]

Status SubString (SString &sub, SString S, int pos, int len )
{   if (pos<1 || pos>S[0] || len<0 || len>S[0]-pos+1)
return ERROR;   //pos不合法则警告
Sub[1……len] = S [pos……pos+len-1];
Sub[0]=len;   return OK;
}
将串S中从第pos个字符开始长度为len的字符序列复制到串Sub中（注：串Sub的预留长度与S一样）
s =‘ a_{1} , a_{2} , …….. , a_{n}’
pos
len
4.2	串的表示和实现
1.定长顺序存储：求子串

## 原课件第 23 页 [DS-CH04-S023]

讨论：想存放超长字符串怎么办？——静态数组有缺陷！
改用动态分配的一维数组——
“堆”！
讨论

## 原课件第 24 页 [DS-CH04-S024]

第2学时

## 原课件第 25 页 [DS-CH04-S025]

思路：利用malloc函数合理预设串长空间。
特点： 若在操作中串值改变，还可以利用realloc函数按新串长度增加(堆砌)空间。
Typedef struct {
char *ch;     // 若非空串,按串长分配空间; 否则 ch = NULL
int length;   //串长度
}HString
特点：仍用一组连续的存储单元来存放串，但存储空间是在程序执行过程中动态分配而得。
约定：所有按堆存储的串，其关键信息放置在：
4.2	串的表示和实现
2.堆分配存储

## 原课件第 26 页 [DS-CH04-S026]

Status StrInsert ( HString &S,  int pos,  HString T ) {
if (pos<1||pos>S.length+1) return ERROR;    //pos不合法则告警
if(T.length){          //只要串T不空，就需要重新分配S空间，以便插入T
if (!（S.ch=(char*)realloc (S.ch, (S.length+T.length)*
sizeof(char))  ))  exit(OVERFLOW);
for ( i=S.length-1; i>=pos-1; --i )   //为插入T而腾出pos之后的位置
S.ch [i+T.length] = S.ch [i];       //从S的pos位置起全部字符均后移
S.ch[pos-1…pos+T.length-2] = T.ch[0…T.length-1]; //插入T
S.length + = T.length;            //刷新S串长度
} return OK;
}//StrInsert
4.2	串的表示和实现
2.堆分配存储：插入操作

## 原课件第 27 页 [DS-CH04-S027]

Status StrAssign( HString &T, char *chars ) {
if (T.ch)   free(T.ch);
for (i=0, c=chars;* c; ++i, ++c);       //求串长度
if (!i) {T.ch = NULL; T.length = 0;}
else{
if (!(T.ch = (char*)malloc (i*sizeof(char))))
exit(OVERFLOW);
T.ch[0..i-1] = chars[0..i-1];
T.length =i;
}
Return OK;
}//StrAssign
指针变量C也可以自增！意即每次后移一个数据单元。
直到终值为“假”停止，串尾特征是‘/0’＝NULL=0
4.2	串的表示和实现
2.堆分配存储：赋值操作
该参数是一个字符串，C语言约定用字符数组存储字符串常量时，自动在串尾加结束符 ‘ \0’，以利操作加速，但不计入串长；char c[10]=“abcde”，自动加入一个‘ \0’

## 原课件第 28 页 [DS-CH04-S028]

比较操作：
Int  Strcompare ( Hstring S, Hstring T )
{
for ( i = 0; i < S.length && i <T.length; ++i )
if ( S.ch[i] != T.ch[i] )  return  S.ch [i] – T.ch[i];
return  S.length- T.length;
}  // StrCompare
清空操作：
Status ClearString ( Hstring  &S)
{
if ( S.ch )  { free(S.ch);  S.ch = NULL; }
S.length = 0;
return  OK;
} // ClearString
4.2	串的表示和实现
2.堆分配存储：

## 原课件第 29 页 [DS-CH04-S029]

Status Concat ( HString  &T, Hstring  S1,  Hstring  S2 )
{  //用T返回由S1和S2连接而成的新串。
if (T.ch)   free(T.ch);            // 释放旧空间
if ( !(T.ch = (char *) malloc ((S1.length+S2.length) *
sizeof (char) ) ) )       exit ( OVERFLOW);
T.ch[0 .. S1.length-1] = S1.ch[0 .. S1.length-1];
T.length = S1.length + S2.length ;
T.ch [S1.length .. T.length-1] = S2.ch [0 .. S2.length-1];
return  OK;
} // Concat
4.2	串的表示和实现
2.堆分配存储：连接操作

## 原课件第 30 页 [DS-CH04-S030]

Status SubString ( Hstring &Sub, Hstring S,int pos,int len )
{  //用Sub返回串S的第pos个字符起长度为len的子串。
// 其中,1<=pos<= StrLength (S) 且 0<=len<=StrLength(S)-pos+1。
if ( pos < 1 || pos>S.length || len<0 ||  len>S.length-pos+1)
return  ERROR;        // 参数不合法
if ( Sub.ch)   free ( Sub.ch);    // 释放旧空间
if (!len)  { Sub.ch = NULL; Sub.length = 0; }   // 空子串
else {                                                                  // 完整子串
Sub.ch = ( char *) malloc ( len *sizeof ( char ));
Sub.ch[0..len-1] = S.ch [ pos-1.. Pos+len-2] ;
Sub.length = len;
}
return  OK;
}
4.2	串的表示和实现
2.堆分配存储：求子串操作

## 原课件第 31 页 [DS-CH04-S031]

讨论：法1存储密度为       ；法2存储密度为           ；
显然，若数据元素很多，用法2存储更优—称为块链结构
特点 ：用链表存储串值，易插入和删除。
法1：链表结点（数据域）大小取1
法2：链表结点（数据域）大小取n(例如n=4)
1/2
9/15=3/5
A          
B          
C           
I         NULL
head
head
A    B     C    D  
E     F    G     H 
I       #     #     #  NULL
4.2	串的表示和实现
3.链式存储

## 原课件第 32 页 [DS-CH04-S032]

#define  CHUNKSIZE  80     //可由用户定义的块大小
typedef  struct  Chunk {           //首先定义结点类型
char    ch [ CHUNKSIZE ];  //结点中的数据域
struct  Chunk * next ;          //结点中的指针域
}Chunk;
串的链式存储结构对某些操作比较方便（如：链接操作），但是总体来说没有前面的两种存储结构灵活。
typedef  struct {                 //其次定义用链式存储的串类型
Chunk  *head;           //头指针
Chunk  *tail;             //尾指针
int  curLen;               //结点个数
} Lstring;
4.2	串的表示和实现
3.链式存储：块链的定义

## 原课件第 33 页 [DS-CH04-S033]

第3学时

## 原课件第 34 页 [DS-CH04-S034]

回顾：index(S，T，pos)
对应word中的查找功能
什么是模式匹配?
S: |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19
吃 | 葡 | 萄 | 不 | 吐 | 葡 | 萄 | 皮 | ， | 不 | 吃 | 葡 | 萄 | 倒 | 吐 | 葡 | 萄 | 皮 | 。
T: | 葡 | 萄 | 皮
 | 1 | 2 | 3
index(S,T，1)=？
6
查找下一个的功能？
index(S,T，9)=？
16
若存在，则返回它在主串S中第pos个字符之后第一次出现的位置；
否则，函数值为0。
S:主串
T：模式串
Pos：查找的开始位置
4.3    串的模式匹配算法

## 原课件第 35 页 [DS-CH04-S035]

4.3    串的模式匹配算法
模式匹配(Pattern Matching) 即子串定位运算（Index函数）。
算法目的：确定主串中所含子串第一次出现的位置（定位）
——即如何实现 Index(S,T,pos)函数（见教材P71）
初始条件：串S和T存在，T是非空串，1≤pos≤StrLength(s)
操作结果：若主串S中存在和串T值相同的子串，则返回它在主串S中第pos个字符之后第一次出现的位置；否则函数值为0。
注：S称为被匹配的串，T称为模式串。
若S包含串T，则称“匹配成功”，否则称 “匹配不成功” 。

## 原课件第 36 页 [DS-CH04-S036]

4.3    串的模式匹配算法
思考提问1：模式匹配算法（BF算法）的算法思想是什么？
1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19
吃 | 葡 | 萄 | 不 | 吐 | 葡 | 萄 | 皮 | ， | 不 | 吃 | 葡 | 萄 | 倒 | 吐 | 葡 | 萄 | 皮 | 。
 | 葡 | 萄 | 皮
 | 1 | 2 | 3
index(S,T，pos)=？
6
S
T
BF算法思想
主串S[pos]==T[1]?若相等继续比较
否则，S[pos+1]==T[1]?
直到找到，或者失败
思考1：从哪开始比较？
思考2：不相等怎么办？
思考3：相等怎么办？
思考4：什么时候结束？

## 原课件第 37 页 [DS-CH04-S037]

① BF算法设计思想：
将主串的第pos个字符和模式的第1个字符比较，
若相等，继续逐个比较后续字符；
若不等，从主串的下一字符（pos+1）起，重新与第一个字符比较。
BF算法  （又称古典或经典的、朴素的、穷举的）
KMP算法（特点：速度快）
算法种类：
直到主串的一个连续子串字符序列与模式相等 。返回值为S中与T匹配的子序列第一个字符的序号，即匹配成功。
否则，匹配失败，返回值 0 .
S=‘a b a b c a b c a c b a b’
T=‘a b c a c’
pos=5

## 原课件第 38 页 [DS-CH04-S038]

例：主串S="ababcabcacbab"，模式T="abcac"。
用定长顺序存储表示。
a     b     a     b     c     a     b    c     a   c     b     a    b
i=3，j=3失败；
i回溯到2，j回溯到1
i回溯的位置能用刚才失败时的i和j的值表达出来吗？
i
j
i
j
i
j
第
1
趟
a     b     c     a     c
i-j+2
4.3    串的模式匹配算法—BF算法
1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13

## 原课件第 39 页 [DS-CH04-S039]

例：主串S="ababcabcacbab"，模式T="abcac"
a     b     a     b     c     a    b     c     a    c    b     a    b
i=3，j=3失败；
i回溯到2，j回溯到1
j
i
第
1
趟
a     b     c     a     c
4.3    串的模式匹配算法—BF算法
1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13

## 原课件第 40 页 [DS-CH04-S040]

例：主串S="ababcabcacbab"，模式T="abcac"
a     b     a     b     c     a     b    c    a     c     b    a     b
i=2，j=1失败
i回溯到3，j回溯到1
第
2
趟
i
j
a      b     c    a     c
4.3    串的模式匹配算法—BF算法
1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13

## 原课件第 41 页 [DS-CH04-S041]

例：主串S="ababcabcacbab"，模式T="abcac"
a     b     a     b     c    a     b     c    a     c     b     a    b
i=2，j=1失败
i回溯到3，j回溯到1
第
2
趟
i
j
a      b     c     a     c
4.3    串的模式匹配算法—BF算法
1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13

## 原课件第 42 页 [DS-CH04-S042]

例：主串S="ababcabcacbab"，模式T="abcac"
a     b     a     b     c     a     b    c    a     c     b    a    b
a     b     c     a    c
i=7，j=5失败
i回溯到4，j回溯到1
第
3
趟
i
j
i
j
i
j
i
j
i
j
4.3    串的模式匹配算法—BF算法
1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13

## 原课件第 43 页 [DS-CH04-S043]

例：主串S="ababcabcacbab"，模式T="abcac"
a     b     a     b     c    a     b    c     a     c     b     a     b
a     b     c     a     c
i=7，j=5失败
i回溯到4，j回溯到1
第
3
趟
i
j
4.3    串的模式匹配算法—BF算法
1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13

## 原课件第 44 页 [DS-CH04-S044]

例：主串S="ababcabcacbab"，模式T="abcac"
a     b     a     b     c     a     b     c    a    c     b    a     b
a     b     c     a     c
i=4，j=1失败
i回溯到5，j回溯到1
第
4
趟
i
j
4.3    串的模式匹配算法—BF算法
1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13

## 原课件第 45 页 [DS-CH04-S045]

例：主串S="ababcabcacbab"，模式T="abcac"
a     b     a     b     c     a     b    c     a     c    b    a     b
a     b     c     a     c
i=4，j=1失败
i回溯到5，j回溯到1
第
4
趟
i
j
4.3    串的模式匹配算法—BF算法
1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13

## 原课件第 46 页 [DS-CH04-S046]

例：主串S="ababcabcacbab"，模式T="abcac"
a     b     a     b     c     a     b    c    a     c     b    a     b
a     b     c     a     c
i=5，j=1失败
i回溯到6，j回溯到1
第
5
趟
i
j
4.3    串的模式匹配算法—BF算法
1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13

## 原课件第 47 页 [DS-CH04-S047]

例：主串S="ababcabcacbab"，模式T="abcac"
a     b     a     b     c     a    b     c    a     c     b    a     b
a     b     c     a     c
i=5，j=1失败
i回溯到6，j回溯到1
第
5
趟
i
j
4.3    串的模式匹配算法—BF算法
1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13

## 原课件第 48 页 [DS-CH04-S048]

例：主串S="ababcabcacbab"，模式T="abcac"
a     b     a     b     c     a    b    c     a    c     b     a     b
a     b     c     a     c
i=11，j=6，T中全部字符都比较完毕，匹配成功。
匹配成功时：j的值是多少？
T在S中的位置怎么用i，j，T[0]表示？
第
6
趟
i
j
i
j
i
j
i
j
i
j
i
j
j>T[0]
i-T[0]
4.3    串的模式匹配算法—BF算法
1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13
循环执行的条件是什么？
i<=S[0] && j<=T[0]

## 原课件第 49 页 [DS-CH04-S049]

匹配成功（另外一种情况）：i>S[0]   &&  j>T[0]
4.3    串的模式匹配算法—BF算法
a     b     a     b     c     a    b    b     a    b     c     a     c
a     b     c     a     c
1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13
i
j

## 原课件第 50 页 [DS-CH04-S050]

思考：不成功时是什么情况？
i>S[0] &&  j<=T[0]
4.3    串的模式匹配算法—BF算法
a     b     a     b     c     a    b    b     a    c     b     a     b
a     b     c     a     c
1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13
i
j
i
j
i
j

## 原课件第 51 页 [DS-CH04-S051]

Int Index (SString S, SString T, int pos) {
i=pos;      j=1;
while ( i<=S[0] && j<=T[0] ) {
if (S[i] = = T[j] ) {++i, ++j}   //继续比较后续字符
else {i=i-j+2; j=1;}      //指针回溯到 下一首位，重新开始匹配
}
if(j>T[0]) return i-T[0];  //子串结束，说明匹配成功
else return 0;
}//Index
思考：
（1）i<=S[0]可以改成S[0]-T[0]+1吗？
（2）匹配成功时，循环执行的次数最多是多少？
4.3    串的模式匹配算法—BF算法
S=‘a b a b c a a b a c b a b’
T=‘a b c a c’
例如：S="aaaaaaaaaaab"
T="aaab"

## 原课件第 52 页 [DS-CH04-S052]

思考：
（1）i<=S[0]可以改成S[0]-T[0]+1吗？
（2）匹配成功时，循环执行的次数最多是多少？
答：
（1）不能改，i是S和T比较时新一轮的比较开始位置，而且在后面的比较过程中还要i++。
（2） (n-m+1)*m
4.3    串的模式匹配算法—BF算法

## 原课件第 53 页 [DS-CH04-S053]

讨论：
若n为主串长度，m为子串长度，则串的BF匹配算法最坏的情况下需要比较字符的总次数为
O(n*m)
查找成功时最恶劣情况是：主串中前面n-m个位置都部分匹配到子串的最后一位时出现不等，此时需要将指针i回溯，并从模式的第一个字符开始重新比较，整个匹配过程中，指针i需回溯（n-m)次，则while循环次数为(n-m+1)*m。
但一般情况下，BF算法的时间复杂度为近似于O(n+m)
例如：在上面第二段文字中查找“回族”两个字。
例如：S="aaaaaaaaaaab"
T="aaab"
4.3    串的模式匹配算法—BF算法

## 原课件第 54 页 [DS-CH04-S054]

第4学时

## 原课件第 55 页 [DS-CH04-S055]

KMP算法（特点：速度快）
① KMP算法设计思想
② KMP算法的推导过程
③ KMP算法的实现 （关键技术:计算next[j]）
④ KMP算法的时间复杂度

## 原课件第 56 页 [DS-CH04-S056]

Int Index (SString S, SString T, int pos) {
i=pos;      j=1;
while ( i<=S[0] && j<=T[0] ) {
if (S[i] = = T[j] ) {++i, ++j}
else {i=i-j+2; j=1;}
}//while
if(j>T[0]) return i-T[0];
else return 0;
}//Index
4.3    串的模式匹配算法—KMP算法
Int Index_KMP (SString S, SString T, int pos) {
i=pos;      j=1;
while ( i<=S[0] && j<=T[0] ) {
if (j==0|| S[i] = = T[j] ) {++i, ++j}
else   { j=next[j]; }
}
if(j>T[0])     return i-T[0];
else return0;
}//Index_KMP
两个算法比较

## 原课件第 57 页 [DS-CH04-S057]

能否利用已经部分匹配的结果而加快模式串的滑动速度？要滑动到哪里？
能！而且主串S的指针i不必回溯！j回溯到k（next[j]）,加快T的滑动速度。
例：
① KMP算法设计思想
S=‘a b a b c a b c a c b a b’
T=‘a b c a c’
S=‘a b a b c a b c a c b a b’
T=‘a b c a c’
S=‘a b a b c a b c a c b a b’
T=‘a b c a c’
最后j>T[0],匹配成功，返回值应为i=6
KMP算法只比较了3趟，BF算法比较了6趟。
需要讨论两个问题：
① 如何“记忆”部分匹配结果？
② 如何由“记忆”结果计算出主串S第i个字符应该与模式T中哪个字符再比较？即确定模式T中的新比较起点k（next[j]）.
i
i
i
k
k
a b a
a b c
4.3    串的模式匹配算法—KMP算法
j
j
i
j
i

## 原课件第 58 页 [DS-CH04-S058]

第一步:先把模式T所有可能的失配点j所对应的next[j]计算出来；
第二步: 执行定位函数index_kmp （与BF算法模块非常相似）
KMP算法的实现
Int Index_KMP (SString S, SString T, int pos) {
i=pos;      j=1;
while ( i<=S[0] && j<=T[0] ) {
if (j==0|| S[i] = = T[j] ) {++i, ++j}   //不失配则继续比较后续字符
else   { j=next[j]; }     // S的i指针不回溯，从T的k位置开始匹配
}
if(j>T[0])     return i-T[0];  //子串结束，说明匹配成功
else return0;
}//Index_KMP
4.3    串的模式匹配算法—KMP算法
注意：求next数组，也需要一个函数来实现，get_next(SString T,int next[])，见课本p83
T=“ababac”  next[j]= 0  1  1   2  3   2    next[j]只和T有关，和S无关。

## 原课件第 59 页 [DS-CH04-S059]

比较j=2时失败,next[j]?
① KMP算法设计思想—next[j]?
4.3    串的模式匹配算法—KMP算法
S=‘…a c d b c s b c f c b a b…’
T=‘a b c a c’
i
j
T=‘a b c a c’
S=‘….c b c a a s b c f c b a b….’
T=‘a b c a c’
j
i
S=‘….c b c a a s b c f c b a b….’
比较j=1时失败,next[j]?
Int Index_KMP (SString S, SString T, int pos) {
i=pos;      j=1;
while ( i<=S[0] && j<=T[0] ) {
if (j==0|| S[i] = = T[j] ) {++i, ++j}
else   { j=next[j]; }
}
if(j>T[0])     return i-T[0];
else return0;
}//Index_KMP

## 原课件第 60 页 [DS-CH04-S060]

① KMP算法设计思想—next[j]?
4.3    串的模式匹配算法—KMP算法
S=‘……a b a c c s b c f c b a b…..’
T=‘a b c a c’
j
T=‘a b c a c’
i
比较j=3时失败,next[j]?
S=‘……a a b c c s b c f c b a b…..’
T=‘a a c a c’
j
T=‘a a c a c’
i
比较j=3时失败,next[j]?
Int Index_KMP (SString S, SString T, int pos) {
i=pos;      j=1;
while ( i<=S[0] && j<=T[0] ) {
if (j==0|| S[i] = = T[j] ) {++i, ++j}
else   { j=next[j]; }
}
if(j>T[0])     return i-T[0];
else return0;
}//Index_KMP

## 原课件第 61 页 [DS-CH04-S061]

① KMP算法设计思想—next[j]?
4.3    串的模式匹配算法—KMP算法
S=‘a b c b c s b c f c b a b’
T=‘a b c a c’
j
T=‘a b c a c’
i
比较j=4时失败,next[j]?
S=‘a b a b c s b c f c b a b’
T=‘a b a a c’
j
T=‘a b a a c’
i
比较j=4时失败,next[j]?
S=‘a a a b c s b c f c b a b’
T=‘a a a a c’
j
T=‘a a a a c’
i
比较j=4时失败,next[j]?

## 原课件第 62 页 [DS-CH04-S062]

① KMP算法设计思想—next[j]?
4.3    串的模式匹配算法—KMP算法
S=‘a b c c a s b c f c b a b’
T=‘a b c c c’
j
T=‘a b c c c’
i
比较j=5时失败,next[j]?
S=‘a b c a a s b c f c b a b’
T=‘a b c a c’
j
T=‘a b c a c’
i
S=‘a b a b s b c f c b a b’
T=‘a b a b c’
j
T=‘a b a b c’
i
S=‘a a a a a b c f c b a b’
T=‘a a a a c’
j
T=‘a a a a c’
i
next[ j ]＝
0        当j＝1时
max { k |1<k<j 且‘T_{1}…T_{k-1}’=‘T_{j}_{-(k-1)} …T_{j-1}’ }
1       其他情况

## 原课件第 63 页 [DS-CH04-S063]

怎样计算模式T所有可能的失配点 j 所对应的 next[j]？
例：模 式 串  T： a  b   a  a   b  c   a  c
可能失配位 j： 1  2   3  4   5  6   7  8
新匹配位  next[j] :
next[ j ]＝
0        当j＝1时
max { k |1<k<j 且‘T_{1}…T_{k-1}’=‘T_{j}_{-(k-1)} …T_{j-1}’ }
1       其他情况
0
1
1
2
2
3
1
2
讨论：
j=1时, next[ j ]≡ 0；因为属于“j=1”;
j=2时, next[ j ]≡ 1；因为属于“其他情况”；
刚才已归纳：
j=3时, k={2}，只需查看‘T_{1}’ ≠ ‘T_{2}’；
j=4时, 1<k<j ,k={2，3}，要查看‘T_{1}’=‘T_{3}’ 和‘T_{1}T_{2}’‘≠ T_{2 }T_{3}’
j=5时, 1<k<j, k={2，3，4}，要查看‘T_{1}’=‘T_{4}’ 、‘T_{1}T_{2}’ ≠‘T_{3}T_{4}’ 和
‘T_{1}T_{2}T_{3}’‘≠ T_{2}T_{3}T_{4}’
以此类推，可得后续next[j]值。

## 原课件第 64 页 [DS-CH04-S064]

第一步:先把模式T所有可能的失配点j所对应的next[j]计算出来；
第二步: 执行定位函数index_kmp （与BF算法模块非常相似）
KMP算法的实现
Int Index_KMP (SString S, SString T, int pos) {
i=pos;      j=1;
while ( i<=S[0] && j<=T[0] ) {
if (j==0|| S[i] = = T[j] ) {++i, ++j}   //不失配则继续比较后续字符
else   { j=next[j]; }     // S的i指针不回溯，从T的k位置开始匹配
}
if(j>T[0])     return i-T[0];  //子串结束，说明匹配成功
else return0;
}//Index_KMP
4.3    串的模式匹配算法—KMP算法
注意：求next数组，也需要一个函数来实现，get_next(SString T,int next[])，见课本p83

## 原课件第 65 页 [DS-CH04-S065]

验证一下：若 T=“abcac”next[j]=01112
S=‘a b a b c a b c a c b a b’
T=‘a b c a c’
S=‘a b a b c a b c a c b a b’
T=‘a b c a c’
S=‘a b a b c a b c a c b a b’
T=‘a b c a c’
匹配成功，的返回值应为i=6
i
i
i
k
k
a b a
a b c
4.3    串的模式匹配算法—KMP算法
j
j
i
j
i

## 原课件第 66 页 [DS-CH04-S066]

① KMP算法设计思想
KMP三人发现模式串T可能存在这样的现象：
4.3    串的模式匹配算法—KMP算法
S=‘a b a c b a c b a c c b a b’
T=‘a c b a c c’
j
i
红色和绿色两块相等，红色块又和蓝色块相等，那么就可以让蓝色块滑动到和绿色块对齐，继续比较。如下图：
S=‘a b a b a c b a c c b a b’
T=‘a c b a c c’

## 原课件第 67 页 [DS-CH04-S067]

② KMP算法的推导过程
抓住部分匹配结果的两个特征：
两式联立可得：‘T_{1}…T_{k-1}’=‘T_{j}_{-(k-1)} …T_{j-1}’
注意：j 为当前已知的失配位置，我们的目标是计算新起点 k，
仅剩一个未知数k，理论上已可解，且k仅与模式串T有关！
则S前i-1～i-(k-1)位＝T的j-1～j-(k-1)位
S=‘a b a c b a c b a c c b a b’
T=‘a c b a c c’
i
k
则T的k-1～1位＝S前i-1～i-(k-1)位
i
k
j
S=‘a b a c b a c b a c c b a b’
T=‘a c b a c c’
刚才是在S的i处和T的第j字符 处失配，K是j回溯到的位置。
设目前应与T的第k字符开始比较
即：S中位置i前面的k-1位字符串=T中的前k-1位
即：S中位置i前面的k-1位字符串=T中j前面的k-1位
4.3    串的模式匹配算法—KMP算法

## 原课件第 68 页 [DS-CH04-S068]

② KMP算法的推导过程(续)：如何计算next[j]
根据模式串T的规律：   ‘T_{1}…T_{k-1}’=‘T_{j}_{-(k-1)} …T_{j-1}’
和已知的当前失配位置j ，可以归纳出计算新起点 k的表达式。
令k = next[ j ]，则
next[ j ]＝
0        当j＝1时
max { k |1<k<j 且‘T_{1}…T_{k-1}’=‘T_{j-(k-1)} …T_{j-1}’ }
1       其他情况
讨论：
① next[ j ]有何意义？
一旦失配，应从模式串T中第next[ j ]个字符开始与S的失配点i 重新匹配!
② next[ j ]怎么求？
后面会举例（参见教材P81）
4.3    串的模式匹配算法—KMP算法

## 原课件第 69 页 [DS-CH04-S069]

② KMP算法的推导过程(续) ：如何计算next[j]
next[ j ]＝
0        当j＝1时
max { k |1<k<j 且‘T_{1}…T_{k-1}’=‘T_{j}_{-(k-1)} …T_{j-1}’ }
1       其他情况
为什么其他情况，next[j]=1?
找不到符合‘T_{1}…T_{k-1}’=‘T_{j}_{-(k-1)} …T_{j-1}’ 这个条件的k，就说明j要回溯到1.
为什么j=1时  next[j]=0 ?
j=1，意思就是第一个字符就匹配失败，下一趟的比较应该让i++，j变成1，为了下一趟是i++，j++同时增加，需要在上一趟时把j=0，然后j++后就会变成1，这时候i也增加了1.
见改进程序KMP
If(j==0 || s[i]==T[j])  {i++  ; j++}
4.3    串的模式匹配算法—KMP算法

## 原课件第 70 页 [DS-CH04-S070]

提问：模式串 P= ‘ababaaab ’的 next 函数值序列为 ________ 。
01123422
求解Next的方法总结：
根据定义的公式的方法：用前缀和后缀的方法，非常简单。
(1) next[1]=0,求next[2]=1;
(2)求后面的next[j]时，把第1位到第j-1位的字符串取出来，求该串的前缀和后缀，前缀后缀最长是j-2，取出最长的相等的前缀和后缀，这个长度加一就是next[j]。
例如：a  b  a  a  b  c  a  c
next[4]=?  前面的串是：aba，前缀和后缀a=a，长度是1，所以next[4]=1+1=2  （最大长度加1）
next[6]=?  前面的串是：abaab，前缀和后缀ab=ab，长度是2，所以next[6]=2+1=3（最大长度加1）
4.3    串的模式匹配算法—KMP算法

## 原课件第 71 页 [DS-CH04-S071]

模式： a a a a b
j：1 2 3 4 5
next[j]：  0 1 2 3 4
S:              a a a b a a a a b
T:              a a a a b
i:               1 2 3 4 5 6 7 8 9
a a a a b
a a a a b
a a a a b
a a a a b
讨论：next [ j ]是否完美无缺？
答：未必，例如当      S=‘a b a a a a b’,T=‘a a a a b’时,仍有多余动作（参见P84改进算法,称为nextval [ j ] ）
4.3    串的模式匹配算法—KMP算法

## 原课件第 72 页 [DS-CH04-S072]

当P_{j}==P_{next[j]}时，则
因为S_{i} != P_{j}，所以 S_{i }!= P_{next[j]}
因此，S_{i }没有必要继续与 P_{next}_{[j]}进行比较，
而应该直接和P_{next}_{[j]}的下一个字符P_{next}_{[next[j]]}
进行比较。
因此，在计算next函数时，
如果出现P_{j}=P_{next}_{[j] }= P_{k}
则next[j]=next[k]=next[next[j]]
修改算法见教材P84 算法4.8
此时效率不高的原因为：
4.3    串的模式匹配算法—KMP算法

## 原课件第 73 页 [DS-CH04-S073]

i                 1   2   3   4     5
模式              a    a   a   a    b
j=Next[i]       0    1   2   3    4
Nextval[i]      0    0   0   0    4
举例：
字符串’ababaaab’ 的 next函数值为________ 。
nextval=？
模式串 P= ‘ abaabcac ’的 next 函数值序列为 ________ 。nextval=？
01122312
01010421
提问：
01123422
01021302
4.3    串的模式匹配算法—KMP算法

## 原课件第 74 页 [DS-CH04-S074]

④ KMP算法的时间复杂度
注意：由于BF算法在一般情况下的时间复杂度也近似于O(n+m),
所以至今仍被采用。
而此时KMP的情况是：由于指针i无须回溯，比较次数仅为n,即使加上计算next[j]时所用的比较次数m，比较总次数也仅为n+m=O(n＋m)，大大快于BF算法。
回顾BF的最恶劣情况：S与T之间存在大量的部分匹配，比较总次数为： (n-m+1)*m＝O(n*m)
KMP算法的用途：因为主串指针i不必回溯，所以从外存输入文件时可以做到边读入边查找，“流式”作业！
4.3    串的模式匹配算法—KMP算法
KMP算法的空间效率思考：额外引入一个数组next，需要m个空间。空间效率是O（m）
用空间，换时间。

## 原课件第 75 页 [DS-CH04-S075]

熟悉串的基本操作的定义，并能利用这些基本操作来实现串的其它各种操作的方法。
2.了解串的各种存储结构的特点及其适用场合。信息检索、文字编辑、自然语言翻译系统等。
本章小结

## 原课件第 76 页 [DS-CH04-S076]
