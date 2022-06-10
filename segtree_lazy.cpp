#include <bits/stdc++.h>
using namespace std;


template <typename T, typename L> 
struct segtree{
 
    int size_;
    vector<T> values;
    vector<L> lazy;
    T NEUTRAL_ELEMENT;
    L NO_LAZY;
 
    void init(int n){
        size_ = 1;
        while(size_ < n) size_ *= 2;
        values.assign(2*size_-1, NEUTRAL_ELEMENT);
        lazy.assign(2*size_-1, NO_LAZY);
    }

    void propagate(int x, int lx, int rx){
        if(lx != rx) {
            int m = lx + (rx - lx) / 2;
            values[2*x+1].prop(lazy[x], lx, m);
            values[2*x+2].prop(lazy[x], m+1, rx);
            lazy[2*x+1].prop(lazy[x]);
            lazy[2*x+2].prop(lazy[x]);
        }
        lazy[x] = NO_LAZY;
    }
 
    void build(vector<int>& a, int x, int lx, int rx){
        if(lx == rx){
            if(lx < a.size())
                values[x] = T(a[lx]);
            return;
        }
        int m = lx + (rx - lx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m + 1, rx);
        values[x] = values[2 * x + 1] + values[2 * x + 2];
    }
    
    void build(vector<int>& a){
        build(a, 0, 0, size_-1);
    }

    void update(int val, int l, int r, int x, int lx, int rx){
        propagate(x, lx, rx);
        if(lx > r || rx < l) return;
        if(lx >= l && rx <= r) {
            lazy[x].prop(val);
            values[x].prop(val, lx, rx);
            return;
        }
        int m = lx + (rx - lx) / 2;
        update(val, l, r, 2 * x + 1, lx, m);
        update(val, l, r, 2 * x + 2, m+1, rx);
        values[x] = values[2 * x + 1] + values[2 * x + 2];

    }

    void update(int l, int r, int val){
        update(val, l, r, 0, 0, size_-1);
    }
 
    T calc(int l, int r, int x, int lx, int rx){
        propagate(x, lx, rx);
        if(lx > r || rx < l) return NEUTRAL_ELEMENT;
        if(lx >= l && rx <= r) return values[x];
        int m = lx + (rx - lx) / 2;
        T res1 = calc(l, r, 2 * x + 1, lx, m);
        T res2 = calc(l, r, 2 * x + 2, m+1, rx);
        return res1 + res2;
    }
 
    T calc(int l, int r){
        return calc(l, r, 0, 0, size_-1);
    }
};

struct lazyNode{

    int sum;

    lazyNode() {
        sum = 0;
    }

    void operator=(const lazyNode& other) {
        sum = other.sum;
    }

    void prop(const lazyNode& other) {
        sum += other.sum;
    }

    void prop(const int& val){
        sum += val;
    }

};

struct segNode{

    int sum;

    segNode(){
        sum = 0;
    }

    segNode(int sum) : sum(sum){}

    segNode operator+(const segNode& other) const{
        segNode res;
        res.sum = sum + other.sum;
        return res;
    }

    void prop(const lazyNode& other, int l = 0, int r = 0) {
        sum += (other.sum * (r - l + 1));
    }

    void prop(const int& val, int l = 0, int r = 0){
        sum += (val * (r - l + 1));
    }
};
 