#ifndef DS_CHAPTER3_REFERENCE_H
#define DS_CHAPTER3_REFERENCE_H
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#define DS_CAP 1024
typedef struct { int data[DS_CAP]; size_t top; } IntStack; /* top == element count */
typedef struct QNode { int data; struct QNode* next; } QNode;
typedef struct { QNode* first; QNode* rear; } IntQueue; /* no dummy head */
typedef struct CharNode { char ch; struct CharNode* link; } CharNode;
static bool sEmpty(const IntStack* s) { return s->top == 0; }
static bool sPush(IntStack* s, int x) {
    if (s->top == DS_CAP) return false;
    s->data[s->top++] = x; return true;
}
static bool sPop(IntStack* s, int* x) {
    if (sEmpty(s)) return false;
    *x = s->data[--s->top]; return true;
}
static bool qEmpty(const IntQueue* q) { return q->first == NULL; }
static void qPush(IntQueue* q, int x) {
    QNode* p = (QNode*)malloc(sizeof(*p)); if (!p) abort();
    p->data = x; p->next = NULL;
    if (q->rear) q->rear->next = p; else q->first = p;
    q->rear = p;
}
static bool qPop(IntQueue* q, int* x) {
    if (qEmpty(q)) return false;
    QNode* p = q->first; *x = p->data; q->first = p->next;
    if (!q->first) q->rear = NULL;
    free(p); return true;
}

/* @begin twoStackQueue */
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
/* @end */
/* @begin maxRecursive */
static int maxRecursive(const int a[], size_t n) { /* n >= 1 */
    assert(n > 0);
    if (n == 1) return a[0];
    int previous = maxRecursive(a, n-1); /* exactly ONE recursive call */
    return a[n-1] > previous ? a[n-1] : previous;
}
/* @end */
/* @begin ringQueue */
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
/* @end */
/* @begin reverseQueue */
static bool reverseQueue(IntQueue* q) { /* stack capacity must cover all q elements */
    IntStack s = {{0},0}; int x;
    size_t count = 0;
    for (const QNode* p = q->first; p; p = p->next) ++count;
    if (count > DS_CAP) return false; /* leave queue unchanged */
    while (qPop(q, &x)) { bool ok = sPush(&s, x); assert(ok); }
    while (sPop(&s, &x)) qPush(q, x);
    return true;
}
/* @end */
/* @begin reverseQueueADT */
static void reverseQueueADT(IntQueue* q) { /* precondition: length(q) <= DS_CAP */
    IntStack s = {{0},0}; int x;
    while (qPop(q, &x)) { bool ok = sPush(&s, x); assert(ok); }
    while (sPop(&s, &x)) qPush(q, x);
}
/* @end */
/* @begin processInput */
static void processInput(const int a[], size_t n, FILE* output) {
    IntStack s = {{0},0}; int x;
    for (size_t i = 0; i < n; ++i) {
        if (a[i] != -1) {
            if (!sPush(&s, a[i])) fprintf(output, "stack full\n");
        } else if (sPop(&s, &x)) fprintf(output, "%d\n", x);
        else fprintf(output, "stack empty\n");
    }
}
/* @end */
/* @begin processKeyboard */
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
/* @end */
/* @begin legalOperations */
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
/* @end */
/* @begin matchHashExpression */
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
/* @end */
/* @begin matchBracketRing */
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
/* @end */
/* @begin linkedCounts */
static size_t linkedStackCount(const QNode* top) {
    size_t count = 0;
    for (; top; top = top->next) ++count;
    return count;
}
static size_t linkedQueueCount(const IntQueue* q) {
    return linkedStackCount(q->first);
}
/* @end */
/* @begin clearStack */
static void clearStack(IntStack* s) {
    int x; while (sPop(s, &x)) { /* discard */ }
}
/* @end */
/* @begin stackSizeByOperations */
static size_t stackSizeByOperations(IntStack s) { /* embedded array, safe value copy */
    size_t count = 0; int x;
    while (sPop(&s, &x)) ++count;
    return count;
}
/* @end */
/* @begin matchParentheses */
static bool matchParentheses(const char* str) { /* only '(' and ')' matter */
    size_t n = strlen(str), top = 0;
    char* stack = (char*)malloc(n ? n : 1); if (!stack) abort();
    for (size_t i = 0; i < n; ++i) {
        if (str[i] == '(') stack[top++] = '(';
        else if (str[i] == ')') {
            if (!top) { free(stack); return false; }
            --top;
        }
    }
    bool ok = top == 0; free(stack); return ok;
}
/* @end */
/* @begin ackermann */
static unsigned long long ackermann(unsigned m, unsigned long long n) {
    /* Mathematical definition. Only small test values: overflow/resources are bounded. */
    if (m == 0) return n + 1;
    if (n == 0) return ackermann(m-1, 1);
    return ackermann(m-1, ackermann(m, n-1));
}
/* @end */
/* @begin reverseStack */
static void reverseStack(IntStack* s) {
    int a[DS_CAP], x; size_t n = 0;
    while (sPop(s, &x)) a[n++] = x;
    for (size_t i = 0; i < n; ++i) { bool ok = sPush(s, a[i]); assert(ok); }
}
/* @end */
/* @begin copyStack */
static bool copyStack(IntStack* s1, IntStack* s2) { /* distinct stacks */
    if (s1->top > DS_CAP - s2->top) return false;
    IntStack tmp = {{0},0}; int x;
    while (sPop(s1, &x)) { bool ok = sPush(&tmp, x); assert(ok); }
    while (sPop(&tmp, &x)) {
        bool a = sPush(s1, x), b = sPush(s2, x); assert(a && b);
    }
    return true;
}
/* @end */
/* @begin removeStackValue */
static void removeStackValue(IntStack* s, int m) {
    IntStack tmp = {{0},0}; int x;
    while (sPop(s, &x)) if (x != m) { bool ok = sPush(&tmp, x); assert(ok); }
    while (sPop(&tmp, &x)) { bool ok = sPush(s, x); assert(ok); }
}
/* @end */
/* @begin copyQueue */
static void copyQueue(IntQueue* q1, IntQueue* q2) { /* distinct; q2 starts empty */
    assert(qEmpty(q2)); int x; size_t m = 0;
    while (qPop(q1, &x)) { qPush(q2, x); ++m; }
    for (size_t i = 0; i < m; ++i) {
        bool ok = qPop(q2, &x); assert(ok);
        qPush(q1, x); qPush(q2, x);
    }
}
/* @end */
#endif
