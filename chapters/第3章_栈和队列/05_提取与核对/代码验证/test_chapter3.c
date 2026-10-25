#include "chapter3_reference.h"
static void test_bracket_ring(const char* s, bool expected) {
 CharNode h={0,NULL};h.link=&h;CharNode* tail=&h;
 for(size_t i=0;s[i];++i){CharNode*p=(CharNode*)malloc(sizeof(*p));assert(p);p->ch=s[i];p->link=&h;tail->link=p;tail=p;}
 assert(matchBracketRing(&h)==expected);
 CharNode* p=h.link;while(p!=&h){CharNode*q=p;p=p->link;free(q);}
}
int main(void){
 IntStack s={{0},0};int x;
 assert(!sPop(&s,&x));assert(stackSizeByOperations(s)==0);clearStack(&s);
 for(int i=0;i<DS_CAP;++i){assert(sPush(&s,i));}
 assert(!sPush(&s,5));assert(stackSizeByOperations(s)==DS_CAP);assert(s.top==DS_CAP);clearStack(&s);assert(sEmpty(&s));
 for(int i=1;i<=4;++i){assert(sPush(&s,i));}
 reverseStack(&s);for(int i=1;i<=4;++i){assert(sPop(&s,&x));assert(x==i);}
 for(int i=1;i<=4;++i){assert(sPush(&s,i));}
 IntStack copy={{0},0};assert(copyStack(&s,&copy));for(int i=4;i>=1;--i){assert(sPop(&s,&x)&&x==i);assert(sPop(&copy,&x)&&x==i);}
 int input[]={2,1,2,3,2};for(size_t i=0;i<5;++i)assert(sPush(&s,input[i]));removeStackValue(&s,2);assert(sPop(&s,&x)&&x==3);assert(sPop(&s,&x)&&x==1);assert(sEmpty(&s));
 TwoStackQueue q={0};assert(twoStackEmpty(&q));assert(!twoStackDequeue(&q,&x));for(int i=0;i<DS_CAP+5;++i)assert(twoStackEnqueue(&q,i));for(int i=0;i<DS_CAP+5;++i){assert(twoStackDequeue(&q,&x));assert(x==i);}assert(twoStackEmpty(&q));
 /* Full input plus nonempty output rejects without overwriting queued values. */
 for(int i=0;i<DS_CAP*2;++i){assert(twoStackEnqueue(&q,i));}
 assert(!twoStackEnqueue(&q,9999));for(int i=0;i<DS_CAP*2;++i){assert(twoStackDequeue(&q,&x));assert(x==i);}
 QNode* rear=newRingQueue();assert(!ringDequeue(&rear,&x));for(int i=0;i<20;++i)ringEnqueue(&rear,i);for(int i=0;i<20;++i){assert(ringDequeue(&rear,&x));assert(x==i);}assert(rear->next==rear);ringEnqueue(&rear,5);assert(ringDequeue(&rear,&x)&&x==5);free(rear);
 for(int n=0;n<50;++n){IntQueue a={0},b={0};for(int i=0;i<n;++i)qPush(&a,i);assert(linkedQueueCount(&a)==(size_t)n);copyQueue(&a,&b);assert(reverseQueue(&a));for(int i=0;i<n;++i){assert(qPop(&a,&x)&&x==n-1-i);assert(qPop(&b,&x)&&x==i);}assert(qEmpty(&a)&&qEmpty(&b));}
 IntQueue large={0};for(int i=0;i<DS_CAP+1;++i)qPush(&large,i);assert(!reverseQueue(&large));for(int i=0;i<DS_CAP+1;++i)assert(qPop(&large,&x)&&x==i);
 assert(legalOperations("IOIIOIOO"));assert(!legalOperations("IOOIOIIO"));assert(!legalOperations("IIIOIOIO"));assert(legalOperations("IIIOOIOO"));assert(!legalOperations("IXO"));assert(legalOperations(""));
 assert(matchParentheses(""));assert(matchParentheses("a+(b*(c))"));assert(!matchParentheses(")("));assert(!matchParentheses("(()"));
 assert(matchHashExpression("(a)#",4));assert(matchHashExpression("#",1));assert(!matchHashExpression("(a)",3));assert(!matchHashExpression(")#",2));
 test_bracket_ring("",true);test_bracket_ring("{a+[b*(c)]}",true);test_bracket_ring("([)]",false);test_bracket_ring(")",false);test_bracket_ring("((",false);
 int a[]={-9,-4,-10};assert(maxRecursive(a,3)==-4);assert(maxRecursive(a,1)==-9);
 for(unsigned m=0;m<=3;++m)for(unsigned n=0;n<=4;++n){unsigned long long expected=m==0?n+1:m==1?n+2:m==2?2*n+3:(1ULL<<(n+3))-3;assert(ackermann(m,n)==expected);}
 FILE* output=tmpfile();assert(output);int sequence[]={5,-1,-1};processInput(sequence,3,output);rewind(output);char buffer[100]={0};assert(fread(buffer,1,99,output)>0);assert(strcmp(buffer,"5\nstack empty\n")==0);fclose(output);
 IntQueue adt={0};qPush(&adt,1);qPush(&adt,2);reverseQueueADT(&adt);assert(qPop(&adt,&x)&&x==2);assert(qPop(&adt,&x)&&x==1);
 FILE* keyboard=tmpfile();output=tmpfile();assert(keyboard&&output);fputs("7 -1 -1",keyboard);rewind(keyboard);assert(processKeyboard(3,keyboard,output));assert(!processKeyboard(1,keyboard,output));rewind(output);memset(buffer,0,sizeof(buffer));assert(fread(buffer,1,99,output)>0);assert(strcmp(buffer,"7\nstack empty\n")==0);fclose(keyboard);fclose(output);
 puts("PASS: stack/queue capacity, empty/singleton, FIFO, copying, reversal, bracket, recursion and operation-sequence checks");return 0;
}
