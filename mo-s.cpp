#include <bits/stdc++.h>
using namespace std;
 
const int N = 5e4 + 10;
const int Q = 1e5 + 10;
int A[N], last[N], rev[N + Q], cnt[N + Q];
bool use[N];

struct Query {
  int idx, l, r, t, lb, rb;
} queries[Q];

struct Update {
  int x, new_y, prv_y;
} updates[Q];

int nq, nu, compressed_val;

long long ans[Q], curr_ans;

void add_element(int x) {
  use[x] = true;
  if (++cnt[A[x]] == 1) {
    curr_ans += rev[A[x]];
  }
}

void remove_element(int x) {
  use[x] = false;
  if (--cnt[A[x]] == 0) {
    curr_ans -= rev[A[x]];
  }
}

void reflect_update(int x, int y) {
  if (!use[x]) {
    A[x] = y;
    return;
  }
  remove_element(x);
  A[x] = y;
  add_element(x);
}

void do_update(int i) { 
    reflect_update(updates[i].x, updates[i].new_y); 
}

void undo_update(int i) { 
    reflect_update(updates[i].x, updates[i].prv_y); 
}

bool cmp(Query a, Query b) {
  return (a.lb < b.lb) || (a.lb == b.lb && a.rb < b.rb) ||
         (a.lb == b.lb && a.rb == b.rb && a.t < b.t);
}

int main() {
  int n;
  cin >> n;
  int block = pow(n, 2.0 / 3.0);
  map<int, int> mp;
  for (int i = 1; i <= n; i++) {
    cin >> A[i];
    last[i] = A[i];
    mp[A[i]];
  }
  int m;
  cin >> m;
  for (int i = 1; i <= m; i++) {
    string s;
    int x, y;
    cin >> s >> x >> y;

    if (s[0] == 'Q') {
      nq++;
      queries[nq] = {nq, x, y, nu, x / block, y / block};
    } else {
      updates[++nu] = {x, y, last[x]};
      last[x] = y;
      mp[y];
    }
  }
  // Coordinate compression.
  for (auto &it : mp) {
    it.second = ++compressed_val;
    rev[compressed_val] = it.first;
  }
  for (int i = 1; i <= n; i++) {
    A[i] = mp[A[i]];
  }
  for (int i = 1; i <= nu; i++) {
    updates[i].new_y = mp[updates[i].new_y];
    updates[i].prv_y = mp[updates[i].prv_y];
  }
  
  // Sort the queries.
  sort(queries + 1, queries + nq + 1, cmp);

  // Answer the queries.
  for (int i = 1, T = 0, L = 1, R = 0; i <= nq; i++) {
    while (T < queries[i].t) do_update(++T);
    while (T > queries[i].t) undo_update(T--);
    while (R < queries[i].r) add_element(++R);
    while (L > queries[i].l) add_element(--L);
    while (R > queries[i].r) remove_element(R--);
    while (L < queries[i].l) remove_element(L++);
    ans[queries[i].idx] = curr_ans;
  }
  for (int i = 1; i <= nq; i++) {
      cout << ans[i] << '\n';
  }
}