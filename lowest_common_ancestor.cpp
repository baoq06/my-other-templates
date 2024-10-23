struct lowest_common_ancestor {
    int n;
    vector<int> dep;
    vector<vector<int>> par;

    lowest_common_ancestor(int _n = 0) {
        n = _n;
        dep.assign(n + 1, 1); dep[0] = 0;
        par.assign(n + 1, vector<int>(LOG + 1, 0));
    }

    void assign_depth(int cur) {
        for(auto& next : adj[cur]) 
            if(next != par[cur][0]) {
                par[next][0] = cur;
                dep[next] = dep[cur] + 1;
                assign_depth(next);
            }
    }

    void binary_lifting() {
        for(int j = 1; j <= LOG; j++)
            for(int i = 1; i <= n; i++)
                par[i][j] = par[par[i][j - 1]][j - 1];
    }

    void build() {
        assign_depth(1);
        binary_lifting();
    }

    int get_lca(int x, int y) {
        if(dep[x] < dep[y]) return get_lca(y, x);
        for(int i = LOG; i >= 0; i--)
            if(dep[par[x][i]] >= dep[y])
                x = par[x][i];

        if(x == y)  return x;

        for(int i = LOG; i >= 0; i--)
            if(par[x][i] != par[y][i]) {
                x = par[x][i];
                y = par[y][i];
            }

        return par[x][0];
    }
};
