#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = std::numeric_limits<int>::max();

void solve() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> b[i];
    }
    i64 res = 0;
    std::vector<std::pair<int, int>> vec;
    for (int i = 1; i <= n; i++) {
        if (a[i] > b[i])
            std::swap(a[i], b[i]);
        res += (b[i] - a[i]);
        vec.push_back({a[i], b[i]});
    }
    std::sort(vec.begin(), vec.end());
    for (auto i = 1; i < n; i++) {
        if (vec[i].first <= vec[i - 1].second) {
            std::cout << res << "\n";
            return;
        }
    }
    int dis = inf;
    for (auto i = 1; i < n; i++) {
        dis = std::min(dis, vec[i].first - vec[i - 1].second);
    }
    std::cout << res + (dis << 1) << "\n";
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
