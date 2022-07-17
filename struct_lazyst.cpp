struct lazyST
{   
    vector<int> st, lazy;
    lazyST(int N)
    {
        st = vector<int>(N * 4 + 1, 0);
        lazy = vector<int>(N * 4 + 1, 0);
    }
    
    vector<int> a;
    void readArray(int N)
    {
        a = vector<int>(N + 1);
        for(int i = 1; i <= N; i++) cin >> a[i];
    }
    
    void buildTree(int id, int l, int r)
    {
        if(l == r)
        {
            st[id] = a[l];
            return;
        }
        
        int mid = (l + r) >> 1;
        buildTree(id * 2, l, mid);
        buildTree(id * 2  + 1, mid + 1, r);
        
        st[id] = st[id * 2] + st[id * 2 + 1];
    }
    
    void pushDown(int id, int l, int r)
    {
        st[id * 2] += lazy[id];
        lazy[id * 2] += lazy[id];
        st[id * 2 + 1] += lazy[id];
        lazy[id * 2 + 1] += lazy[id];
        lazy[id] = 0;
    }
    
    void update(int id, int l, int r, int x, int y, int c)
    {
        if(l > y || r < x || l > r || x > y) return;
        if(l >= x && r <= y)
        {
            st[id] += c;
            lazy[id] += c;
            return;
        }
        pushDown(id, l, r);
        int mid = (l + r) >> 1;
        update(id * 2, l, mid, x, y, c);
        update(id * 2 + 1, mid + 1, r, x, y, c);
        
        st[id] = st[id * 2] + st[id * 2 + 1];
        
    }
    
    int getSum(int id, int l, int r, int x, int y)
    {
        if(l > y || r < x) return 0;
        if(l >= x && r <= y) return st[id];
        
        pushDown(id, l, r);
        int mid = (l + r) >> 1;
        return getSum(id * 2, l, mid, x, y) + getSum(id * 2 + 1, mid + 1, r, x, y);
    }
};