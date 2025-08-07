#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e2 + 7;
constexpr int P = 2017;

int n, m, t;
int ans;

struct Matrix {
    int a[N][N];

    void I() {
        for (int i = 0; i <= n; i++) {
            a[i][i] = 1;
            a[i][0] = 1;
        }
    }

    friend Matrix operator * (const Matrix &a, const Matrix &b) {
        Matrix res;
        memset(res.a, 0, sizeof(res.a));
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                for (int k = 0; k <= n; k++) {
                    res.a[i][j] += a.a[i][k] * b.a[k][j] % P;
                    res.a[i][j] %= P;
                }
            }
        }
        return res;
    }
} mat;

void expow(int b) {
    Matrix bas = mat;
    for (; b; b >>= 1) {
        if (b & 1)
            mat = mat * bas;
        bas = bas * bas;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    mat.I();
    for (int i = 1, u, v; i <= m; i++) {
        std::cin >> u >> v;
        mat.a[u][v] = mat.a[v][u] = 1;
    }
    std::cin >> t;
    expow(t - 1);
    for (int i = 0; i <= n; i++) {
        ans += mat.a[1][i];
        ans %= P;
    }
    std::cout << ans << "\n";
    return 0;
}
