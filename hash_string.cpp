const int N = 1e6;
const int BASE = 311;
const int MOD = 1e9 + 7;
string s, t;

struct hash_string {
    vector<int> hash, power;
    int n, BASE, MOD;
    string s;
    hash_string(string _s = "", int _BASE = 0, int _MOD = 0) {
        s =  ' ' + _s;
        n = s.size() - 1;
        BASE = _BASE;
        MOD = _MOD;
        hash.assign(n + 1, 0);  
        power.assign(N + 1, 0);
    }

    void build() {
        power[0] = 1;
        for(int i = 1; i <= N; i++)
            power[i] = (1LL * power[i - 1] * BASE) % MOD;

        hash[0] = 0;
        for(int i = 1; i <= n; i++)
            hash[i] = (hash[i - 1] + 1LL * power[i] * s[i]) % MOD;  
    }

    int get_hash(int l, int r) {
        return 1LL * (hash[r] - hash[l - 1] +  MOD) * power[N - r] % MOD;
    }
};
