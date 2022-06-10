#include<bits/stdc++.h>
using namespace std;

template <typename T>
struct segtree{
 
    int size;
    vector<T> values;
    T NEUTRAL_ELEMENT;
 
    void init(int n){
        size = 1;
        while(size < n) size *= 2;
        values.assign(2*size-1, NEUTRAL_ELEMENT);
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
        values[x] = values[2*x+1] + values[2*x+2];
    }
    
    void build(vector<int>& a){
        build(a, 0, 0, size-1);
    }
 
    void set(int i, int v, int x, int lx, int rx){
        if(lx == rx){
            values[x] = T(v);
            return;
        }
        int m = lx + (rx - lx) / 2;
        if(i <= m)
            set(i, v, 2 * x + 1, lx, m);
        else 
            set(i, v, 2 * x + 2, m+1, rx);
        values[x] = values[2*x+1] + values[2*x+2];
    }
 
    void set(int i, int v){
        set(i, v, 0, 0, size-1);
    }
 
    T calc(int l, int r, int x, int lx, int rx){
        if(lx > r || rx < l) return NEUTRAL_ELEMENT;
        if(lx >= l && rx <= r) return values[x];
        int m = lx + (rx - lx) / 2;
        T res1 = calc(l, r, 2 * x + 1, lx, m);
        T res2 = calc(l, r, 2 * x + 2, m+1, rx);
        return res1 + res2;
    }
 
    T calc(int l, int r){
        return calc(l, r, 0, 0, size-1);
    }
};

struct node{

    int sum;

    //Neutral Element
    node(){
        sum = 0;
    }

    //Single Element
    node(int sum) : sum(sum){}

    //Merging children
    node operator+(const node& other) const{
        node res;
        res.sum = sum + other.sum;
        return res;
    }
};