#include<bits/stdc++.h>
using namespace std;

struct SparseTable{

    int LOG, N;
    vector<vector<int>> st;
    vector<int> logs;

    void init(int n){
        N = n;
        LOG = ceil(log2(n));
        st.assign(n, vector<int>(LOG+1));
        logs.assign(n+1, 0);
    }

    int func(int x, int y){
        return min(x, y);
    }

    int initial(){
        return INT_MAX;
    }

    void build(vector<int>& a){

        logs[1] = 0;
        for (int i = 2; i <= N; i++)
            logs[i] = logs[i/2] + 1;

        for (int i = 0; i < N; i++) st[i][0] = a[i];

        for (int j = 1; j <= LOG; j++)
            for (int i = 0; i + (1 << j) <= N; i++)
                st[i][j] = func(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
    }

    int query1(int L, int R){
        int ans = initial();
        for (int j = LOG; j >= 0; j--) {
            if ((1 << j) <= R - L + 1) {
                ans = func(ans, st[L][j]);
                L += 1 << j;
            }
        }
        return ans;
    }

    //Idempotent
    int query2(int L, int R){
        int j = logs[R - L + 1];
        int ans = func(st[L][j], st[R - (1 << j) + 1][j]);
        return ans;
    }
};
