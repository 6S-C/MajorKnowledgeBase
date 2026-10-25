#pragma once
#include <vector>
#include <array>
#include <algorithm>
#include <cstddef>

// Teaching implementations: nodes are allocated with new, released with delete.
struct Node { int data; Node* next = nullptr; };
struct DNode { int data = 0; unsigned freq = 0; DNode* prior = nullptr; DNode* next = nullptr; };
struct CNode { char data = 0; CNode* next = nullptr; };
struct SeqList { int data[1024]; int length = 0; };

// @begin insertIncreasing
bool insertIncreasing(SeqList& L, int x) {
    if (L.length == 1024) return false;
    int i = 0;
    while (i < L.length && L.data[i] < x) ++i;
    for (int j = L.length; j > i; --j) L.data[j] = L.data[j-1];
    L.data[i] = x; ++L.length; return true;
}
// @end
// @begin insertDecreasing
bool insertDecreasing(SeqList& L, int x) {
    if (L.length == 1024) return false;
    int i = 0;
    while (i < L.length && L.data[i] > x) ++i;
    for (int j = L.length; j > i; --j) L.data[j] = L.data[j-1];
    L.data[i] = x; ++L.length; return true;
}
// @end
// @begin listLength
std::size_t listLength(const Node* head) { // head is a dummy node
    std::size_t n = 0;
    for (auto p = head->next; p; p = p->next) ++n;
    return n;
}
// @end
// @begin concatenate
void concatenate(Node* head1, Node* head2) { // disjoint lists, distinct dummy nodes
    auto p = head1;
    while (p->next) p = p->next;
    p->next = head2->next;
    head2->next = nullptr; // transfer ownership; head2 remains an empty list
}
// @end
// @begin deleteAll
void deleteAll(Node* head, int x) {
    auto pre = head;
    while (pre->next) {
        auto p = pre->next;
        if (p->data == x) { pre->next = p->next; delete p; }
        else pre = p;
    }
}
// @end
// @begin compareLists
int compareLists(const std::vector<int>& A, const std::vector<int>& B) {
    std::size_t i = 0;
    while (i < A.size() && i < B.size()) {
        if (A[i] < B[i]) return -1;
        if (A[i] > B[i]) return 1;
        ++i;
    }
    return (A.size() > B.size()) - (A.size() < B.size());
}
// @end
// @begin deleteOpenInterval
void deleteOpenInterval(Node* head, int minval, int maxval) {
    if (minval >= maxval) return;
    auto pre = head;
    while (pre->next && pre->next->data <= minval) pre = pre->next;
    while (pre->next && pre->next->data < maxval) {
        auto p = pre->next; pre->next = p->next; delete p;
    }
}
// @end
// @begin locate
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
// @end
// @begin removeDuplicates
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
// @end
// @begin deleteMinimum
bool deleteMinimum(Node* head) { // delete the first minimum, dummy head
    if (!head->next) return false;
    auto minpre = head;
    for (auto pre = head; pre->next; pre = pre->next)
        if (pre->next->data < minpre->next->data) minpre = pre;
    auto p = minpre->next; minpre->next = p->next; delete p;
    return true;
}
// @end
// @begin moveMinimumFront
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
// @end
// @begin exchangeWithPrevious
bool exchangeWithPrevious(DNode* head, DNode* p) { // dummy-head double ring
    if (p == head || p->prior == head) return false;
    auto q = p->prior;
    auto a = q->prior; auto b = p->next;
    a->next = p; p->prior = a;
    p->next = q; q->prior = p;
    q->next = b; b->prior = q;
    return true;
}
// @end
// @begin exchangeBareRing
void exchangeBareRing(DNode* p) { // no dummy; caller updates any external start marker
    auto q = p->prior;
    if (q == p || p->next == q) return; // rings of size 1 or 2 have unchanged links
    auto a = q->prior; auto b = p->next;
    a->next = p; p->prior = a;
    p->next = q; q->prior = p;
    q->next = b; b->prior = q;
}
// @end
// @begin difference
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
// @end
// @begin containsContiguous
bool containsContiguous(const Node* A, const Node* B) { // no dummy heads
    if (!B) return true;
    for (auto start = A; start; start = start->next) {
        auto p = start; auto q = B;
        while (p && q && p->data == q->data) { p = p->next; q = q->next; }
        if (!q) return true;
    }
    return false;
}
// @end
// @begin containsSubsequence
bool containsSubsequence(const Node* A, const Node* B) { // gaps allowed
    while (A && B) {
        if (A->data == B->data) B = B->next;
        A = A->next;
    }
    return B == nullptr;
}
// @end
// @begin splitCharacters
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
// @end
// @begin removeSortedDuplicates
void removeSortedDuplicates(Node* head) {
    auto p = head->next;
    while (p && p->next) {
        if (p->data == p->next->data) {
            auto q = p->next; p->next = q->next; delete q;
        } else p = p->next;
    }
}
// @end
// @begin reverseArray
void reverseArray(std::vector<int>& A) {
    for (std::size_t i = 0; i < A.size()/2; ++i)
        std::swap(A[i], A[A.size()-1-i]);
}
// @end
// @begin reverseBare
void reverseBare(Node*& first) {
    Node* prev = nullptr;
    while (first) {
        auto next = first->next; first->next = prev; prev = first; first = next;
    }
    first = prev;
}
// @end
// @begin reverseDummy
void reverseDummy(Node* head) { reverseBare(head->next); }
// @end
// @begin reverseDummyRing
void reverseDummyRing(Node* head) { // head itself is never reversed into data
    Node* prev = head; auto p = head->next;
    while (p != head) {
        auto next = p->next; p->next = prev; prev = p; p = next;
    }
    head->next = prev;
}
// @end
// @begin reverseBareRing
void reverseBareRing(Node*& first) {
    if (!first) return;
    auto oldfirst = first; auto p = first->next; auto prev = first;
    while (p != oldfirst) {
        auto next = p->next; p->next = prev; prev = p; p = next;
    }
    oldfirst->next = prev; first = prev;
}
// @end
