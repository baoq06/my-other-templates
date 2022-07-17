struct Hash
{
    int n;
    vector<ll> h; 
    Hash(int _n)
    {
        h = vector<ll>(_n + 1, 0);
        n = _n;
    }
    
    void buildHash(string s, int size)
    {
        h[0] = 0;
        for(int i = 1; i <= size; i++) 
            h[i] = (h[i - 1] + 1LL * s[i - 1] * POW[i]) % MOD;
    }
    
    ll getHash(int i, int j)
    {
        return 1LL * (h[j] - h[i - 1] + MOD) * POW[n - j] % MOD;
    }
};