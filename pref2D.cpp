#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> pref2d;

void precalculate(vector<vector<int>>& a){
    int n = a.size();
    int m = a[0].size();
    pref2d.assign(n, vector<int>(m, 0));
    pref2d[0][0] = a[0][0];
    for(int i = 1; i < n; i++) pref2d[i][0] = pref2d[i-1][0] + a[i][0];
    for(int i = 1; i < m; i++) pref2d[0][i] = pref2d[0][i-1] + a[0][i];

    for(int i = 1; i < n; i++){
        for(int j = 1; j < m; j++) pref2d[i][j] = pref2d[i-1][j] + pref2d[i][j-1] - pref2d[i-1][j-1] + a[i][j];
    }

}

int sum(int i1, int j1, int i2, int j2){
    int res = pref2d[i2][j2];
    if(i1 > 0) res -= pref2d[i1-1][j2];
    if(j1 > 0) res -= pref2d[i2][j1-1];
    if(i1 > 0 && j1 > 0) res += pref2d[i1-1][j1-1];
    return res;
}
