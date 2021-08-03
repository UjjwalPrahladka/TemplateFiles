#include <bits/stdc++.h> 
using namespace std; 
const int MAX = 2e5;
const int LOG = 18;
vector<int> adj[MAX+1];
int lev[MAX+1];
int memo[MAX+1][LOG+1];
int start_time[MAX+1], end_time[MAX+1];
int dfs_time = 0;

void dfs(int u, int p){
    if(p == u) lev[u] = 0;
    memo[u][0] = p; 
    for (int i = 1; i <= LOG; i++) 
        memo[u][i] = memo[memo[u][i - 1]][i - 1]; 
    
    start_time[u] = dfs_time++;

    for(int v : adj[u]){
        if(v != p){
            lev[v] = lev[u] + 1; 
            dfs(v, u);
        }
    }

    end_time[u] = dfs_time++;
}

int lca(int u, int v){ 
    if (lev[u] < lev[v]) 
        swap(u, v); 
  
    for (int i = LOG; i >= 0; i--) 
        if ((lev[u] - pow(2, i)) >= lev[v]) 
            u = memo[u][i]; 
  
    if (u == v) 
        return u; 
  
    for (int i = LOG; i >= 0; i--) { 
        if (memo[u][i] != memo[v][i]) { 
            u = memo[u][i]; 
            v = memo[v][i]; 
        } 
    } 

    return memo[u][0]; 
}

vector<int> adj_at[MAX+1];
int special[MAX+1];

bool isAncestor(int u, int v){
    return start_time[u] <= start_time[v] && end_time[v] <= end_time[u];
}

int root(vector<int>& vert){

    int k = vert.size();
    sort(vert.begin(), vert.end(), [&](int x, int y){ return start_time[x] < start_time[y];});

    for(int i = 0; i < k-1; i++){
        vert.push_back(lca(vert[i], vert[i+1]));
    }

    vert.erase(unique(vert.begin(), vert.end()), vert.end());

    sort(vert.begin(), vert.end(), [&](int x, int y){ return start_time[x] < start_time[y]; });

    for(int x : vert) adj_at[x].clear();

    vector<int> stack_of_vertices;
    stack_of_vertices.push_back(vert[0]);

    for(int i = 1; i < (int) vert.size(); i++){

        while(stack_of_vertices.size() >= 2 && !isAncestor(stack_of_vertices.back(), vert[i])){
            
            adj_at[stack_of_vertices[stack_of_vertices.size() - 1]].push_back(stack_of_vertices[stack_of_vertices.size() - 2]);
            adj_at[stack_of_vertices[stack_of_vertices.size() - 2]].push_back(stack_of_vertices[stack_of_vertices.size() - 1]);

            stack_of_vertices.pop_back();
        }

        stack_of_vertices.push_back(vert[i]);

    }

    while(stack_of_vertices.size() >= 2 ){
            
        adj_at[stack_of_vertices[stack_of_vertices.size() - 1]].push_back(stack_of_vertices[stack_of_vertices.size() - 2]);
        adj_at[stack_of_vertices[stack_of_vertices.size() - 2]].push_back(stack_of_vertices[stack_of_vertices.size() - 1]);

        stack_of_vertices.pop_back();
    }

    return stack_of_vertices[0];
}

int sub_size[MAX+1];
int total_cnt = 0;

int solve(int u){

    int ans = 0;

    sub_size[u] = special[u] ? 1 : 0;


    for(int v : adj_at[u]){
        if(v != par){
            ans += solve(v, u);
            sub_size[u] += sub_size[v];
        }
    }


    if(u != par){
        int w = lev[u] - lev[par];
        ans += (w * (total_cnt - sub_size[u]) * sub_size[u]);
    }

    return ans;
}

int32_t main(){
    int n;
    cin >> n;
    for(int i = 0; i < n-1; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(0, 0);

    int q;
    cin >> q;
    while(q--){
        int k;
        cin >> k;
        vector<int> vert;
        while(k--){
            int x;
            cin >> x;
            x--;
            special[x] = true;
            vert.push_back(x);
        }

        total_cnt = vert.size();
        int aux_root = root(vert);
        cout << solve(aux_root, aux_root) << '\n';

        for(int x : vert) special[x] = false;
    }
}

