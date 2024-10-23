struct dinic_flow {
    struct edge {
        int node, flow;
        ll capicity, rev;
    };

    int n;
    vector<int> level, ptr;
    vector<vector<edge>> adj;

    dinic_flow(int _n = 0) {
        n = _n;
        level.assign(n + 1, 0);
        ptr.assign(n + 1, 0);
        adj.assign(n + 1, vector<edge>());
    }

    void add_edge(int cur, int next, ll capicity) {
        edge _next = {next, 0, capicity, (int) adj[next].size()};
        edge _cur = {cur, 0, 0, (int) adj[cur].size()};
        adj[cur].push_back(_next);
        adj[next].push_back(_cur);
    }

    bool bfs(int source, int sink) {
        level.clear();
        level.resize(n + 1, 0);

        level[source] = 1;
        queue<int> q;
        q.push(source);

        while(!q.empty()) {
            auto cur = q.front();
            q.pop();

            for(const auto& next : adj[cur])
                if(!level[next.node] && next.flow < next.capicity) {
                    level[next.node] = level[cur] + 1;
                    q.push(next.node);
                    if(next.node == sink) return true; 
                }
        }
        return false;
    }

    ll send_flow(int cur, ll flow, const int& sink) {
        if(cur == sink) return flow;

        for(; ptr[cur] < (int) adj[cur].size(); ptr[cur]++) {
            edge& e = adj[cur][ptr[cur]];

            if(level[e.node] == level[cur] + 1 && e.flow < e.capicity) {
                ll curFlow = min(flow, e.capicity - e.flow);
                ll tempFlow = send_flow(e.node, curFlow, sink);

                if(tempFlow > 0) {
                    e.flow += tempFlow;
                    adj[e.node][e.rev].flow -= tempFlow;
                    return tempFlow;
                }
            }
        }
        return 0;
    }

    ll find_max_flow(int source, int sink) {
        ll maxFlow = 0;
        while(bfs(source, sink)) {
            ptr.clear();
            ptr.assign(n + 1, 0);
            while(ll pushed = send_flow(source, INT_MAX, sink))
                maxFlow += pushed;
        }
        return maxFlow;
    }
};
