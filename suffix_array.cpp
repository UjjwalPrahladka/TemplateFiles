#include<bits/stdc++.h>
using namespace std;

struct item{
    int mn;
};
 
struct segtree{
 
    int size;
    vector<item> values;
    item NEUTRAL_ELEMENT = {INT_MAX};
 
    void init(int n){
        size = 1;
        while(size < n) size *= 2;
        values.resize(2*size-1);
    }
 
    item merge(item a, item b){
        return {min(a.mn, b.mn)};
    }
 
    item single(int v){
        return {v};
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


vector<int> p;
vector<int> c;
vector<int> lcp;
string s;


void radix_sort(vector<pair<pair<int,int>, int>> &a){
    int n = a.size();

    
    vector<int> cnt(n);
    for(int i = 0; i < n; i++) cnt[a[i].first.second]++;

    vector<pair<pair<int,int>, int>> a_new(n);
    vector<int> pos(n);
    pos[0] = 0;
    for(int i = 1; i < n; i++) pos[i] = pos[i-1] + cnt[i-1];

    for(auto x: a){
        int i = x.first.second;
        a_new[pos[i]] = x;
        pos[i]++;
    }

    a = a_new;



    cnt = vector<int>(n);
    for(int i = 0; i < n; i++) cnt[a[i].first.first]++;

    a_new = vector<pair<pair<int,int>, int>>(n);
    pos = vector<int>(n);
    pos[0] = 0;
    for(int i = 1; i < n; i++) pos[i] = pos[i-1] + cnt[i-1];

    for(auto x: a){
        int i = x.first.first;
        a_new[pos[i]] = x;
        pos[i]++;
    }

    a = a_new;
    

}


void build_suffix_array(){

    s += '$'; // use space instead if s contains $
    int n = s.size();

    p = vector<int>(n);
    c = vector<int>(n);

    vector<pair<char, int>> a(n);
    for(int i = 0; i < n; i++) a[i] = {s[i], i};
    sort(a.begin(), a.end());

    for(int i = 0; i < n; i++) p[i] = a[i].second;

    c[p[0]] = 0;
    for(int i = 1; i < n; i++){
        if(a[i].first == a[i-1].first){
            c[p[i]] = c[p[i-1]];
        }
        else{
            c[p[i]] = c[p[i-1]] + 1;
        }
    }

    int k = 0;
    while((1 << k) < n){

        vector<pair<pair<int,int>, int>> a(n);
        for(int i = 0; i < n; i++){
            a[i] = {{c[i], c[(i + (1 << k)) % n]}, i};
        }

        radix_sort(a);

        for(int i = 0; i < n; i++) p[i] = a[i].second;

        c[p[0]] = 0;
        for(int i = 1; i < n; i++){
            if(a[i].first == a[i-1].first){
                c[p[i]] = c[p[i-1]];
            }
            else{
                c[p[i]] = c[p[i-1]] + 1;
            }
        }

        k++;

    }
}

 
void build_lcp(){
    int n = s.size();
    lcp = vector<int>(n);

    int k = 0;
    for(int i = 0; i < n-1; i++){
        int pi = c[i];
        int j = p[pi - 1];

        while(i + k < n && j + k < n && s[i + k] == s[j + k]) k++;

        lcp[pi-1] = k;
        k = max(k - 1, 0);
    }
}


//build segtree on lcp with min operation
int lcp_between(int i, int j, segtree& ds){
    int x = c[i], y = c[j];
    if(i > j) swap(i, j);
    int common = ds.calc(i, j-1).mn;
    return common;
}

