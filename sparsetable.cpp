#include<bits/stdc++.h>
using namespace std;

template <typename T>
struct SparseTable{

    int LOG, N;
    vector<vector<T>> st;
    vector<int> logs;

    void init(int n){
        N = n;
        LOG = ceil(log2(n));
        st.assign(n, vector<T>(LOG+1));
        logs.assign(n+1, 0);
    }

    void build(vector<int>& a){

        logs[1] = 0;
        for (int i = 2; i <= N; i++)
            logs[i] = logs[i/2] + 1;

        for (int i = 0; i < N; i++) {
            st[i][0] = T(a[i]);
        }

        for (int j = 1; j <= LOG; j++){
            for (int i = 0; i + (1 << j) <= N; i++){
                st[i][j] = st[i][j-1] + st[i + (1 << (j - 1))][j - 1];
            }
        }
    }

    T query1(int L, int R){
        T ans;
        for (int j = LOG; j >= 0; j--) {
            if ((1 << j) <= R - L + 1) {
                ans = ans + st[L][j];
                L += 1 << j;
            }
        }
        return ans;
    }

    //Idempotent
    T query2(int L, int R){
        int j = logs[R - L + 1];
        return st[L][j] + st[R - (1 << j) + 1][j];
    }
};

struct Node{
    int mn;

    Node(){
        mn = INT_MAX;
    }

    Node(int mn) : mn(mn){}

    Node operator+(const Node& other) const{
        Node res;
        res.mn = min(mn, other.mn);
        return res;
    }

    void operator=(const Node& other){
        mn = other.mn;
    }
};