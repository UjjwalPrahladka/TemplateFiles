#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int MAX = 1e6 + 6;
const int MOD = 1e9 + 7;
vector<int> fact(MAX+1);
vector<int> invFact(MAX+1);
vector<int> inv(MAX+1);

int power(int a, int b){
    int res = 1;
    while(b > 0){
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b = b >> 1;
    }
    return res;
}

void precalculate(){
    fact[0] = 1;
    for(int i = 1; i <= MAX; i++) fact[i] = 1LL * fact[i-1] * i % MOD;

    invFact[MAX] = power(fact[MAX], MOD-2);
    for(int i = MAX-1; i >= 0; i--)
        invFact[i] = 1LL * invFact[i+1] * (i+1) % MOD; 

    inv[1] = 1;
    for(int i = 2; i <= MAX; i++)
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
}
 
 
int nCr(int n, int r){
    if(n < r) return 0;
    return 1LL * fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
}
