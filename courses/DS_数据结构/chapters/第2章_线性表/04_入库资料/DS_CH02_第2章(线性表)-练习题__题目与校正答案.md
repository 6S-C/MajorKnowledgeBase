# 第2章(线性表)-练习题：题目与校正答案

来源原文件：第2章(线性表)-练习题；原文件保存在00_原始资料。原附解不直接入库，已单独保存并校正。

## 题目原文（移除原附解）

# 第2章(线性表)-练习题

来源：第2章(线性表)-练习题.docx

1、 试描述头指针、头结点、开始结点的区别、并说明头指针和头结点的作用。

2、 何时选用顺序表、何时选用链表作为线性表的存储结构为宜?

3、 在顺序表中插入和删除一个结点需平均移动多少个结点?具体的移动次数取决于哪两个因素?

4、 为什么在单循环链表中设置尾指针比设置头指针更好?

5、 在单链表、双链表和单循环链表中，若仅知道指针p指向某结点，不知道头指针，能否将结点*p从相应的链表中删去?若可以，其时间复杂度各为多少?

6、下述算法的功能是什么?

LinkList Demo(LinkList L){       // L是无头结点单链表

ListNode *Q,*P;

if(L&&L->next){

Q=L;L=L->next;P=L;

while (P->next) P=P->next;

P->next=Q; Q->next=NULL;

}

return L;

}// Demo

7、不带头结点的单链表head为空的判定条件是（ ）。

A、head=NULL           B、head->next=NULL

C、head->next=head     D、head!=NULL

8、在双向链表指针p的结点前插入一个指针q的结点操作是（    ）。

A.  p->Llink=q;q->Rlink=p;p->Llink->Rlink=q;q->Llink=q；

B.  p->Llink=q;p->Llink->Rlink=q;q->Rlink=p;q->Llink=p->Llink;

C.  q->Rlink=p;q->Llink=p->Llink;p->Llink->Rlink=q;p->Llink=q;

D.  q->Llink=p->Llink;q->Rlink=q;p->Llink=q;p->Llink=q;

9、在一单链表中，已知q所指的结点是p所指结点的前驱结点，若在q和p之间插入s结点，则执行（ ）。

A、s->next=p->next;p->next=s;		B、p->next=s->next;s->next=p;

C、q->next=s;s->next=p;			D、p->next=s;s->next=q;

10、在一个单链表中，若p所指的结点不是最后结点，在p之后插入s结点，则执行（ ）。

A、s->next=p;p->next=s;					B、s->next=p->next;p->next=s;

C、s->next=p->next;p=s;				D、p->next=s;s->next=p;

11、在一个单链表中，若删除p所指结点的后续结点，则执行（ ）。

A、p->next=p->next->next;B、p=p->next;p->next=p->next->next;

C、p->next=p->next;			D、p=p->next->next;

12、从一个具有n个结点的单链表中查找其值等于x结点时，在查找成功的情况下，需要平均比较（ ）个结点？

A、n		B、n/	2C、(n-1)/2			D、(n+1)/2

13、在一个具有n个结点的有序单链表中插入一个新结点并仍然有序的时间复杂度是（ ）。

A、O(1)			B、O(n)	C、O(n	^{2})	D、O(nlog	_{2}n)

14、给定有n个元素的向量，建立一个有序单链表的时间复杂度是（ ）。

A、O(1)		B、O(n)			C、O(n^{2})	D、O(nlog	_{2}n)

15、带有一个头结点的单链表head为空的条件是              .

16、对于一个具有n个结点的单链表，在已知p所指结点之后插入一个新结点的时间复杂度为          ；在给定值为x的结点后插入一个新结点的时间复杂度是            。

17、以下程序的功能是实现带附加头结点的单链表数据结点逆序连接，请填空完善之。

void reverse(pointer h)

/* h为附加头结点指针；类型pointer同算法设计第3题*/

{ pointer p,q;

p=h->next;  h->next=NULL;

while((1))

{q=p; p=p->next; q->next=h->next; h->next=(2); }

}

18、设顺序表L是一个非递减有序表，试写一算法，将x插入L中，并使L仍是一个有序表。

19、设顺序表L是一个递减有序表，试写一算法，将x插入其后仍保持L的有序性。

20、写一算法在单链表上实现线性表的ListLength(L)运算。

21、已知L1和L2分别指向两个单链表的头结点，且已知其长度分别为m和n。试写一算法将这两个链表连接在一起，请分析你的算法的时间复杂度。

22、删除带头结点单链表L中的元素x。

