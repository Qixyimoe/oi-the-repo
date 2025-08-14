#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = std::numeric_limits<int>::max();

void solve() {
    int n, x;
    std::cin >> n >> x;
    std::string s;
    std::cin >> s;
    s = '$' + s;
    if (x == 1 || x == n) { std::cout << "1\n"; return; }
    int l = -inf, r = inf;
    for (int i = x; i >= 1; i--) {
        if (s[i] == '#') {
            l = i;
            break;
        }
    }
    for (int i = x; i <= n; i++) {
        if (s[i] == '#') {
            r = i;
            break;
        }
    }
    if (l == -inf && r == inf) { std::cout << "1\n"; return; }
    std::cout << std::max(std::min(x, n - r + 2), std::min(l + 1, n - x + 1)) << "\n";
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
