#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int l = 0, r = 0;
        for (int j = 1; j < i; j++)
            l += (a[j] > a[i] ? 1 : 0);
        for (int j = i + 1; j <= n; j++)
            r += (a[j] > a[i] ? 1 : 0);
        ans += std::min(l, r);
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