23、已知：A=(a_{1},a_{2},……,a_{n-1},a_{n})  B=(b_{1},b_{2},……,b_{n-1},b_{n})均为顺序表，试编写一个比较A、B大小的算法。

24、删除有序表中所有其值大于minval且小于maxval的数据元素。

25、双向循环链表的结点中，增加一个访问频度的数据域freq，编写算法实现LOCATE(L,x)。

26、写一算法将单链表中值重复的结点删除，使所得结果表中各结点值均不相同。

27、试编写在带头结点的单链表中删除（一个）最小值结点的（高效）算法。

void  delete（Linklist  &L）

28、已知非空线性链表由list指出，链结点的构造为（data,link）。请写一算法，将链表中数据域值最小的那个链结点移到链表的最前面。要求：不得额外申请新的链结点。

29、已知p指向双向循环链表中的一个结点，其结点结构为data、llink、rlink三个域，写出算法change(p),交换p所指向的结点和它的前缀结点的顺序。

30、已知递增有序的单链表A,B分别存储了一个集合，请设计算法以求出两个集合A和B 的差集A-B（即仅由在A中出现而不在B中出现的元素所构成的集合），并以同样的形式存储，同时返回该集合的元素个数。

31、两个整数序列A=a1,a2,a3,…,am和B=b1,b2,b3,…,bn已经存入两个单链表中，设计一个算法，判断序列B是否是序列A的子序列。

32、已知L为没有头结点的单链表中第一个结点的指针，每个结点数据域存放一个字符，该字符可能是英文字母字符或数字字符或其它字符，编写算法构造三个以带头结点的单循环链表表示的线性表，使每个表中只含同一类字符。（要求用最少的时间和最少的空间）

33、在一个非递减有序的线性表中，有数值相同的元素存在。若存储方式为单链表，设计算法去掉数值相同的元素，使表中不再有重复的元素。例如：（7，10，10，21，30，42，42，42，51，70）将变作（7，10，21，30，42，51，70），分析算法的时间复杂度。

34、请写一个算法将顺序存储结构的线性表（a_{1}...a_{n}）逆置为(a_{n}...a_{1})。

类似本题的另外叙述有：

(1) 设有一带头结点的单链表,编程将链表颠倒过来.要求不用另外的数组或结点完成.

(2) 设有一个带头结点的单向链表，数据项递减有序。写一算法，重新排列链表，使数据项递增有序，要求算法时间复杂度为O（n）。（注：用程序实现）

(3) 试编写求倒排循环链表元素的算法。

(4) 请设计算法将不带头结点的单链表就地逆置。

(5) 试编写算法 ，将不设表头结点的、不循环的单向链表就地逆转。

(6) 有一个单链表L（至少有1个结点），其头结点指针为head，编写一个过程将L逆置，即最后一个结点变成第一个结点，原来倒数第二个结点变成第二个结点，如此等等。


---

# 第2章(线性表)-练习题：答案与解析

状态：Codex辅助编写并逐题核对的学习参考答案，不是教师公布的标准答案。依据本次课程材料和算法推导；存在题设歧义时已明确说明。原附解有错误时以本文件的校正说明为准。日期：2026-10-25。


## 1．头指针、头结点与开始结点

头指针是指针变量；有头结点时指向头结点，无头结点时指向第一个数据结点。头结点是不计入数据长度的辅助结点。开始结点是第一个数据结点。使首元素插删与一般位置一致的是“设置头结点”，原附解写成“设置头指针”不准确。

## 2．顺序表与链表的选择

按下标访问多、长度较稳定、缓存局部性重要时优先顺序表；插删多、能取得前驱或目标结点、容量变化较大时可选链表。无序按值查找二者一般都是Θ(n)，有序顺序表可二分Θ(log n)，普通单链表不能直接获得这种随机访问优势。链表删除尾结点不因存在尾指针就必然Θ(1)，仍可能需找前驱。

## 3．顺序表插删平均移动次数

原长度n，插入位置i=1…n+1时移动n-i+1个元素，均匀平均n/2；删除位置i=1…n时移动n-i个元素，平均(n-1)/2。依赖表长、操作位置以及位置概率分布。

## 4．单循环链表为何常设尾指针

无头结点时首元素为rear->next，尾为rear；有头结点时头结点为rear->next，非空表首数据为rear->next->next。定位首尾均Θ(1)，仅存头指针找尾一般Θ(n)。空表的表示必须单独约定。

## 5．仅知p，能否删除p所指结点

