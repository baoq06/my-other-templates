struct disjoint_set_union {
    int n;
    vector<int> e;

    disjoint_set_union(int _n = 0) {
        n = _n;
        e.assign(n + 1, -1);
    }

    int get(int cur) {
        return e[cur] < 0 ? cur : e[cur] = get(e[cur]);
    }

    bool connected(int x, int y) {
        return get(x) == get(y);
    }

    int size(int cur) {
        return -e[get(cur)];
    }

    bool unite(int x, int y) {
        x = get(x);
        y = get(y);
        if(x == y) return 0;
        if(e[x] > e[y]) swap(x, y);
        e[x] += e[y]; e[y] = x;
        return 1;
    }
};
