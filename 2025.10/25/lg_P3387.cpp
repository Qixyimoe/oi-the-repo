#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e4 + 7;

int n, m;
int scc, idx, ans;
int w[N], dp[N], ind[N];
int bel[N], val[N], ink[N];
int dfn[N], low[N];

std::stack<int> stc;
std::vector<int> adj1[N], adj2[N];

void addedge(int u, int v, int o) { o == 1 ? adj1[u].push_back(v) : adj2[u].push_back(v); return; }

void tarjan(int u) {
    dfn[u] = low[u] = ++idx;
    stc.push(u); ink[u] = 1;
    for (auto v : adj1[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        } else if (ink[v]) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        scc++; int x = 0;
        do {
            x = stc.top(); stc.pop();
            ink[x] = 0; val[scc] += w[x]; bel[x] = scc;
        } while (x != u);
    }
}

void topo() {
    std::queue<int> q;
    for (int i = 1; i <= scc; i++) {
        if (!ind[i]) { q.push(i); dp[i] = val[i]; }
    }
    while (q.size()) {
        int u = q.front(); q.pop();
        for (auto v : adj2[u]) {
            dp[v] = std::max(dp[v], dp[u] + val[v]);
            ind[v]--;
            if (!ind[v])
                q.push(v);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> w[i];
    }
    for (int i = 1, x, y; i <= m; i++) {
        std::cin >> x >> y;
        addedge(x, y, 1);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i])
            tarjan(i);
    }
    for (int i = 1; i <= n; i++) {
        for (auto j : adj1[i]) {
            if (bel[i] == bel[j])
                continue;
            addedge(bel[i], bel[j], 2);
            ind[bel[j]]++;
        }
    }
    topo();
    for (int i = 1; i <= scc; i++) {
        ans = std::max(ans, dp[i]);
    }
    std::cout << ans << "\n";
    return 0;
}
