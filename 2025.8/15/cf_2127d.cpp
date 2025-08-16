#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;
constexpr int P = 1e9 + 7;

int fac[N];

void init() {
    fac[0] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = (1ll * fac[i - 1] * i) % P;
    }
}

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> G[n + 1];
    for (int i = 1, u, v; i <= m; i++) {
        std::cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);    
    }
    int cnt = 0;
    i64 ans = (m >= n ? 0 : 2);
    for (int u = 1; u <= n; u++) {
        if (G[u].size() > 1) {
            int x = 0;
            for (auto v : G[u]) {
                x += (G[v].size() == 1);
            }
            if (x >= G[u].size() - 2)
                ans = ans * fac[x] % P;
            else
                ans = 0;
        } else {
            cnt++;
        }
    }
    cnt = (cnt < n - 1 ? 2 : 1);
    std::cout << (ans * cnt % P) << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    init();

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
