struct SegTree
{
    vector<long> st;
    int n;

    SegTree(int _n)
    {
        n = _n;
        st.assign(n * 4 + 1, 0);
    }

    void update(int id, int l, int r, int pos, int val)
    {
        if(l > pos || r < pos) return;
        if(l == r)
        {
            st[id] = val;
            return;
        }

        int mid = (l + r) >> 1;
        update(id * 2, l, mid, pos, val);
        update(id * 2 + 1, mid + 1, r, pos, val);

        st[id] = st[id * 2] + st[id * 2 + 1];
    }

    long getSum(int id, int l, int r, int x, int y)
    {
        if(l > y || r < x) return 0;
        if(l >= x && r <= y) return st[id];

        int mid = (l + r) >> 1;
        return getSum(id * 2, l, mid, x, y) + getSum(id * 2 + 1, mid + 1, r, x, y);
    }

    void update(int pos, int val) {update(1, 1, n, pos, val);}
    long getSum(int x, int y) {return getSum(1, 1, n, x, y);}
    long query(int x, int y)
    {
        long sum = 0;
        while(head[x] != head[y])
        {
            if(depth[head[x]] < depth[head[y]]) swap(x, y);
            sum += getSum(pos[head[x]], pos[x]);
            x = parent[head[x]];
        }

        if(depth[x] > depth[y]) swap(x, y);
        sum += getSum(pos[x], pos[y]);
        return sum;
    }
};

int DFS(int u)
{
    int mx = -1; int sz = 1;
    for(auto& v : adj[u])
    {
        if(v == parent[u]) continue;
        parent[v] = u;
        depth[v] = depth[u] + 1;
        int c = DFS(v);
        sz += c;
        if(c > mx) mx = c, heavy[u] = v;
    }
    return sz;
}

int cnt_pos = 0;
void HLD(int u,  int h)
{
	head[u] = h; pos[u] = ++cnt_pos;
	if(heavy[u] != -1)
		HLD(heavy[u], h);

	for(auto v : adj[u])
		if(v != parent[u] && v != heavy[u])
			HLD(v, v);
}
