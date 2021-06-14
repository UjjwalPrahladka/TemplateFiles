#include<bits/stdc++.h>
#define int int 
using namespace std;
struct BIT{

    vector<vector<int>> values;
    int N, M;
    
    void init(int n, int m){
        N = n;
        M = m;
        values = vector<vector<int>>(N+1, vector<int>(M+1));
    }
 
    void update(int i, int j, int val){
        while(i <= N){
            while(j <= M){
                values[i][j] += val;
                j += j & -j;
            }
            i += i & -i;
        }
    }
 
    int sum(int i, int j){
        int sum = 0;
        while(i > 0){
            while(j > 0){
                sum += values[i][j];
                j -= j & -j;
            }
            i -= i & -i;
        }
        return sum;
    }
 
    int rangeSum(int x1, int y1, int x2, int y2){
        return sum(x2, y2) - sum(x2, y1-1) - sum(x1-1, y2) + sum(x1-1, y1-1);
    }
 
};