#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, m, idx, ans;
int dfn[N], low[N], flg[N];

std::vector<int> adj[N];

void addedge(int u, int v) { adj[u].push_back(v); }

void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++idx;
    int ch = 0;
    for (auto v : adj[u]) {
        if (!dfn[v]) {
            ch++;
            tarjan(v, u);
            low[u] = std::min(low[u], low[v]);
            if (u != fa && low[v] >= dfn[u] && !flg[u]) {
                ans++;
                flg[u] = 1;
            }
        } else if (v != fa) {
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if (fa == u && ch > 1 && !flg[u]) {
        ans++;
        flg[u] = 1;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1, u, v; i <= m; i++) {
        std::cin >> u >> v;
        addedge(u, v);
        addedge(v, u);
    }
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            idx = 0;
            tarjan(i, i);
        }
    }
    std::cout << ans << "\n";
    for (int i = 1; i <= n; i++) {
        if (flg[i])
            std::cout << i << " ";
    }
    std::cout << "\n";
    return 0;
}
