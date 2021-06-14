#include<bits/stdc++.h>
#define int int
using namespace std;
const int MAX = 4e6+10;

long long phi[MAX], result[MAX];
  

void computeTotient(){
    phi[0] = 0;
    phi[1] = 1;
    for (int i = 2; i < MAX; i++)
        phi[i] = i;

    for (int i = 2; i < MAX; i++) {
        if (phi[i] == i) {
            for (int j = i; j < MAX; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}

// result[i] = gcd(1, i) + gcd(2, i) + gcd(3, i)....gcd(i, i)
void sumGCDUptoN(){

    computeTotient();
  
    for (int i=1; i<MAX; ++i){
        for (int j=1; i*j<MAX; ++j)
            result[i*j] += i*phi[j];
    }
}