- 普通单链表：无法普遍找到前驱，因此不能保证删除物理结点p。若p不是末结点，可把后继数据复制到p再删除后继，Θ(1)地删除p原来的逻辑元素，但实际释放的不是p，其他外部引用可能受影响。
- 双链表：若前后链接均有效且不需修改无法取得的外部首尾指针，可Θ(1)删除。非循环表首尾和外部句柄需额外处理，不能无条件成立。
- 单循环链表：沿环找到p的前驱需Θ(n)，然后改链Θ(1)。删除单元素环或被外部头/尾引用的p仍需更新外部句柄。

## 6．Demo的功能

无头单链表左循环移位一个元素：原首结点摘下接至尾部，原第二结点成为首结点。空表、单元素不变；Θ(n)时间、Θ(1)辅助空间。

## 7—17．选择与填空

| 题号 | 答案 | 说明 |
|---|---|---|
| 7 | A | 实际代码应写head==NULL，题面单等号是判定式排版 |
| 8 | C | 插前需修改4条链接，原p前驱必须存在 |
| 9 | C | q是p前驱，插入s到两者之间 |
| 10 | B | s.next=p.next；p.next=s |
| 11 | A | 还应先保存后继指针再释放内存 |
| 12 | D | 成功且各目标等概率，平均(n+1)/2 |
| 13 | B | 寻找位置Θ(n)，改链接Θ(1) |
| 14 | 通常C；算法未限定时有歧义 | 逐个有序插入最坏Θ(n²)；先归并排序再建链可Θ(n log n)，若问更优实现则D也成立 |
| 15 | head->next==NULL | 有附加头结点 |
| 16 | Θ(1)；Θ(n) | 已知p与需先按值定位的区别 |
| 17 | (1) p!=NULL；(2) q | 每次摘下原链首结点，头插到新链 |

## 算法代码约定

下列为C++17参考实现，与原题使用引用的风格一致。普通单链表默认有附加头结点，另有明确说明的除外。结点以new分配、delete释放；若改写C须统一为malloc/free。要求输入链结构有效、不同链不共享数据结点；下标从0开始。

```cpp
struct Node { int data; Node* next = nullptr; };
struct DNode { int data = 0; unsigned freq = 0;
              DNode* prior = nullptr; DNode* next = nullptr; };
struct CNode { char data = 0; CNode* next = nullptr; };
struct SeqList { int data[1024]; int length = 0; };
// 使用<vector>、<array>、<algorithm>、<cstddef>；std::vector/std::array为标准容器。
```

## 18．非递减顺序表插入x

先找第一个≥x的位置，后移元素；允许相等值。最坏Θ(n)时间、Θ(1)辅助空间，满表返回false。


```cpp
bool insertIncreasing(SeqList& L, int x) {
    if (L.length == 1024) return false;
    int i = 0;
    while (i < L.length && L.data[i] < x) ++i;
    for (int j = L.length; j > i; --j) L.data[j] = L.data[j-1];
    L.data[i] = x; ++L.length; return true;
}
```

## 19．非递增顺序表插入x

先找第一个≤x的位置。最坏Θ(n)时间、Θ(1)辅助空间；若题意严格递减且禁止重复，还需遇相等时拒绝插入。


```cpp
bool insertDecreasing(SeqList& L, int x) {
    if (L.length == 1024) return false;
    int i = 0;
    while (i < L.length && L.data[i] > x) ++i;
    for (int j = L.length; j > i; --j) L.data[j] = L.data[j-1];
    L.data[i] = x; ++L.length; return true;
}
```

## 20．单链表长度

不计头结点；空表返回0。Θ(n)时间、Θ(1)辅助空间。


```cpp
std::size_t listLength(const Node* head) { // head is a dummy node
    std::size_t n = 0;
    for (auto p = head->next; p; p = p->next) ++n;
    return n;
}
```

## 21．连接L1、L2

找到L1尾部接上L2数据链；将L2置空，避免两个表共享并重复释放。Θ(m+1)时间、Θ(1)辅助空间，已有尾指针则可Θ(1)。


```cpp
void concatenate(Node* head1, Node* head2) { // disjoint lists, distinct dummy nodes
    auto p = head1;
    while (p->next) p = p->next;
    p->next = head2->next;
    head2->next = nullptr; // transfer ownership; head2 remains an empty list
}
```

## 22．删除所有值为x的结点

连续命中时前驱不后移。原附解if(p->data=x)把比较写成赋值，必须改==。Θ(n)时间、Θ(1)辅助空间。


```cpp
void deleteAll(Node* head, int x) {
    auto pre = head;
    while (pre->next) {
        auto p = pre->next;
        if (p->data == x) { pre->next = p->next; delete p; }
        else pre = p;
    }
}
```

