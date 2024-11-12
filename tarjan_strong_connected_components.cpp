const int N = 1e5 + 10;
vector<int> adj[N];
int ans = 0, low[N], num[N];
stack<int> st;

int cnt = 0;
void tarjan(int cur) {
    low[cur] = num[cur] = ++cnt;
    st.push(cur);

    for(auto& next : adj[cur])
        if(num[next]) 
            minimize(low[cur], num[next]);
        else {
            tarjan(next);
            minimize(low[cur], low[next]);
        }

    if(num[cur] == low[cur]) {
        ans++;
        int temp = 0;
        do {
            temp = st.top();
            st.pop();
            low[temp] = num[temp] = INT_MAX;
        }
        while(temp != cur);
    }
}
