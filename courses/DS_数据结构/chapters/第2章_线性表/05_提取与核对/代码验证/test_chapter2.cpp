#include "chapter2_reference.hpp"
#include <cassert>
#include <random>
#include <iostream>
#include <set>
using V=std::vector<int>;
Node* make(const V& v) { auto h=new Node{}; auto p=h; for(int x:v){p->next=new Node{x};p=p->next;}return h; }
V values(const Node* h) { V v;for(auto p=h->next;p;p=p->next){assert(v.size()<10000);v.push_back(p->data);}return v; }
void destroy(Node* h){while(h){auto p=h;h=h->next;delete p;}}
DNode* doubleRing(const V& v) {auto h=new DNode{};h->next=h->prior=h;for(int x:v){auto p=new DNode{x};p->prior=h->prior;p->next=h;h->prior->next=p;h->prior=p;}return h;}
V doubleValues(DNode* h) {V v; auto pre=h;for(auto p=h->next;p!=h;p=p->next){assert(p->prior==pre);v.push_back(p->data);pre=p;assert(v.size()<10000);}assert(h->prior==pre);return v;}
void destroyDouble(DNode*h){auto p=h->next;while(p!=h){auto q=p;p=p->next;delete q;}delete h;}
int main(){
 std::mt19937 rng(20261025); int trials=0;
 for(int t=0;t<500;++t){
  V a;for(unsigned i=0,n=rng()%40;i<n;++i)a.push_back(int(rng()%11)-5);
  auto h=make(a);removeDuplicates(h);V unique;for(int x:a)if(std::find(unique.begin(),unique.end(),x)==unique.end())unique.push_back(x);assert(values(h)==unique);destroy(h);
  h=make(a);deleteAll(h,2);V filtered;for(int x:a)if(x!=2)filtered.push_back(x);assert(values(h)==filtered);destroy(h);
  h=make(a);assert(listLength(h)==a.size());auto expected=a;assert(deleteMinimum(h)==!a.empty());if(!expected.empty())expected.erase(std::min_element(expected.begin(),expected.end()));assert(values(h)==expected);destroy(h);
  h=make(a);auto first=h->next;moveMinimumFront(first);h->next=first;expected=a;if(!a.empty()){auto it=std::min_element(expected.begin(),expected.end());int x=*it;expected.erase(it);expected.insert(expected.begin(),x);}assert(values(h)==expected);destroy(h);
  expected=a;std::reverse(expected.begin(),expected.end());h=make(a);reverseDummy(h);assert(values(h)==expected);destroy(h);auto array=a;reverseArray(array);assert(array==expected);
  h=make(a);auto tail=h;while(tail->next)tail=tail->next;tail->next=h;reverseDummyRing(h);V ring;for(auto p=h->next;p!=h;p=p->next){ring.push_back(p->data);assert(ring.size()<=a.size());}assert(ring==expected);tail=h;while(tail->next!=h)tail=tail->next;tail->next=nullptr;destroy(h);
  if(!a.empty()){h=make(a);auto b=h->next;tail=b;while(tail->next)tail=tail->next;tail->next=b;reverseBareRing(b);ring.clear();auto p=b;do{ring.push_back(p->data);p=p->next;assert(ring.size()<=a.size());}while(p!=b);assert(ring==expected);tail=b;while(tail->next!=b)tail=tail->next;tail->next=nullptr;h->next=b;destroy(h);}
  auto sorted=a;std::sort(sorted.begin(),sorted.end());h=make(sorted);deleteOpenInterval(h,-2,3);filtered.clear();for(int x:sorted)if(!(x>-2&&x<3))filtered.push_back(x);assert(values(h)==filtered);destroy(h);
  h=make(sorted);removeSortedDuplicates(h);auto su=sorted;su.erase(std::unique(su.begin(),su.end()),su.end());assert(values(h)==su);destroy(h);
  SeqList L{};for(int x:sorted)L.data[L.length++]=x;assert(insertIncreasing(L,1));sorted.insert(std::lower_bound(sorted.begin(),sorted.end(),1),1);assert(V(L.data,L.data+L.length)==sorted);
  std::sort(sorted.rbegin(),sorted.rend());L.length=0;for(int x:sorted)L.data[L.length++]=x;assert(insertDecreasing(L,1));sorted.push_back(1);std::sort(sorted.rbegin(),sorted.rend());assert(V(L.data,L.data+L.length)==sorted);
  V b;for(unsigned i=0,n=rng()%30;i<n;++i)b.push_back(int(rng()%11)-5);std::sort(b.begin(),b.end());b.erase(std::unique(b.begin(),b.end()),b.end());auto A=make(su),B=make(b);V diff;std::set_difference(su.begin(),su.end(),b.begin(),b.end(),std::back_inserter(diff));assert(difference(A,B)==diff.size());assert(values(A)==diff);assert(values(B)==b);destroy(A);destroy(B);
  h=make(a);B=make(b);auto both=a;both.insert(both.end(),b.begin(),b.end());concatenate(h,B);assert(values(h)==both);assert(!B->next);destroy(h);destroy(B);
  for(std::size_t i=0;i<a.size();++i){auto d=doubleRing(a);auto p=d->next;for(std::size_t j=0;j<i;++j)p=p->next;expected=a;bool changed=exchangeWithPrevious(d,p);if(i){assert(changed);std::swap(expected[i],expected[i-1]);}else assert(!changed);assert(doubleValues(d)==expected);destroyDouble(d);}
  ++trials;
 }
 auto h=make({1,2,3});auto b=make({1,3});assert(!containsContiguous(h->next,b->next));assert(containsSubsequence(h->next,b->next));assert(containsContiguous(h->next,nullptr));destroy(h);destroy(b);
 assert(compareLists({}, {})==0);assert(compareLists({1},{1,2})==-1);assert(compareLists({2},{1,9})==1);
 auto d=doubleRing({1,2,3});d->next->freq=3;d->next->next->freq=2;d->prior->freq=2;auto p=locate(d,3);assert(p->freq==3);assert(doubleValues(d)==V({1,3,2}));assert(!locate(d,99));destroyDouble(d);
 CNode* chars=nullptr;CNode** end=&chars;for(char c:std::string("a1!B2?")){*end=new CNode{c};end=&(*end)->next;}auto split=splitCharacters(chars);assert(!chars);std::array<std::string,3> cv;for(int k=0;k<3;++k){auto head=split[k];auto p=head->next;while(p!=head){cv[k]+=p->data;auto q=p;p=p->next;delete q;}delete head;}assert((cv==std::array<std::string,3>{"aB","12","!?"}));
 SeqList full{};full.length=1024;assert(!insertIncreasing(full,2));assert(!insertDecreasing(full,2));
 std::cout<<"PASS: "<<trials<<" randomized list cases plus boundary, pointer-integrity and character-split checks\n";
}
