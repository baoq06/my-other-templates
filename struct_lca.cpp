struct LCA
{
    vector<vector<int>> parent;
    vector<int> depth;
    int n;

    LCA(const int& _n = 0)
    {
        n = _n;
        parent.assign(n + 1, vector<int>(LOG + 1, 0));
        depth.assign(n + 1, 0);
        depth[0] = -1;
    }

    void assignDepth(int u)
    {
        for(auto& v : adj[u])
        {
            if(v == parent[u][0]) continue;
            parent[v][0] = u;
            depth[v] = depth[u] + 1;
            assignDepth(v);
        }
    }

    void binLifting()
    {
        for(int j = 1; j <= LOG; j++)
            for(int i = 1; i <= n; i++)
                parent[i][j] = parent[parent[i][j - 1]][j - 1];
    }

    void process() {assignDepth(1); binLifting();}
    int query(int u, int v)
    {
        if(depth[u] < depth[v]) return query(v, u);
        for(int i = LOG; i >= 0; i--)
            if(depth[parent[u][i]] >= depth[v]) u = parent[u][i];
        
        if(u == v) return u;

        for(int i = LOG; i >= 0; i--)
            if(parent[u][i] != parent[v][i])
            {
                u = parent[u][i];
                v = parent[v][i];
            }
        return parent[u][0];
    }
};
