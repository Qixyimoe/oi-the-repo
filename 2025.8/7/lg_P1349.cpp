#include <bits/stdc++.h>

#define int long long

int p, q, a1, a2, n, m;

struct Matrix {
    int a[5][5];

    void I() {
        for (int i = 1; i <= 2; i++) {
            for (int j = 1; j <= 2; j++)
                a[i][j] = (i == j ? 1 : 0);
        }
    }

    friend Matrix operator * (const Matrix &a, const Matrix &b) {
        Matrix res;
        memset(res.a, 0, sizeof(res.a));
        for (int i = 1; i <= 2; i++) {
            for (int j = 1; j <= 2; j++) {
                for (int k = 1; k <= 2; k++) {
                    res.a[i][j] += a.a[i][k] * b.a[k][j] % m;
                    res.a[i][j] %= m;
                }
            }
        }
        return res;
    }
} ans, bas;

void init() {
    ans.a[1][1] = a2, ans.a[2][1] = a1;
    bas.a[1][1] = p, bas.a[1][2] = q;
    bas.a[2][1] = 1;
}

void expow(int b) {
    for (; b; b >>= 1) {
        if (b & 1)
            ans = bas * ans;
        bas = bas * bas;
    }
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> p >> q >> a1 >> a2 >> n >> m;
    if (n == 1) { std::cout << a1 << "\n"; exit(0); }
    if (n == 2) { std::cout << a2 << "\n"; exit(0); }
    init();
    expow(n - 2);
    std::cout << ans.a[1][1] % m << "\n";
    return 0;
}
