struct LCA 
{
    int LOG = 19;
    vector<vector<int>> par, adj;
    vector<int> high;
    int N;
    vector<int> BIN;
    
    
    LCA(int _N, vector<vector<int>> temp)
    {
        par = vector<vector<int>>(_N + 1, vector<int>(LOG + 1, 0));
        high = vector<int>(_N + 1, 0);
        high[0] = -1;
        adj = temp; N = _N;
        BIN = vector<int>(20, 1);
        for(int i = 1; i <= 19; i++) BIN[i] = BIN[i - 1] * 2;
    }
    
    
    void assignHeight(int u)
    {
        for(auto i : adj[u])
        {
            if(i == par[u][0]) continue;
            par[i][0] = u;
            high[i] = high[u] + 1;
            assignHeight(i);
        }
    }
    
    
    void createBinJumping()
    {
        for(int j = 1; j <= LOG; j++)
            for(int i = 1; i <= N; i++) par[i][j] = par[par[i][j - 1]][j - 1];
    }
    
    
    int solve(int u, int v)
    {
        if(high[u] < high[v]) return solve(v, u);
        
        //balance 
        for(int i = LOG; i >= 0; i--) if(high[par[u][i]] >= high[v]) u = par[u][i];
        if(u == v) return u;
        
        //go up the same time
        for(int i = LOG; i >= 0; i--)
            if(par[u][i] != par[v][i])
            {
                u = par[u][i];
                v = par[v][i];
            }
        return par[u][0];
    }
};
