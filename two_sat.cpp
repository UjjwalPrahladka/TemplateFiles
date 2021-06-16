#include<bits/stdc++.h>
using namespace std;

struct TwoSat{
    
    // lets say n ids 0....n-1
    // init graph with nodes = 2 * id
    // id 0 => 0 pos, 1 neg
    // id 3 => 6 pos, 7 neg
    // id k => 2 * k pos, 2 * k + 1 neg

    int neg(int u){
        if(u & 1) return u-1;
        return u+1;
    }
    
    void force(int u){
        //addEdge(neg(u), u);
    }

    void biImplication(int u, int v){
        //addEdge(neg(u), neg(v));
        //addEdge(neg(v), neg(u));
        //addEdge(u, v);
        //addEdge(v, u);
    }

    void addOr(int u, int v){
        //addEdge(neg(u), v);
        //addEdge(neg(v), u);
    }

    void addXor(int u, int v){
        addOr(u, v);
        addOr(neg(u), neg(v));
    }

};
