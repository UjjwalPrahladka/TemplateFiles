#include<bits/stdc++.h>
using namespace std;

const int MAX = 2e5;
const int LOG = 32;

struct item{
    int sum;
};
 
    
int size;
item values[MAX*LOG];
int L[MAX*LOG], R[MAX*LOG], root[MAX];
int pos;
item NEUTRAL_ELEMENT = {0};

void init(int n){
    size = 1;
    while(size < n) size *= 2;
    for(int i = 0; i < 2*size*LOG; i++){
        values[i] = {};
        L[i] = 0, R[i] = 0, root[i] = 0;
        pos = 2 * size - 1;
    }
    for(int i = 0; i < 2 * size - 1; i++){
        if(2 * i + 2 < 2 * size - 1){
            L[i] = 2 * i + 1;
            R[i] = 2 * i + 2;
        }
    }
}

item merge(item a, item b){
    return {a.sum + b.sum};
}

item single(int v){
    return{v};
}


int update(int val, int idx, int x, int lx, int rx){
    if(lx > idx || rx < idx) return x;

    int ID = pos++;
    int m = lx + (rx - lx) / 2;
    if(lx == rx){
        values[ID] = single(values[x].sum + val);
        return ID;
    }

    L[ID] = update(val, idx, L[x], lx, m);
    R[ID] = update(val, idx, R[x], m+1, rx);

    values[ID] = merge(values[L[ID]], values[R[ID]]);
    return ID;

}

void update(int idx, int val, int version){
    //version 0 already declared start from version 1.
    root[version] = update(val, idx, root[version-1], 0, size-1);
}

item calc(int l, int r, int x, int lx, int rx){
    if(lx > r || rx < l) return NEUTRAL_ELEMENT;
    if(lx >= l && rx <= r) return values[x];
    int m = lx + (rx - lx) / 2;
    item res1 = calc(l, r, L[x], lx, m);
    item res2 = calc(l, r, R[x], m+1, rx);
    return merge(res1, res2);
}

item calc(int l, int r, int version){
    return calc(l, r, root[version], 0, size-1);
}
