#include<bits/stdc++.h>
using namespace std;

const int MAX = 2e5;

vector<int> adj[MAX];
int sz[MAX], col[MAX], cnt[MAX];
bool big[MAX];


void dfs_sz(int u, int p){
    sz[u] = 1;
    for(int v : adj[u]){
        if(v != p){
            dfs_sz(v, u);
            sz[u] += sz[v];
        }
    }
}

void add(int u, int p, int x){
    cnt[col[u]] += x;
    for(int v : adj[u]){
        if(v != p && !big[v]){
            add(v, u, x);
        }
    }
}

void dfs(int u, int p, bool keep){
    int bigChild = -1, mx = -1;
    for(int v : adj[u]){
        if(v != p && sz[v] > mx){
            mx = sz[v];
            bigChild = v;
        }
    }

    for(int v : adj[u]){
        if(v != p && v != bigChild){
            dfs(v, u, 0);
        }
    }

    if(bigChild != -1){
        dfs(bigChild, u, 1);
        big[bigChild] = true;
    }

    add(u, p, 1);
    // use cnt here
    if(bigChild != -1) big[bigChild] = false;
    if(keep == 0){
        add(u, p, -1);
    }

}

void init(int n){
    for(int i = 0; i < n; i++) {
        adj[i].clear();
        sz[i] = 0;
        big[i] = false;
        cnt[i] = 0;
    }
}



vector<int> *vec[MAX];

void dfs(int u, int p, bool keep){
    int mx = -1, bigChild = -1;
    for(int v: adj[u])
        if(v != p && sz[v] > mx)
            mx = sz[v], bigChild = v;
    for(int v: adj[u])
        if(v != p && v != bigChild)
            dfs(v, u, 0);
    if(bigChild != -1) dfs(bigChild, u, 1), vec[u] = vec[bigChild];
    else vec[u] = new vector<int> ();
    vec[u]->push_back(u);
    cnt[ col[u] ]++;
    for(int v : adj[u]){
        if(v != p && v != bigChild){
            for(int x : *vec[v]){
               cnt[ col[x] ]++;
               vec[u] -> push_back(x);
            }
        }
    }
    //now cnt[c] is the number of vertices in subtree of vertex v that has color c.
    // note that in this step *vec[v] contains all of the subtree of vertex v.
    if(keep == 0){
        for(int x : *vec[u]) cnt[ col[x] ]--;
    }
}
