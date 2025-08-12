#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    std::vector<int> s(n + 1);
    auto check = [&](int x) -> std::pair<int, int> {
        std::vector<int> s(n + 1);
        for (int i = 1; i <= n; i++) {
            s[i] = (a[i] >= x ? 1 : -1);
            s[i] += s[i - 1];
        }
        int p = 0;
        for (int i = k; i <= n; i++) {
            if (s[i - k] < s[p])
                p = i - k;
            if (s[i] - s[p] >= 0)
                return {p + 1, i};
        }
        return {0, 0};
    };
    int l = 1, r = n + 1, ans = 0;
    std::pair<int, int> tp;
    while (l < r) {
        int mid = (l + r) >> 1;
        auto it = check(mid);
        if (it.first) {
            l = mid + 1;
            ans = mid;
            tp = it;
        } else
            r = mid;
    }
    std::cout << ans << " " << tp.first << " " << tp.second << "\n";
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
