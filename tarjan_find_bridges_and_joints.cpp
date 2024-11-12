const int N = 1e5 + 10;
vector<int> adj[N];
int numJoint = 0, numEdge = 0, low[N], num[N];
bool node[N];

int cnt = 0;
void tarjan(int cur, int par) {
    int numChild = 0;
    low[cur] = num[cur] = ++cnt;

    for(auto& next : adj[cur]) {
        if(next == par) continue;
        if(num[next])
            minimize(low[cur], num[next]);
        else {
            tarjan(next, cur);
            numChild++;
            minimize(low[cur], low[next]);

            if(low[next] >= num[next])
                numEdge++;

            if(cur == par) {
                if(numChild >= 2)
                    node[cur] = true;
            }
            else if(low[next] >= num[cur])
                node[cur] = true;
        }
    }
}
