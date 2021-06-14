#include<bits/stdc++.h>
#define int int
using namespace std;

const int N = 1e5 + 10;
const int LOGN = 20;

vector<int> g[N];
int sub[N], nn, U[N], V[N], W[N], deleted[N], ans[N];

int par[N], level[N], dist[LOGN][N];

int adj(int x, int e) { return U[e] ^ V[e] ^ x; }

void dfs1(int u, int p) {
    sub[u] = 1;
    nn++;
    for (auto e : g[u]) {
        int w = adj(u, e);
        if (w != p && !deleted[e]) dfs1(w, u), sub[u] += sub[w];
    }
}


int find_centroid(int u, int p) {
    for (auto e : g[u]) {
        if (deleted[e]) continue;
        int w = adj(u, e);
        if (w != p && sub[w] > nn / 2) return find_centroid(w, u);
    }
    return u;
}

void add_edge_centroid_tree(int parent, int child) {
    if(parent == -1) {
        par[child] = -1;
        level[child] = 0;
        return;
    }
    par[child] = parent;
    level[child] = level[parent] + 1;
}

void dfs2(int u, int p, int lvl) {
    for (auto e : g[u]) {
        int w = adj(u, e);
        if (w == p || deleted[e]) continue;
        dist[lvl][w] = dist[lvl][u] + W[e];
        dfs2(w, u, lvl);
    }
}

void decompose(int root, int p = -1) {
    nn = 0;  
    dfs1(root, -1);  

    int centroid = find_centroid(root, -1);

    add_edge_centroid_tree(p, centroid);
    
    dist[level[centroid]][centroid] = 0;
    dfs2(centroid, -1, level[centroid]);

    for (auto e : g[centroid]) {
        if (deleted[e]) continue;
        deleted[e] = 1;
        int w = adj(centroid, e);
        decompose(w, centroid);
    }
}
 
int compute_distance(int x, int y) {
    int lca_level = 0;
    int t_x = x, t_y = y;
    if(level[x] < level[y]) swap(x, y);
    while(level[x] != level[y]){
        x = par[x];
    }
    while(x != y){
        x = par[x];
        y = par[y];
    }
    lca_level = level[x];    
    return dist[lca_level][t_x] + dist[lca_level][t_y];
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n-1; i++) {
        cin >> U[i] >> V[i];
        U[i]--, V[i]--;
        W[i] = 1;
        g[U[i]].push_back(i);
        g[V[i]].push_back(i);
    }
    decompose(0);
    for(int i = 0; i < n; i++) ans[i] = 999999;
    int cur = 0;
    while(cur != -1){
        ans[cur] = min(ans[cur], dist[level[cur]][0]);
        cur = par[cur];
    }

    while(m--){
        int t, x;
        cin >> t >> x;
        x--;
        if(t == 1){
            int cur = x;
            while(cur != -1){
                ans[cur] = min(ans[cur], dist[level[cur]][x]);
                cur = par[cur];
            }
        }else{
            int cur = x;
            int res = INT_MAX;
            while(cur != -1){
                res = min(ans[cur] + dist[level[cur]][x], res);
                cur = par[cur];
            }
            cout << res << '\n';
        }
    }
}