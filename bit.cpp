#include<bits/stdc++.h>
using namespace std;
struct BIT{

    vector<int> values;
    int N, LOGN;
 
    void init(int n){
        N = n;
        LOGN = ceil(log2(N));
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

    void rangeAdd(int i, int j, int val){
        update(i, val);
        update(j+1, -val);
    }

    //lower_bound(x) => works if prefix sum in increasing
    int find(int x){
        int sum = 0;
        int pos = 0;
        
        for(int i = LOGN; i >= 0; i--){
            if(pos + (1 << i) <= N and sum + values[pos + (1 << i)] < x){
                sum += values[pos + (1 << i)];
                pos += (1 << i);
            }
        }
 
        return pos + 1;
    }
 
};
