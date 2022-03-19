#include<bits/stdc++.h>
using namespace std;

struct item{

};
 
struct segtree{
 
    int size;
    vector<item> values;
    item NEUTRAL_ELEMENT = {};
 
    void init(int n){
        size = 1;
        while(size < n) size *= 2;
        values.assign(2*size-1, {});
    }
 
    item merge(item a, item b){

    }
 
    item single(int v){
        
    }
    
    void build(vector<int>& a, int x, int lx, int rx){
        if(lx == rx){
            if(lx < a.size())
                values[x] = single(a[lx]);
            return;
        }
        int m = lx + (rx - lx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m + 1, rx);
        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }
    
    void build(vector<int>& a){
        build(a, 0, 0, size-1);
    }
 
    void set(int i, int v, int x, int lx, int rx){
        if(lx == rx){
            values[x] = single(v);
            return;
        }
        int m = lx + (rx - lx) / 2;
        if(i <= m)
            set(i, v, 2 * x + 1, lx, m);
        else 
            set(i, v, 2 * x + 2, m+1, rx);
        values[x] = merge(values[2 * x + 1], values[2 * x + 2]);
    }
 
    void set(int i, int v){
        set(i, v, 0, 0, size-1);
    }
 
    item calc(int l, int r, int x, int lx, int rx){
        if(lx > r || rx < l) return NEUTRAL_ELEMENT;
        if(lx >= l && rx <= r) return values[x];
        int m = lx + (rx - lx) / 2;
        item res1 = calc(l, r, 2 * x + 1, lx, m);
        item res2 = calc(l, r, 2 * x + 2, m+1, rx);
        return merge(res1, res2);
    }
 
    item calc(int l, int r){
        return calc(l, r, 0, 0, size-1);
    }
};