## 23．按字典序比较顺序表

返回-1/0/1。先比较首个不同元素，公共前缀相同时短表较小。Θ(min(m,n)+1)时间、Θ(1)辅助空间，不改变原表。


```cpp
int compareLists(const std::vector<int>& A, const std::vector<int>& B) {
    std::size_t i = 0;
    while (i < A.size() && i < B.size()) {
        if (A[i] < B[i]) return -1;
        if (A[i] > B[i]) return 1;
        ++i;
    }
    return (A.size() > B.size()) - (A.size() < B.size());
}
```

## 24．删除有序表开区间(minval,maxval)

本实现用非递减单链表，保留等于两端的元素。空表及minval≥maxval均安全。最坏Θ(n)时间、Θ(1)辅助空间。


```cpp
void deleteOpenInterval(Node* head, int minval, int maxval) {
    if (minval >= maxval) return;
    auto pre = head;
    while (pre->next && pre->next->data <= minval) pre = pre->next;
    while (pre->next && pre->next->data < maxval) {
        auto p = pre->next; pre->next = p->next; delete p;
    }
}
```

## 25．按访问频度调整双向循环链表LOCATE

初始freq非递增，命中后先++freq，再前移至最后一个freq≥新freq的结点之后；同频保持已有相对位置。不命中返回nullptr。原附解漏写了++freq。Θ(n)时间、Θ(1)空间；计数器需避免溢出。


```cpp
DNode* locate(DNode* head, int x) { // dummy-head ring sorted by nonincreasing freq
    auto p = head->next;
    while (p != head && p->data != x) p = p->next;
    if (p == head) return nullptr;
    ++p->freq;
    auto q = p->prior;
    while (q != head && q->freq < p->freq) q = q->prior;
    if (q != p->prior) {
        p->prior->next = p->next; p->next->prior = p->prior;
        p->next = q->next; p->prior = q;
        q->next->prior = p; q->next = p;
    }
    return p;
}
```

## 26．无序单链表去重

保留每个值首次出现的结点；与其后的元素逐一比较，补齐原附解“略”的算法。最坏Θ(n²)时间、Θ(1)辅助空间；哈希可用额外Θ(n)空间换期望Θ(n)时间。


```cpp
void removeDuplicates(Node* head) { // unsorted, preserve first occurrence
    for (auto p = head->next; p; p = p->next) {
        auto pre = p;
        while (pre->next) {
            auto q = pre->next;
            if (q->data == p->data) { pre->next = q->next; delete q; }
            else pre = q;
        }
    }
}
```

## 27．删除一个最小值结点

删除第一个最小值，空表返回false。Θ(n)时间、Θ(1)空间。


```cpp
bool deleteMinimum(Node* head) { // delete the first minimum, dummy head
    if (!head->next) return false;
    auto minpre = head;
    for (auto pre = head; pre->next; pre = pre->next)
        if (pre->next->data < minpre->next->data) minpre = pre;
    auto p = minpre->next; minpre->next = p->next; delete p;
    return true;
}
```

## 28．最小值结点移到最前

这里明确采用无头结点表示，first引用能更新调用者的首指针；不申请新结点。保留第一个最小值。Θ(n)时间、Θ(1)空间；有头结点时传head->next。


```cpp
void moveMinimumFront(Node*& first) { // NO dummy head
    if (!first) return;
    Node* minpre = nullptr;
    Node* minnode = first;
    for (auto pre = first; pre->next; pre = pre->next)
        if (pre->next->data < minnode->data) {
            minpre = pre; minnode = pre->next;
        }
    if (!minpre) return;
    minpre->next = minnode->next;
    minnode->next = first; first = minnode;
}
```

## 29．与前驱交换双向循环链表结点

分两种表示。带头结点版本不交换辅助头结点，第一个数据结点无可交换的数据前驱。无头版本1/2个结点的环链接本身无需改变，但外部线性起点如需随交换移动，由调用者更新；≥3个结点修改6条链接。两者Θ(1)时间和空间。


```cpp
bool exchangeWithPrevious(DNode* head, DNode* p) { // dummy-head double ring
    if (p == head || p->prior == head) return false;
    auto q = p->prior;
    auto a = q->prior; auto b = p->next;
    a->next = p; p->prior = a;
    p->next = q; q->prior = p;
    q->next = b; b->prior = q;
    return true;
}

void exchangeBareRing(DNode* p) { // no dummy; caller updates any external start marker
    auto q = p->prior;
    if (q == p || p->next == q) return; // rings of size 1 or 2 have unchanged links
    auto a = q->prior; auto b = p->next;
    a->next = p; p->prior = a;
    p->next = q; q->prior = p;
    q->next = b; b->prior = q;
}
```

