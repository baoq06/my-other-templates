const int N = 2e5 + 10;
ll a[N];

struct heavy_light_decomposition {
    int n;
    vector<ll> st;
    vector<int> heavy, head, pos, dep, par;
    vector<vector<int>> adj;

    heavy_light_decomposition(int _n = 0) {
        n = _n;
        st.assign(n * 4 + 1, 0);
        heavy.assign(n + 1, -1);
        head.assign(n + 1, 0);
        pos.assign(n + 1, 0);
        dep.assign(n + 1, 0);
        par.assign(n + 1, 0);
        adj.assign(n + 1, vector<int>());
    }

    void add_edge(int x, int y) {
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    int dfs(int cur) {
        int mx = -1, sz = 1;
        for(auto& next : adj[cur]) {
            if(next == par[cur]) continue;
            par[next] = cur;
            dep[next] = dep[cur] + 1;
            int c = dfs(next);
            sz += c;
            if(c > mx) 
                mx = c,
                heavy[cur] = next;
        }
        return sz;
    }

    int cntPos = 0;
    void decompose(int cur, int h) {
        head[cur] = h;
        pos[cur] = ++cntPos;
        if(heavy[cur] != -1)
            decompose(heavy[cur], h);

        for(auto& next : adj[cur])
            if(next != par[cur] && next != heavy[cur])
                decompose(next, next);
    }

    void update(int id, int l, int r, int p, ll value) {
        if(l > p || r < p) return;
        if(l == r) {
            // cout << "z " << p << ' ' << value << '\n';
            st[id] = value;
            return;
        }

        int mid = (l + r) >> 1;
        update(id * 2, l, mid, p, value);
        update(id * 2 + 1, mid + 1, r, p, value);

        st[id] = st[id * 2] + st[id * 2 + 1];
    }
    void update(int p, ll value) {
        update(1, 1, n, p, value);
    }

    ll get_sum(int id, int l, int r, const int& x, const int& y) {
        if(l > y || r < x) return 0;
        if(l >= x && r <= y) return st[id];

        ll mid = (l + r) >> 1;
        ll retLeft = get_sum(id * 2, l, mid, x, y);
        ll retRight = get_sum(id * 2 + 1, mid + 1, r, x, y);
        
        return retLeft + retRight;
    }
    ll get_sum(const int& x, const int& y) {
        return get_sum(1, 1, n, x, y);
    }

    ll query(int x, int y) {
        ll ret = 0;
        while(head[x] != head[y]) {
            if(dep[head[x]] < dep[head[y]]) swap(x, y);
            ret += get_sum(pos[head[x]], pos[x]);
            x = par[head[x]];
        }

        if(dep[x] > dep[y]) swap(x, y);
        ret += get_sum(pos[x], pos[y]);
        return ret;
    }

    void build() {
        dfs(1);
        decompose(1, 1);
        for(int i = 1; i <= n; i++)
            update(pos[i], a[i]);       
    }
};
//update nho doi vi tri i thanh pos[i]
