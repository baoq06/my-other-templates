const int MOD = 1e9 + 7;

struct matrix {
    vector<vector<int>> data;
    int MOD;

    int row() const {
        return data.size();
    }

    int col() const {
        return data[0].size();
    }

    auto & operator [] (int i) {
        return data[i];
    }

    const auto & operator [] (int i) const {
        return data[i];
    }

    matrix() = default;

    matrix(int r, int c, int _MOD) {
        MOD = _MOD;
        data.assign(r, vector<int>(c, 0));
    }
    matrix(const vector<vector<int>> &d): data(d) {}

    friend ostream & operator << (ostream &out, const matrix &d) {
        for(auto x : d.data) {
            for(auto y : x) out << y << ' ';
            out << '\n';
        }
        return out;
    }

    matrix identity(ll n) {
        matrix a = matrix(n, n, MOD);
        while(n--) a[n][n] = 1;
        return a;
    }

    matrix operator * (const matrix &b) {
        matrix a = *this;
        matrix c(a.row(), b.col(), MOD);

        for(int i = 0; i < a.row(); i++)
            for(int j = 0; j < b.col(); j++)
                for(int k = 0; k < a.col(); k++) {
                    c[i][j] += 1LL * a[i][k] % MOD * (b[k][j] % MOD) % MOD;
                    c[i][j] %= MOD;
                }
        return c;
    }

    matrix pow(ll exp) {
        matrix base = *this, ans = identity(row());
        for(; exp > 0; exp >>= 1, base = base * base)
            if(exp & 1) ans = ans * base;
        return ans;
    }
};
