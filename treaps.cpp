#include<bits/stdc++.h>
#include <random>
using namespace std;

mt19937 mt(time(nullptr));

struct Treap{
    int data, priority;
    array<Treap*, 2> kids;
    int subtreeSize, sum, toProp, toFlip;

    Treap(int data) : data(data){
        priority = mt();
        kids = {nullptr, nullptr};
        subtreeSize = 1;
        sum = data;
        toProp = 0;
        toFlip = 0;
    }

};

int size(Treap *me) {
    return (me == nullptr ? 0 : me->subtreeSize);
}

void recalc(Treap *me) {
    if (me == nullptr) return;
    me->subtreeSize = 1;
    me->sum = me->data + me->toProp * size(me);
    for (Treap* t:me->kids) if (t != nullptr) {
        me->subtreeSize += t->subtreeSize;
        me->sum += t->sum + t->toProp * size(t);
    }
}

void prop(Treap *me) {
    if (me == nullptr) return;
    if (me->toProp == 0) return;
    for (Treap *t:me->kids) if (t != nullptr) t->toProp += me->toProp;
    me->data += me->toProp;
    me->toProp = 0;
    recalc(me);
}

void flip(Treap *me){

}

Treap* merge(Treap *l, Treap *r) {
    if (l == nullptr) return r;
    if (r == nullptr) return l;
    prop(l); prop(r);
    if (l->priority < r->priority) {
        l->kids[1] = merge(l->kids[1], r);
        recalc(l);
        return l;
    }
    else {
        r->kids[0] = merge(l, r->kids[0]);
        recalc(r);
        return r;
    }
}

array<Treap*, 2> split(Treap *me, int nInLeft) {
    if (me == nullptr) return {nullptr, nullptr};
    prop(me);
    if (size(me->kids[0]) >= nInLeft) {
        array<Treap*, 2> leftRes = split(me->kids[0], nInLeft);
        me->kids[0] = leftRes[1];
        recalc(me);
        return {leftRes[0], me};
    }
    else {
        nInLeft = nInLeft - size(me->kids[0]) - 1;
        array<Treap*, 2> rightRes = split(me->kids[1], nInLeft);
        me->kids[1] = rightRes[0];
        recalc(me);
        return {me, rightRes[1]};
    }
    return {nullptr, nullptr};
}

Treap* rangeAdd(Treap* t, int l, int r, int toAdd) {
    array<Treap*, 2> a = split(t, l);
    array<Treap*, 2> b = split(a[1], r-l+1);
    b[0]->toProp += toAdd;
    return merge(a[0], merge(b[0], b[1]));
}

void display(Treap* cur){
    if(cur == nullptr) return;
    display(cur->kids[0]);
    cout << cur->data << ' ';
    display(cur->kids[1]);
}

/*

*/


