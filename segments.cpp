#include <bits/stdc++.h>
using namespace std;

struct item{
    int sum;
};
 
struct segtree{
 
    int size;
    vector<item> values;
    item NEUTRAL_ELEMENT = {0};
 
    void init(int n){
        size = 1;
        while(size < n) size *= 2;
        values = vector<item>(2*size-1);
    }
 
    item merge(item a, item b){
        return {a.sum + b.sum};
    }
 
    item single(int v){ 
        return {v};
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

// 1,3  2,6  4,6  7,9 =>  1,1,1   2,3,2   4,6,2   7,9,1  (l,r,cnt)
vector<vector<int>> type1(vector<pair<int, int>>& a){
    int n = a.size();

    int L[n], R[n];
    for(int i = 0; i < n; i++) L[i] = a[i].first, R[i] = a[i].second;

    sort(L, L + n);
    sort(R, R + n);

    vector<vector<int>> res;

    int prev = L[0];
    int cnt = 1;

    int j = 0;
    for(int i = 1; i < n; i++){
        while(j < i && R[j] < L[i]){
            if(prev <= R[j]) res.push_back({prev, R[j], cnt});
            cnt--;
            prev = R[j] + 1;
            j++;
        }
        
        if(prev <= L[i] - 1) res.push_back({prev, L[i]-1, cnt});
        cnt++;
        prev = L[i];
    }
    while(j < n){
        if(prev <= R[j]) res.push_back({prev, R[j], cnt});
        cnt--;
        prev = R[j] + 1;
        j++;
    }


    return res;

}


// type2 - cnti = number of intervals that are nested in ith interval
vector<int> type2(vector<pair<int,int>>& a){
    int n = a.size();

    set<int> values;
    for(int i = 0; i < n; i++){
        values.insert(a[i].first);
        values.insert(a[i].second);
    }

    map<int, int> compressed_val;
    int cur = 0;
    for(int x : values){
        compressed_val[x] = cur++;
    }

    int L[n], R[n];
    for(int i = 0; i < n; i++){
        L[i] = compressed_val[a[i].first];
        R[i] = compressed_val[a[i].second];
    }


    int order[n];
    iota(order, order + n, 0);
    sort(order, order + n, [&](int x, int y){
        if(R[x] == R[y]) return L[x] > L[y];
        return R[x] < R[y];
    });

    segtree ds;
    ds.init(2*n);

    vector<int> ans(n);
    for(int i = 0; i < n; i++){
        int idx = order[i];
        ans[idx] = ds.calc(L[idx], 2*n-1).sum;

        int val = ds.calc(L[idx], L[idx]).sum;
        ds.set(L[idx], val+1);
    }

    return ans;
}


// type3 - cnti = number of intervals that partially intersects ith interval
vector<int> type3(vector<pair<int,int>>& a){
    int n = a.size();

    set<int> values;
    for(int i = 0; i < n; i++){
        values.insert(a[i].first);
        values.insert(a[i].second);
    }

    map<int, int> compressed_val;
    int cur = 0;
    for(int x : values){
        compressed_val[x] = cur++;
    }

    int L[n], R[n];
    for(int i = 0; i < n; i++){
        L[i] = compressed_val[a[i].first];
        R[i] = compressed_val[a[i].second];
    }

    int order[n];
    iota(order, order + n, 0);
    sort(order, order + n, [&](int x, int y){
        if(L[x] == L[y]) return R[x] > R[y];
        return L[x] < L[y];
    });

    segtree ds;
    ds.init(2*n);

    vector<int> ans(n);
    for(int i = 0; i < n; i++){
        int idx = order[i];
        ans[idx] = ds.calc(L[idx], R[idx]-1).sum;

        int val = ds.calc(R[idx], R[idx]).sum;
        ds.set(R[idx], val+1);
    }

    
    sort(order, order + n, [&](int x, int y){
        if(R[x] == R[y]) return L[x] < L[y];
        return R[x] > R[y];
    });

    ds.init(2*n);

    for(int i = 0; i < n; i++){
        int idx = order[i];
        ans[idx] += ds.calc(L[idx]+1, R[idx]).sum;

        int val = ds.calc(L[idx], L[idx]).sum;
        ds.set(L[idx], val+1);
    }

    return ans;
}


//type4 - cnti = number of intervals that contains ith interval completely.
vector<int> type4(vector<pair<int,int>>& a){
    int n = a.size();

    set<int> values;
    for(int i = 0; i < n; i++){
        values.insert(a[i].first);
        values.insert(a[i].second);
    }

    map<int, int> compressed_val;
    int cur = 0;
    for(int x : values){
        compressed_val[x] = cur++;
    }

    int L[n], R[n];
    for(int i = 0; i < n; i++){
        L[i] = compressed_val[a[i].first];
        R[i] = compressed_val[a[i].second];
    }


    int order[n];
    iota(order, order + n, 0);
    sort(order, order + n, [&](int x, int y){
        if(L[x] == L[y]) return R[x] > R[y];
        return L[x] < L[y];
    });

    segtree ds;
    ds.init(2*n);

    vector<int> ans(n);
    for(int i = 0; i < n; i++){
        int idx = order[i];
        ans[idx] = ds.calc(R[idx], 2*n-1).sum;

        int val = ds.calc(R[idx], R[idx]).sum;
        ds.set(R[idx], val+1);
    }

    return ans;

}


//type5 - cnti = number of intervals that intersects ith interval
vector<int> type5(vector<pair<int,int>>& a){
    int n = a.size();

    int L[n], R[n];
    for(int i = 0; i < n; i++) L[i] = a[i].first, R[i] = a[i].second;
    sort(L, L + n);
    sort(R, R + n);

    vector<int> ans(n);
    for(int i = 0; i < n; i++){
        int started = upper_bound(L, L + n, a[i].second) - L;
        int ended = lower_bound(R, R + n, a[i].first) - R;
        ans[i] = started - ended - 1;
    }   

    return ans;
}
