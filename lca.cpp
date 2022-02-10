#include <bits/stdc++.h> 
using namespace std; 
const int MAX = 2e5;
const int LOG = 18;
vector<int> adj[MAX+1];
int lev[MAX+1], sub_size[MAX+1];
int memo[MAX+1][LOG+1];

void dfs(int u, int p){
    if(p == u) lev[u] = 0;
    memo[u][0] = p; 
    for (int i = 1; i <= LOG; i++) 
        memo[u][i] = memo[memo[u][i - 1]][i - 1]; 
    sub_size[u] = 1;
    for(int v : adj[u]){
        if(v != p){
            lev[v] = lev[u] + 1; 
            dfs(v, u);
            sub_size[u] += sub_size[v];
        }
    }
}

int lca(int u, int v){ 
    if (lev[u] < lev[v]) 
        swap(u, v); 
  
    for (int i = LOG; i >= 0; i--) 
        if ((lev[u] - (1 << i)) >= lev[v]) 
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

int dist(int u, int v){
    int l = lca(u, v);
    return lev[u] + lev[v] - 2 * lev[l];
}
