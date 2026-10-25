# 第3章(栈和队列)-练习题：题目与校正答案

来源原文件：第3章(栈和队列)-练习题；原文件保存在00_原始资料。原附解不直接入库，已单独保存并校正。

## 题目原文（移除原附解）

# 第3章(栈和队列)-练习题

来源：原始Word文件；只读提取，原文保留。

1. 一个栈的输入序列为1 2 3 4 5，则下列序列中不可能是栈的输出序列的是（    ）。
   A. 2 3 4 1 5     B. 5 4 1 3 2     C. 2 3 1 4 5      D. 1 5 4 3 2

2. 一个栈的输入序列为123…n，若输出序列的第一个元素是n，输出第i（1<=i<=n）个元素是（    ）。
A. 不确定          B. n-i+1          C.  i           D. n-i

3. 若栈采用顺序存储方式存储，现两栈共享空间V[1..m]，top[i]代表第i个栈( i =1,2)栈顶，栈1的底在v[1]，栈2的底在V[m]，则栈满的条件是（    ）。
A. |top[2]-top[1]|=0    B. top[1]+1=top[2]    
C. top[1]+top[2]=m      D. top[1]=top[2]      

4. 栈在（    ）中应用。
A. 递归调用     B. 子程序调用    C. 表达式求值    D. A，Ｂ，Ｃ

5. 执行完下列语句段后，i值为：（    ） 
     int   f(int x)
     { return  ((x>0) ? x* f(x-1):2);}
      int i  ;
      i =f(f(1));
A．2       B. 4        C. 8        D. 无限递归

