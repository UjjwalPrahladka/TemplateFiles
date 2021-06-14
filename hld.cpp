#include<bits/stdc++.h>
#define int int 
using namespace std;
 
 
struct item{
    int sum;
};
 
struct segtree{
 
    int size;
    vector<item> sums;
    item NEUTRAL_ELEMENT = {0};
 
    void init(int n){
        size = 1;
        while(size < n) size *= 2;
        sums = vector<item>(2*size-1);
    }
 
    item merge(item a, item b){
        return {max(a.sum, b.sum)};
    }
 
    item single(int v){
        return {v};
    }
    void build(vector<int>& a, int x, int lx, int rx){
        if(lx == rx){
            if(lx < a.size())
                sums[x] = single(a[lx]);
            return;
        }
        int m = lx + (rx - lx) / 2;
        build(a, 2 * x + 1, lx, m);
        build(a, 2 * x + 2, m + 1, rx);
        sums[x] = merge(sums[2 * x + 1], sums[2 * x + 2]);
    }
    
    void build(vector<int>& a){
        build(a, 0, 0, size-1);
    }
 
    void set(int i, int v, int x, int lx, int rx){
        if(lx == rx){
            sums[x] = single(v);
            return;
        }
        int m = lx + (rx - lx) / 2;
        if(i <= m)
            set(i, v, 2 * x + 1, lx, m);
        else 
            set(i, v, 2 * x + 2, m+1, rx);
        sums[x] = merge(sums[2 * x + 1], sums[2 * x + 2]);
    }
 
    void set(int i, int v){
        set(i, v, 0, 0, size-1);
    }
 
    item calc(int l, int r, int x, int lx, int rx){
        if(lx > r || rx < l) return NEUTRAL_ELEMENT;
        if(lx >= l && rx <= r) return sums[x];
        int m = lx + (rx - lx) / 2;
        item res1 = calc(l, r, 2 * x + 1, lx, m);
        item res2 = calc(l, r, 2 * x + 2, m+1, rx);
        return merge(res1, res2);
    }
 
    item calc(int l, int r){
        return calc(l, r, 0, 0, size-1);
    }
}ds;
 
vector<int> parent, depth, heavy, head, pos, lin_array, node_val;
vector<vector<int>> adj, memo;
int cur_pos, LOG;
 
int dfs(int v) {
    memo[v][0] = parent[v]; 
    for (int i = 1; i <= LOG && memo[v][i-1] != -1; i++) 
        memo[v][i] = memo[memo[v][i - 1]][i - 1]; 
    int size = 1;
    int max_c_size = 0;
    for (int c : adj[v]) {
        if (c != parent[v]) {
            parent[c] = v, depth[c] = depth[v] + 1;
            int c_size = dfs(c);
            size += c_size;
            if (c_size > max_c_size)
                max_c_size = c_size, heavy[v] = c;
        }
    }
    if(size == 1){
        heavy[v] = -1;
    }
    return size;
}
 
void decompose(int v, int h) {
    lin_array.push_back(node_val[v]);
    head[v] = h, pos[v] = cur_pos++;
    if (heavy[v] != -1)
        decompose(heavy[v], h);
    for (int c : adj[v]) {
        if (c != parent[v] && c != heavy[v])
            decompose(c, c);
    }
}
 
void init(int n) {
    adj = vector<vector<int>>(n);
    node_val = vector<int>(n);
    parent = vector<int>(n);
    depth = vector<int>(n);
    heavy = vector<int>(n);
    head = vector<int>(n);
    pos = vector<int>(n);
    ds.init(n);
    cur_pos = 0;
    LOG = (int)log2(n) + 1;
    memo = vector<vector<int>>(n, vector<int>(LOG+1));
}
 
int query(int a, int b) {
    int res = 0;
    for (; head[a] != head[b]; b = parent[head[b]]) {
        if (depth[head[a]] > depth[head[b]])
            swap(a, b);
        int cur_heavy_path_max = ds.calc(pos[head[b]], pos[b]).sum;
        res = max(res, cur_heavy_path_max);
    }
    if (depth[a] > depth[b])
        swap(a, b);
    int last_heavy_path_max = ds.calc(pos[a], pos[b]).sum;
    res = max(res, last_heavy_path_max);
    return res;
}

void update(int a, int b){
    
    for (; head[a] != head[b]; b = parent[head[b]]) {
        if (depth[head[a]] > depth[head[b]])
            swap(a, b);
        // ds.update(pos[head[b]], pos[b]);
    }
    if (depth[a] > depth[b])
        swap(a, b);
    // ds.update(pos[a], pos[b]);
}
 
int lca(int u, int v){ 
    if (depth[u] < depth[v]) 
        swap(u, v); 
  
    for (int i = LOG; i >= 0; i--) 
        if ((depth[u] - pow(2, i)) >= depth[v]) 
            u = memo[u][i]; 
  
    if (u == v) 
        return u; 
  
    for (int i = LOG; i >= 0; i--) { 
        if (memo[u][i] != memo[v][i]) { 
            u = memo[u][i]; 
            v = memo[v][i]; 
        } 
    } 
 
    return memo[u][0]; 
}
 
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
 
    int n, q;
    cin >> n >> q;
    init(n);
    for(int i = 0; i < n; i++) cin >> node_val[i];
    for(int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
 
    dfs(0);
    decompose(0, 0);
 
    ds.build(lin_array);
 
    while(q--){
        int t;
        cin >> t;
        if(t == 1){
            int i, x;
            cin >> i >> x;
            i--;
            ds.set(pos[i], x);
        }
        else{
            int u, v;
            cin >> u >> v;
            u--, v--;
            int l = lca(u, v);
            cout << max(query(u, l), query(v, l)) << ' ';
 
        }
    }
    
}
 
 