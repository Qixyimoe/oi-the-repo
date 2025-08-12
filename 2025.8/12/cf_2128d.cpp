#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> p(n + 1);
    for (int i = 1; i <= n; i++)
        std::cin >> p[i];
    std::vector<i64> f(n + 1, 1);
    if (p[2] < p[1]) f[2] = 3;
    else f[2] = 2;
    i64 ans = f[1] + f[2];
    for (int i = 3, j; i <= n; i++) {
        if (p[i - 1] > p[i]) { j = i - 1; }
        else { j = i - 2; f[i]++; }
        f[i] += f[j] + j;
        ans += f[i];
    }
    std::cout << ans << "\n";
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