6. 表达式3* 2^(4+2*2-6*3)-5求值过程中当扫描到6时，对象栈和算符栈为（   ），其中^为乘幂 。
A. 3,2,4,1,1；(*^(+*-     B. 3,2,8；(*^-    
C. 3,2,4,2,2；(*^(-       D. 3,2,8；(*^(-

7. 用链接方式存储的队列，在进行删除运算时（    ）。 
A. 仅修改头指针             B. 仅修改尾指针    
C. 头、尾指针都要修改       D. 头、尾指针可能都要修改

8. 循环队列存储在数组A[0..m]中，则入队时的操作为（    ）。
A. rear=rear+1               B. rear=(rear+1) mod (m-1)
    C. rear=(rear+1) mod m       D. rear=(rear+1)mod(m+1) 

9. 设栈S和队列Q的初始状态为空，元素e1，e2，e3，e4,e5和e6依次通过栈S，一个元素出栈后即进队列Q，若6个元素出队的序列是e2，e4，e3,e6,e5,e1则栈S的容量至少应该是(    )。
A． 6          B. 4          C. 3          D. 2

10．表达式23+((12*3-2)/4+34*5/7)+108/9的后缀表达式是_______。 
11. 一个栈的输入序列是：1，2，3则不可能的栈输出序列是_______。
12、 链栈中为何不设置头结点?
13. 利用两个栈sl,s2模拟一个队列时，如何用栈的运算实现队列的插入，删除以及判队空运算。请简述这些运算的算法思想。
（1）用栈s1和s2模拟一个队列的输入（插入）：设s1和s2容量相等。分以下三种情况讨论：若s1未满，则元素入s1栈；若s1满，s2空，则将s1全部元素退栈，再压入栈s2，之后元素入s1栈；若s1满，s2不空（已有出队列元素），则不能入队。
（2）用栈s1和s2模拟队列出队（删除）：若栈s2不空，退栈，即是队列的出队；若s2为空且s1不空，则将s1栈中全部元素退栈，并依次压入s2中，s2栈顶元素退栈，这就是相当于队列的出队；若栈s1为空并且s2也为空，队列空，不能出队。
（3）判队空：若栈s1为空并且s2也为空，才是队列空。
讨论：s1和s2容量之和是队列的最大容量。其操作是，s1栈满后，全部退栈并压栈入s2（设s1和s2容量相等）。再入栈s1直至s1满。这相当队列元素“入队”完毕。出队时，s2退栈完毕后，s1栈中元素依次退栈到s2，s2退栈完毕，相当于队列中全部元素出队。
    在栈s2不空情况下，若要求入队操作，只要s1不满，就可压入s1中。若在s1满和s2不空状态下要求队列的入队时，按出错处理。

14、设整数序列a1,a2,…,an，给出求解最大值的递归程序。
15、假设以带头结点的循环链表表示队列，并且只设一个指针指向队尾结点，但不设头指针，请写出相应的入队列和出队列算法。
（1）void EnQueue (LinkedList rear, ElemType x)
// rear是带头结点的循环链队列的尾指针，本算法将元素x插入到队尾
{ s= (LinkedList) malloc (sizeof(LNode)); //申请结点空间
  s->data=x;  s->next=rear->next;         //将s结点链入队尾
  rear->next=s;  rear=s;                  //rear指向新队尾
}
（2）void DeQueue (LinkedList  rear)
     // rear是带头结点的循环链队列的尾指针，本算法执行出队操作，操作成功输出队头元素；否则给出出错信息
     { if (rear->next==rear)  { printf(“队空\n”); exit(0);}
       s=rear->next->next;             //s指向队头元素，
       rear->next->next=s->next;       //队头元素出队。
       printf (“出队元素是”，s->data);
       if (s==rear) rear=rear->next;   //空队列
       free(s);	
     }

16、已知Q是一个非空队列，S是一个空栈。仅用队列和栈的ADT函数和少量工作变量，使用C语言编写一个算法，将队列Q中的所有元素逆置。栈的ADT函数有：
makeEmpty(s:stack);               置空栈
push(s:stack;value:datatype);     新元素value进栈
pop(s:stack):datatype;            出栈，返回栈顶值
isEmpty(s:stack):Boolean;         判栈空否
 队列的 ADT函数有：
enqueue(q:queue:value:datatype);  元素value进队
deQueue(q:queue):datatype;        出队列，返回队头值
isEmpty(q:queue):boolean;         判队列空否 
17、设从键盘输入一整数的序列：a1, a2, a3，…，an,试编写算法实现：用栈结构存储输入的整数，当ai≠-1时，将ai进栈；当ai=-1时，输出栈顶整数并出栈。算法应对异常情况（入栈满等）给出相应的信息。
18、假设以I和O分别表示入栈和出栈操作。栈的初态和终态均为空，入栈和出栈的操作序列可表示为仅由I和O组成的序列，称可以操作的序列为合法序列，否则称为非法序列。
  （1）下面所示的序列中哪些是合法的？
         A. IOIIOIOO     B. IOOIOIIO      C. IIIOIOIO     D. IIIOOIOO
  （2）通过对（1）的分析，写出一个算法，判定所给的操作序列是否合法。若合法，返回true，否则返回false（假定被判定的操作序列已存入一维数组中）。
   （2）设被判定的操作序列已存入一维数组A[]中。
       int Judge(char A[])
        //判断字符数组A中的输入输出序列是否是合法序列。如是，返回true，否则返回false。
        {i=0;                //i为下标
         j=k=0;              //j和k分别为I和字母O的的个数
         while(A[i]!=‘\0’) //未到字符数组尾
           { switch(A[i])
              { case‘I’:j++; break;           //入栈次数增1
                case‘O’: k++; if(k>j){ printf(“序列非法\n”)；exit(0);}
               }	
i++; //不论A[i]是‘I’或‘O’，指针i均后移
}//while
         if(j!=k) { printf(“序列非法\n”)；return(false);}
         else { printf(“序列合法\n”)；return(true);}
        }//算法结束
19、设表达式以字符形式已存入数组E[n]中，‘#’为表达式的结束符，试写出判断表达式中括号（‘（’和‘）’）是否配对的C语言描述算法：EXYX(E)。 
(注：算法中可调用栈操作的基本算法。)
20、设计一个算法，判断一个算术表达式中的括号是否配对。算术表达式保存在带头结点的单循环链表中，每个结点有两个域：ch和link，其中ch域为字符类型。
21、请利用两个栈S1和S2来模拟一个队列。已知栈的三个运算定义如下：PUSH(ST,x):元素x入ST栈；POP(ST,x)：ST栈顶元素出栈，赋给变量x；Sempty(ST)：判ST栈是否为空。那么如何利用栈的运算来实现该队列的三个运算：enqueue:插入一个元素入队列； dequeue:删除一个元素出队列；queue_empty：判队列为空。（请写明算法的思想及必要的注释）
(1) int enqueue(stack s1,elemtp x)
//s1是容量为n的栈，栈中元素类型是elemtp。本算法将x入栈，若入栈成功返回1，否则返回0。
{ if(top1==n && !Sempty(s2)) //top1是栈s1的栈顶指针，是全局变量
{ printf(“栈满”);return(0);}//s1满s2非空,这时s1不能再入栈
if(top1==n && Sempty(s2))  //若s2为空，先将s1退栈,元素再压栈到s2
   { while(!Sempty(s1)) { POP(s1,x);PUSH(s2,x);}
 PUSH(s1,x); return(1);  //x入栈，实现了队列元素的入队
}
(2) void dequeue(stack s2,s1)
//s2是输出栈，本算法将s2栈顶元素退栈，实现队列元素的出队
{ if(!Sempty(s2))        //栈s2不空，则直接出队
   { POP(s2,x);   printf(“出队元素为”,x);  }
  else                   //处理s2空栈。
    if(Sempty(s1)) { printf(“队列空”);exit(0);}  //若输入栈也为空，则判定队空
    else                 //先将栈s1倒入s2中，再作出队操作
     { while(!Sempty(s1)) { POP(s1,x);PUSH(s2,x);}
       POP(s2,x);        //s2退栈相当队列出队。
       printf(“出队元素”，x);
     }
 }//结束算法dequue
(3) int queue_empty()
//本算法判用栈s1和s2模拟的队列是否为空
{ if(Sempty(s1)&&Sempty(s2))  return(1);//队列空
  else return(0);                       //队列不空
}//结束算法

---

# 第3章(栈和队列)-练习题：答案与解析

状态：Codex辅助编写并逐题核对的学习参考答案，不是教师公布的标准答案。依据本次课程材料和算法推导；存在题设歧义时已明确说明。原附解有错误时以本文件的校正说明为准。日期：2026-10-25。


## 1—11．选择与填空

| 题号 | 答案 | 推导 |
|---|---|---|
| 1 | B | 输出5、4后栈顶3挡住1，因此5,4,1,3,2不可能 |
| 2 | B | 首出n意味着全体已入栈，之后pᵢ=n-i+1 |
| 3 | B | 两个已占栈顶相邻，即top[1]+1=top[2]，没有空单元 |
| 4 | D | 递归、子程序调用、表达式求值都可使用栈 |
| 5 | B | f(0)=2，f(1)=2，f(2)=4，f(f(1))=4 |
| 6 | D（常见算符优先算法，读入6之前） | 先归约2×2，再归约4+4，操作数栈底到顶3,2,8；含外层哨兵的算符栈为(,*,^,(,-。若“扫描到6”已把6入栈，则还需附加6，选项没有该状态，故题目时点需按“正准备处理6”理解 |
| 7 | D | 删除唯一元素时还需更新尾指针；多元素时通常只改头指针 |
| 8 | D | 数组A[0..m]有m+1个单元，模m+1 |
| 9 | C，3 | 先压e1,e2出e2；压e3,e4出e4,e3；压e5,e6出e6,e5,e1。最大栈深3，且出e4前必须同时保留e1,e3,e4，故不能小于3 |
| 10 | 见下 | 空格分隔多位数，避免点号与小数混淆 |
| 11 | 3,1,2 | 先出3后2挡住1 |

第10题后缀式：

```text
23 12 3 * 2 - 4 / 34 5 * 7 / + + 108 9 / +
```

以原题点号隔数的记法写成`23.12.3*2-4/34.5*7/++108.9/+`也成立。若用数学实数除法，值为949/14≈67.785714；若C整数除法则为67，题目仅问后缀式，不应混淆两种求值规则。

## 12．链栈为何通常不设头结点

在表头入栈和出栈已经是Θ(1)，不设头结点更省一个结点，空栈为top==NULL。但不是“不允许”设置头结点；带头结点链栈也完全可实现，空时head->next==NULL。

## C算法约定与共用接口

以下为C99实现，完整可编译源在本章05_提取与核对/代码验证/chapter3_reference.h。IntStack用1024单元，top为元素个数；IntQueue是不带头结点、具有first和rear的链队列。sPush/sPop和qPop返回是否成功；sEmpty/qEmpty判断空；qPush尾部入队，分配失败终止。真实工程可换为动态栈及可恢复的内存错误处理。

```c
#define DS_CAP 1024
typedef struct { int data[DS_CAP]; size_t top; } IntStack;
typedef struct QNode { int data; struct QNode* next; } QNode;
typedef struct { QNode* first; QNode* rear; } IntQueue;
typedef struct CharNode { char ch; struct CharNode* link; } CharNode;
// 置空：IntStack s={{0},0}; IntQueue q={NULL,NULL};
// sPush(&s,x); sPop(&s,&x); sEmpty(&s);
// qPush(&q,x); qPop(&q,&x); qEmpty(&q);
```

## 13．两栈模拟队列；21．同类题的完整实现

input负责入队，output负责出队；只有output为空时才整体倒栈。队空当且仅当两个栈都空。单次转移Θ(n)，每个元素至多转移一次，摊还Θ(1)。此处两栈各固定DS_CAP，input满且output非空会拒绝入队，即使总容量尚未用完；最大可达到2×DS_CAP，但不保证任意状态都能用完。原附解会在转移时覆盖待入队x，还漏写input未满分支，均已修正。


```c
typedef struct { IntStack input, output; } TwoStackQueue;
static bool twoStackEmpty(const TwoStackQueue* q) {
    return sEmpty(&q->input) && sEmpty(&q->output);
}
static void transfer(IntStack* from, IntStack* to) { /* to must be empty */
    int x;
    while (sPop(from, &x)) { bool ok = sPush(to, x); assert(ok); }
}
static bool twoStackEnqueue(TwoStackQueue* q, int x) {
    if (q->input.top == DS_CAP) {
        if (!sEmpty(&q->output)) return false;
        transfer(&q->input, &q->output);
    }
    return sPush(&q->input, x); /* transfer must not overwrite the new x */
}
static bool twoStackDequeue(TwoStackQueue* q, int* x) {
    if (sEmpty(&q->output)) transfer(&q->input, &q->output);
    return sPop(&q->output, x);
}
```

## 14．递归求整数序列最大值

n≥1，0基下标；先保存一次递归结果，不能在条件和else重复递归，否则原附解可能退化成指数次调用。Θ(n)时间、Θ(n)递归栈空间。空序列应由调用者报告无最大值。


```c
static int maxRecursive(const int a[], size_t n) { /* n >= 1 */
    assert(n > 0);
    if (n == 1) return a[0];
    int previous = maxRecursive(a, n-1); /* exactly ONE recursive call */
    return a[n-1] > previous ? a[n-1] : previous;
}
```

## 15．仅存尾指针的带头循环链队列

空队列rear指向头结点且rear->next==rear，入队、出队均Θ(1)。用QNode**才能更新调用者的rear，原附解的值传递无法正确更新。删最后一个数据结点后rear回到头结点。


```c
/* rear points to the dummy node when empty; dummy == rear->next otherwise. */
static QNode* newRingQueue(void) {
    QNode* h = (QNode*)malloc(sizeof(*h)); if (!h) abort();
    h->next = h; return h;
}
static void ringEnqueue(QNode** rear, int x) {
    QNode* p = (QNode*)malloc(sizeof(*p)); if (!p) abort();
    p->data = x; p->next = (*rear)->next;
    (*rear)->next = p; *rear = p;
}
static bool ringDequeue(QNode** rear, int* x) {
    QNode* h = (*rear)->next;
    if (*rear == h) return false;
    QNode* p = h->next; *x = p->data; h->next = p->next;
    if (p == *rear) *rear = h;
    free(p); return true;
}
```

## 16．用栈ADT逆置队列

队列依次出队入栈，再依次出栈入队。除创建空栈外，只调用入栈、出栈、入队、出队ADT；不访问队列内部结点。Θ(n)时间、Θ(n)所需栈容量，调用前须保证临时栈能容纳整个队列，本例n≤DS_CAP。


```c
static void reverseQueueADT(IntQueue* q) { /* precondition: length(q) <= DS_CAP */
    IntStack s = {{0},0}; int x;
    while (qPop(q, &x)) { bool ok = sPush(&s, x); assert(ok); }
    while (sPop(&s, &x)) qPush(q, x);
}
```

## 17．输入非-1入栈，-1出栈

对每项处理，满栈拒绝本次压入、空栈报告本次失败，继续处理后续项；不越界。第一个函数供已读入数组调用，第二个直接读取n个整数；调用processKeyboard(n,stdin,stdout)即可处理键盘输入，读入失败返回false。Θ(n)时间，容量固定时空间Θ(1)。


```c
static void processInput(const int a[], size_t n, FILE* output) {
    IntStack s = {{0},0}; int x;
    for (size_t i = 0; i < n; ++i) {
        if (a[i] != -1) {
            if (!sPush(&s, a[i])) fprintf(output, "stack full\n");
        } else if (sPop(&s, &x)) fprintf(output, "%d\n", x);
        else fprintf(output, "stack empty\n");
    }
}

static bool processKeyboard(size_t n, FILE* input, FILE* output) {
    IntStack s = {{0},0}; int x, popped;
    for (size_t i = 0; i < n; ++i) {
        if (fscanf(input, "%d", &x) != 1) return false;
        if (x != -1) {
            if (!sPush(&s, x)) fprintf(output, "stack full\n");
        } else if (sPop(&s, &popped)) fprintf(output, "%d\n", popped);
        else fprintf(output, "stack empty\n");
    }
    return true;
}
```

## 18．判断I/O操作序列是否合法

A、D合法，B有前缀出栈多于入栈，C最终仍剩2个元素，非法。所有前缀I数≥O数且最终两者相等；其他字符拒绝。Θ(n)时间、Θ(1)空间。


```c
static bool legalOperations(const char* a) {
    size_t balance = 0;
    for (; *a; ++a) {
        if (*a == 'I') ++balance;
        else if (*a == 'O') {
            if (!balance) return false;
            --balance;
        } else return false;
    }
    return balance == 0;
}
```

## 19．以#结束的表达式圆括号匹配

逐项检查并防止空栈弹出，遇#直接返回栈空结果；最多检查n个字符。原附解while条件使case #永远无法进入，还缺少正常返回；已修正。若n范围内没有#，视为输入格式不合法。Θ(n)时间、Θ(n)栈空间。


```c
static bool matchHashExpression(const char E[], size_t n) {
    char* stack = (char*)malloc(n ? n : 1); if (!stack) abort();
    size_t top = 0;
    for (size_t i = 0; i < n; ++i) {
        if (E[i] == '#') { bool ok = top == 0; free(stack); return ok; }
        if (E[i] == '(') stack[top++] = '(';
        else if (E[i] == ')') {
            if (!top) { free(stack); return false; }
            --top;
        }
    }
    free(stack); return false; /* missing required '#' terminator */
}
```

## 20．带头循环链表表达式的三类括号匹配

终止条件为p==head而不是NULL。左括号入栈，右括号必须匹配栈顶；忽略其他字符，空表达式为真。Θ(n)时间、Θ(n)辅助空间；输入环须正确闭合。


```c
static bool matchBracketRing(const CharNode* head) {
    size_t n = 0;
    for (const CharNode* p = head->link; p != head; p = p->link) ++n;
    char* stack = (char*)malloc(n ? n : 1); if (!stack) abort();
    size_t top = 0; bool ok = true;
    for (const CharNode* p = head->link; p != head; p = p->link) {
        char c = p->ch;
        if (c == '(' || c == '[' || c == '{') stack[top++] = c;
        else if (c == ')' || c == ']' || c == '}') {
            char expected = c == ')' ? '(' : (c == ']' ? '[' : '{');
            if (!top || stack[top-1] != expected) { ok = false; break; }
            --top;
        }
    }
    ok = ok && top == 0; free(stack); return ok;
}
```

## 21．对应代码位置

与第13题相同，完整的enqueue/dequeue/queue_empty代码已在第13题给出，不能在output未空时倒入input，否则会破坏FIFO。
