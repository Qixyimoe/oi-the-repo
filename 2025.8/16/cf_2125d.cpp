#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;
constexpr int P = 998244353;

int n, m;
i64 pr[N], dp[N];

struct node {
    int l, r;
    i64 prob;

    bool operator < (const node &rhs) const {
        return l < rhs.l;
    }
} a[N];

template <typename T>
T expow(T a, T b) {
    T res = 1;
    for (; b; b >>= 1) {
        if (b & 1)
            res = res * a % P;
        a = a * a % P;
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 0; i <= m; i++)
        pr[i] = 1;
    for (int i = 1, p, q; i <= n; i++) {
        std::cin >> a[i].l >> a[i].r >> p >> q;
        a[i].prob = 1ll * p * expow<i64>(q, P - 2) % P;
        pr[a[i].l] = pr[a[i].l] * (1ll - a[i].prob + P) % P;
    }
    for (int i = 1; i <= m; i++) {
        pr[i] = pr[i - 1] * pr[i] % P;
    }
    std::sort(a + 1, a + n + 1);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        auto [l, r, p] = a[i];
        i64 tmp = dp[l - 1] * pr[r] % P * expow<i64>(pr[l - 1], P - 2) % P * expow<i64>((1 - p + P) % P, P - 2) % P * p % P;
        dp[r] = (dp[r] + tmp) % P;
    }
    std::cout << dp[m] << "\n";
    return 0;
}
