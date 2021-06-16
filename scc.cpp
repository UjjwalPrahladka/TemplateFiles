#include<bits/stdc++.h>
using namespace std;

struct SCC{

    vector<vector<int>> adj;
    vector<vector<int>> rev_adj;
    vector<set<int>> compressed_adj;
    vector<int> component_no;
    vector<bool> vis;
    vector<int> indegree, outdegree;
    vector<int> topological_ordering;
    int N;
    int N_compressed;

    void init(int n){
        N = n;
        adj = vector<vector<int>>(n);
        rev_adj = vector<vector<int>>(n);
        component_no = vector<int>(n, -1);
        vis = vector<bool>(n);
        topological_ordering = vector<int>();
    }

    void addEdge(int u, int v){
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }

    void findOrdering(int u){
        vis[u] = true;
        for(int v: adj[u]){
            if(!vis[v]) findOrdering(v);
        }
        topological_ordering.push_back(u);
    }

    void dfs(int u, int comp){
        component_no[u] = comp;
        vis[u] = true;
        for(int v : rev_adj[u]){
            if(!vis[v]){
                dfs(v, comp);
            }
        }
    }

    void compressSCC(){
        vis.assign(N, false);
        for(int i = 0; i < N; i++){
            if(!vis[i]){
                findOrdering(i);
            }
        }

        N_compressed = 0;
        vis.assign(N, false);
        reverse(topological_ordering.begin(), topological_ordering.end());

        for(int u : topological_ordering){
            if(vis[u]) continue;
            dfs(u, N_compressed);
            N_compressed++;
        }
        
        compressed_adj = vector<set<int>>(N_compressed);

        for(int u = 0; u < N; u++){
            for(int v : adj[u]){
                if(component_no[u] != component_no[v]){
                    compressed_adj[component_no[u]].insert(component_no[v]);
                }
            }
        }

    }

    void fillDegrees(){
        indegree = vector<int>(N_compressed);
        outdegree = vector<int>(N_compressed);

        for(int u = 0; u < N_compressed; u++){
            for(int v : compressed_adj[u]) indegree[v]++, outdegree[u]++;
        }
    }
    
};
