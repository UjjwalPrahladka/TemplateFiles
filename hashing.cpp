#include <bits/stdc++.h>
using namespace std;


struct StringHash{
    const int MOD1 = 1e9 + 7, MOD2 = 1e9 + 9;
    const int base1 = 33, base2 = 37;

    string s;
    int N;

    vector<int> pw1, pw2, inv1, inv2, H1, H2;

    StringHash(string s) : s(s){
        N = s.size();
        pw1.assign(N+1, 0);
        pw2.assign(N+1, 0);
        inv1.assign(N+1, 0);
        inv2.assign(N+1, 0);
        H1.assign(N+1, 0);
        H2.assign(N+1, 0);
    }

    int add(int a, int b, int MOD){
        int res = (a + b) % MOD;
        if(res < 0)
            res += MOD;
        return res;
    }

    int mult(int a, int b, int MOD){
        int res = (a * 1LL * b) % MOD;
        if(res < 0)
            res += MOD;
        return res;
    }

    int power(int a, int b, int MOD){
        int res = 1;
        while(b){
            if((b % 2) == 1)
                res = mult(res, a, MOD);
            a = mult(a, a, MOD);
            b /= 2;
        }
        return res;
    }

    void precalc() {
        pw1[0] = 1, pw2[0] = 1;
        for(int i = 1; i <= N; i++){
            pw1[i] = mult(pw1[i - 1], base1, MOD1);
            pw2[i] = mult(pw2[i - 1], base2, MOD2);
        }
        
        int pw_inv1 = power(base1, MOD1 - 2, MOD1);
        int pw_inv2 = power(base2, MOD2 - 2, MOD2);
        inv1[0] = 1, inv2[0] = 1;
        for(int i = 1; i <= N; i++){
            inv1[i] = mult(inv1[i - 1], pw_inv1, MOD1);
            inv2[i] = mult(inv2[i - 1], pw_inv2, MOD2);
        }
    }

    void build(){
        for(int i = 0; i < N ; ++i){
            H1[i] = add((i == 0) ? 0 : H1[i - 1], mult(pw1[i], s[i] - 'a' + 1, MOD1), MOD1);
            H2[i] = add((i == 0) ? 0 : H2[i - 1], mult(pw2[i], s[i] - 'a' + 1, MOD2), MOD2);
        }
    }

    pair<int,int> getHash(int x , int y){
        int res1 = add(H1[y], (x == 0) ? 0 : -H1[x - 1], MOD1);
        res1 = mult(res1 , (x == 0) ? 1 : inv1[x], MOD1);
        int res2 = add(H2[y], (x == 0) ? 0 : -H2[x - 1], MOD2);
        res2 = mult(res2 , (x == 0) ? 1 : inv2[x], MOD2);
        return {res1, res2};
    }

}; 

