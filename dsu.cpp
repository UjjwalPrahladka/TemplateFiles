#include <bits/stdc++.h>
using namespace std;
struct DSU{

    vector<int> parent;
    vector<int> rank;
    
    void init(int n){
        parent.assign(n, 0);
        rank.assign(n, 0);
        for(int i = 0; i < n; i++){
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int i){
        if(parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    void merge(int i, int j){
        int p1 = find(i);
        int p2 = find(j);
        if(p1 == p2) return;
        if(rank[p1] < rank[p2])
            parent[p1] = p2;
        else{
            parent[p2] = p1;
            if(rank[p1] == rank[p2])
                rank[p1]++;
        }
    }
};
