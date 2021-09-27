#include<bits/stdc++.h>
#define int int 
using namespace std;
struct BIT{

    vector<int> values;
    int N;
 
    void init(int n){
        N = n;
        values.assign(N+1, 0);
    }
 
    void update(int idx, int val){
        while(idx <= N){
            values[idx] += val;
            idx += idx & -idx;
        }
    }
 
    int sum(int idx){
        int sum = 0;
        while(idx > 0){
            sum += values[idx];
            idx -= idx & -idx;
        }
        return sum;
    }
 
    int rangeSum(int i, int j){
        return sum(j) - (i == 1 ? 0 : sum(i-1));
    }
 
};