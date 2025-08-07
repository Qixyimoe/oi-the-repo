#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 55;
constexpr int P = 10000;

int n, m, s, t, k, f;
int w[N], G[N][N];

struct Matrix {
    int a[N][N];

    void I() {
        for (int i = 1; i <= n; i++)
            a[i][i] = 1;
    }

    friend Matrix operator * (const Matrix &a, const Matrix &b) {
        Matrix res;
        memset(res.a, 0, sizeof(res.a));
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= n; k++) {
                    res.a[i][j] += a.a[i][k] * b.a[k][j] % P;
                    res.a[i][j] %= P;
                }
            }
        }
        return res;
    }
} ans, bas, g[N];

void expow(int b) {
    ans.I();
    for (; b; b >>= 1) {
        if (b & 1)
            ans = ans * bas;
        bas = bas * bas;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m >> s >> t >> k;
    s++, t++;
    for (int i = 1, x, y; i <= m; i++) {
        std::cin >> x >> y;
        x++, y++;
        for (int j = 1; j <= 12; j++) {
            g[j].a[x][y] = g[j].a[y][x] = 1;
        }
    }
    std::cin >> f;
    for (int c = 1, x; c <= f; c++) {
        std::cin >> x;
        for (int i = 1; i <= x; i++) {
            std::cin >> w[i];
            w[i]++;
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= 12; j++)
                g[j].a[i][w[j % x + 1]] = 0;
        }
    }
    bas.I();
    for (int i = 1; i <= 12; i++)
        bas = bas * g[i];
    expow(k / 12);
    for (int i = 1; i <= k % 12; i++)
        ans = ans * g[i];
    std::cout << ans.a[s][t] << "\n";
    return 0;
}
