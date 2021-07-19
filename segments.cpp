#include <bits/stdc++.h>
using namespace std;

// 1,3  2,6  4,6  7,9 =>  1,1,1   2,3,2   4,6,2   7,9,1  (l,r,cnt)
vector<vector<int>> type1(vector<pair<int, int>>& a){
    int n = a.size();

    int L[n], R[n];
    for(int i = 0; i < n; i++) L[i] = a[i].first, R[i] = a[i].second;

    sort(L, L + n);
    sort(R, R + n);

    vector<vector<int>> res;

    int prev = L[0];
    int cnt = 1;

    int j = 0;
    for(int i = 1; i < n; i++){
        while(j < i && R[j] < L[i]){
            if(prev <= R[j]) res.push_back({prev, R[j], cnt});
            cnt--;
            prev = R[j] + 1;
            j++;
        }
        
        if(prev <= L[i] - 1) res.push_back({prev, L[i]-1, cnt});
        cnt++;
        prev = L[i];
    }
    while(j < n){
        if(prev <= R[j]) res.push_back({prev, R[j], cnt});
        cnt--;
        prev = R[j] + 1;
        j++;
    }


    return res;

}


// type2 - cnti = number of intervals that are nested in ith interval
vector<int> type2(vector<pair<int,int>>& a){

}


// type3 - cnti = number of intervals that partially intersects ith interval
vector<int> type3(vector<pair<int,int>>& a){

}


//type4 - cnti = number of intervals that contains ith interval completely.
vector<int> type4(vector<pair<int,int>>& a){

}


//type5 - cnti = number of intervals that intersects ith interval
vector<int> type5(vector<pair<int,int>>& a){
    int n = a.size();

    int L[n], R[n];
    for(int i = 0; i < n; i++) L[i] = a[i].first, R[i] = a[i].second;
    sort(L, L + n);
    sort(R, R + n);

    vector<int> ans(n);
    for(int i = 0; i < n; i++){
        int started = upper_bound(L, L + n, a[i].second) - L;
        int ended = lower_bound(R, R + n, a[i].first) - R;
        ans[i] = started - ended;
    }   

    return ans;
}