## 30．有序集合差A-B并计数

A、B元素各不重复，均带头结点；原地删除A中共有元素，B不变，返回剩余数。即使B先到尾也继续计数。原附解*n++会移动指针而非增加计数，且漏算A尾部。Θ(m+n)时间、Θ(1)辅助空间。


```cpp
std::size_t difference(Node* A, const Node* B) { // sorted sets with dummy heads
    auto pre = A; auto q = B->next;
    std::size_t count = 0;
    while (pre->next) {
        auto p = pre->next;
        while (q && q->data < p->data) q = q->next;
        if (q && q->data == p->data) { pre->next = p->next; delete p; }
        else { ++count; pre = p; }
    }
    return count;
}
```

## 31．B是否是A的子序列

原附解实际解的是“连续子表”，下面同时给两种定义。连续匹配最坏O(mn+m+1)，空B为真；允许跳过元素的数学子序列用双指针O(m+n+1)。两者Θ(1)空间，A、B为无头结点首指针。例A=(1,2,3), B=(1,3)，连续为假、非连续为真。


```cpp
bool containsContiguous(const Node* A, const Node* B) { // no dummy heads
    if (!B) return true;
    for (auto start = A; start; start = start->next) {
        auto p = start; auto q = B;
        while (p && q && p->data == q->data) { p = p->next; q = q->next; }
        if (!q) return true;
    }
    return false;
}

bool containsSubsequence(const Node* A, const Node* B) { // gaps allowed
    while (A && B) {
        if (A->data == B->data) B = B->next;
        A = A->next;
    }
    return B == nullptr;
}
```

## 32．字符单链表拆成三个循环链表

输入无头结点，输出分别为英文字母、数字、其他字符的带头结点单循环链表。复用所有数据结点，只增加3个必须的头结点；尾插保留原相对顺序，原L最终为nullptr。Θ(n)时间、Θ(1)辅助空间。


```cpp
std::array<CNode*,3> splitCharacters(CNode*& L) { // input without dummy head
    std::array<CNode*,3> head{new CNode{}, new CNode{}, new CNode{}};
    auto tail = head;
    for (auto h : head) h->next = h;
    while (L) {
        auto p = L; L = L->next;
        char c = p->data;
        int k = ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? 0
              : ((c >= '0' && c <= '9') ? 1 : 2);
        p->next = head[k]; tail[k]->next = p; tail[k] = p;
    }
    return head; // order: letters, digits, other; each is a dummy-head ring
}
```

## 33．非递减链表去重

相邻相等就删除后继，不后移当前指针；兼容空表和末尾连续重复。Θ(n)时间、Θ(1)辅助空间。


```cpp
void removeSortedDuplicates(Node* head) {
    auto p = head->next;
    while (p && p->next) {
        if (p->data == p->next->data) {
            auto q = p->next; p->next = q->next; delete q;
        } else p = p->next;
    }
}
```

## 34．顺序表与单链表各类逆置

顺序表只交换前半部分；原代码对n=0的整数除法边界不安全。带头结点、无头结点、带头循环、无头循环四种链表实现见下。全部Θ(n)时间、Θ(1)辅助空间且不新建结点。原题变式(1)(2)(6)用reverseDummy（(6)若head为数据首指针则reverseBare），(4)(5)用reverseBare，(3)按有无头结点选择循环版本；递减变递增即逆置，重复值保留。


```cpp
void reverseArray(std::vector<int>& A) {
    for (std::size_t i = 0; i < A.size()/2; ++i)
        std::swap(A[i], A[A.size()-1-i]);
}

void reverseBare(Node*& first) {
    Node* prev = nullptr;
    while (first) {
        auto next = first->next; first->next = prev; prev = first; first = next;
    }
    first = prev;
}

void reverseDummy(Node* head) { reverseBare(head->next); }

void reverseDummyRing(Node* head) { // head itself is never reversed into data
    Node* prev = head; auto p = head->next;
    while (p != head) {
        auto next = p->next; p->next = prev; prev = p; p = next;
    }
    head->next = prev;
}

void reverseBareRing(Node*& first) {
    if (!first) return;
    auto oldfirst = first; auto p = first->next; auto prev = first;
    while (p != oldfirst) {
        auto next = p->next; p->next = prev; prev = p; p = next;
    }
    oldfirst->next = prev; first = prev;
}
```
