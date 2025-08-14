#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> col(n + 1), fa(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> col[i];
    }
    std::vector<std::pair<int, int>> G[n + 1];
    std::map<std::pair<int, int>, int> E;
    for (int i = 1, u, v, w; i < n; i++) {
        std::cin >> u >> v >> w;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
        E[{u, v}] = E[{v, u}] = w;
    }
    i64 ans = 0;
    std::map<int, i64> s[n + 1];
    std::function<void(int, int)> dfs = [&](int u, int pa) {
        fa[u] = pa;
        for (auto [v, w] : G[u]) {
            if (v == pa)
                continue;
            if (col[u] != col[v])
                ans += w;
            s[u][col[v]] += w;
            dfs(v, u);
        }
    };
    dfs(1, 0);
    for (int i = 1, v, x; i <= q; i++) {
        std::cin >> v >> x;
        if (col[v] == x) {
            std::cout << ans << "\n";
            continue;
        }
        int w = E[{v, fa[v]}];
        if (fa[v] && col[fa[v]] == x) {
            ans -= w;
        } else if (fa[v] && col[v] == col[fa[v]]) {
            ans += w;
        }
        s[fa[v]][x] += w, s[fa[v]][col[v]] -= w;
        ans = ans + s[v][col[v]] - s[v][x];
        col[v] = x;
        std::cout << ans << "\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
