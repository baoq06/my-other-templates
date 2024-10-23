const int N = 1e5 + 10;
int a[N];

struct segment_tree {
    vector<int> st;
    int n;

    segment_tree(int _n = 0) {
        n = _n;
        st.assign(n * 4 + 1, 0);
    }

    void build(int id, int l, int r) {
        if(l == r) {
            st[id] = a[l];
            return;
        }

        int mid = (l + r) >> 1;
        build(id * 2, l, mid);
        build(id * 2 + 1, mid + 1, r);

        st[id] = max(st[id * 2], st[id * 2 + 1]);
    }
    void build() {
        build(1, 1, n);
    }

    void update(int id, int l, int r, const int& pos, const int& value) {
        if(l > pos || r < pos) return;
        if(l == r) {
            st[id] = value;
            return;
        }

        int mid = (l + r) >> 1;
        update(id * 2, l, mid, pos, value);
        update(id * 2 + 1, mid + 1, r, pos, value);

        st[id] = max(st[id * 2], st[id * 2 + 1]);
    }
    void update(const int& pos, const int& value) {
        update(1, 1, n, pos, value);
    }

    int get(int id, int l, int r, const int& x, const int& y) {
        if(l > y || r < x) return INT_MIN;
        if(l >= x && r <= y) return st[id];

        int mid = (l + r) >> 1;
        int retLeft = get(id * 2, l, mid, x, y);
        int retRight = get(id * 2 + 1, mid + 1, r, x, y);
        
        return max(retLeft, retRight);
    }
    int get(const int& x, const int& y) {
        return get(1, 1, n, x, y);
    }
};
