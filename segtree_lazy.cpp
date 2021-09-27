#include <bits/stdc++.h>
using namespace std;

struct item{
    int sum;
};

struct extra{
    int sum;
};
 
struct segtree{
 
    int size_;
    vector<item> values;
    vector<extra> lazy;
    item NEUTRAL_ELEMENT = {0};
    extra NO_LAZY = {0};
 
    void init(int n){
        size_ = 1;
        while(size_ < n) size_ *= 2;
        values.assign(2*size_-1, {});
        lazy.assign(2*size_-1, {});
    }
 
    item merge(item a, item b){
        return {a.sum + b.sum};
    }
 
    item single(int v){
        return {v};
    }

    void propagate(int x, int lx, int rx){
        if(lx != rx) {
            int m = lx + (rx - lx) / 2;
            values[2*x+1].sum += lazy[x].sum * (m-lx+1);
            values[2*x+2].sum += lazy[x].sum * (rx-m);
            lazy[2*x+1].sum += lazy[x].sum;
            lazy[2*x+2].sum += lazy[x].sum;
        }
        lazy[x] = NO_LAZY;
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
        build(a, 0, 0, size_-1);
    }

    void update(int val, int l, int r, int x, int lx, int rx){
        propagate(x, lx, rx);
        if(lx > r || rx < l) return;
        if(lx >= l && rx <= r) {
            lazy[x].sum += val;
            values[x].sum += val * (rx - lx + 1);
            return;
        }
        int m = lx + (rx - lx) / 2;
        update(val, l, r, 2 * x + 1, lx, m);
        update(val, l, r, 2 * x + 2, m+1, rx);
        values[x] = merge(values[2*x+1], values[2*x+2]);

    }

    void update(int l, int r, int val){
        update(val, l, r, 0, 0, size_-1);
    }
 
    item calc(int l, int r, int x, int lx, int rx){
        propagate(x, lx, rx);
        if(lx > r || rx < l) return NEUTRAL_ELEMENT;
        if(lx >= l && rx <= r) return values[x];
        int m = lx + (rx - lx) / 2;
        item res1 = calc(l, r, 2 * x + 1, lx, m);
        item res2 = calc(l, r, 2 * x + 2, m+1, rx);
        return merge(res1, res2);
    }
 
    item calc(int l, int r){
        return calc(l, r, 0, 0, size_-1);
    }
};
 
int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    segtree ds;
    ds.init(n);
    while(m--){
        int t;
        cin >> t;
        if(t == 1){
            int l, r, v;
            cin >> l >> r >> v;
            r--;
            ds.update(l, r, v);
        }
        else{
            int l, r;
            cin >> l >> r;
            r--;
            cout << ds.calc(l, r).sum << '\n';

        }
    }
}