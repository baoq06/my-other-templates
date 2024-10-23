const int N = 2e5 + 10;
int a[N];

struct segment_tree {
    int n;
    vector<ll> st, lazy;

    segment_tree(int _n = 0) {
        n = _n;
        st.assign(n * 4 + 1, 0);
        lazy.assign(n * 4 + 1, 0);
    }

    void build(int id, int l, int r) {
        if(l == r) {
            st[id] = a[l];
            return;
        }

        int mid = (l + r) >> 1;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);

        st[id] = st[id * 2] + st[id * 2 + 1];
    }
    void build() {
        build(1, 1, n);
    }

    void push_down(int id, int l, int r) {
        int mid = (l + r) >> 1;
        st[id * 2] += lazy[id] * (mid - l + 1);
        st[id * 2 + 1] += lazy[id] * (r - mid);
        lazy[id * 2] += lazy[id];
        lazy[id * 2 + 1] += lazy[id];
        lazy[id] = 0;
    }

    void update(int id, int l, int r, const int& x, const int& y, const ll& value) {
        if(l > y || r < x || l > r || x > y) return;
        if(l >= x && r <= y) {
            st[id] += value * (r - l + 1);
            lazy[id] += value;
            return;
        }

        push_down(id, l, r);
        int mid = (l + r) >> 1;
        update(id * 2, l, mid, x, y, value);
        update(id * 2 + 1, mid + 1, r, x, y, value);

        st[id] = st[id * 2] + st[id * 2 + 1];
    }
    void update(const int& x, const int& y, const ll& value) {
        update(1, 1, n, x, y, value);
    }

    ll get(int id, int l, int r, const int& x, const int& y) {
        if(l > y || r < x) return 0;
        if(l >= x && r <= y) return st[id];

        push_down(id, l, r);
        int mid = (l + r) >> 1;
        ll left = get(id * 2, l, mid, x, y);
        ll right = get(id * 2 + 1, mid + 1, r, x, y);

        return left + right;
    }
    ll get(const int& x, const int& y) {
        return get(1, 1, n, x, y);
    }
};
