#include<bits/stdc++.h>
using namespace std;

struct MaximumMatching{

    vector<vector<int>> adj; // Index of nodes 1.... |  0 is dummy vertex
    vector<int> pairU, pairV, dist;
    int U, V;
    const int INF = INT_MAX;


    void init(int n1, int n2){
        U = n1, V = n2;
        adj = vector<vector<int>>(U + 1);
        pairU = vector<int>(U + 1, 0);
        pairV = vector<int>(V + 1, 0);
        dist = vector<int>(U + 1);
    }

    void addEdge(int u, int v){
        adj[u].push_back(v);
    }

    bool bfs(){
        queue<int> q;
        
        for(int u = 1; u <= U; u++){
            if(pairU[u] == 0){
                dist[u] = 0;
                q.push(u);
            }
            else dist[u] = INF;
        }

        dist[0] = INF;

        while(!q.empty()){
            int u = q.front();
            q.pop();

            if(dist[u] < dist[0]){
                for(int v : adj[u]){
                    if(dist[pairV[v]] == INF){
                        dist[pairV[v]] = dist[u] + 1;
                        q.push(pairV[v]);
                    }
                }
            }
        }

        return dist[0] != INF;
    }

    bool dfs(int u){
        if(u == 0) return true;

        for(int v : adj[u]){
            if(dist[pairV[v]] == dist[u] + 1 && dfs(pairV[v])){
                pairU[u] = v;
                pairV[v] = u;
                return true;
            }
        }

        dist[u] = INF;
        return false;
    }

    int match(){
        int result = 0;
        while(bfs()){
            for(int u = 1; u <= U; u++){
                if(pairU[u] == 0 && dfs(u)) result++;
            }
        }
        return result;
    }
};
