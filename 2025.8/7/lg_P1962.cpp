#include <bits/stdc++.h>

#define int long long

constexpr int P = 1e9 + 7;

int n;

struct Matrix {
    int m[5][5];

    void I() {
        for (int i = 1; i <= 2; i++) {
            for (int j = 1; j <= 2; j++)
                m[i][j] = (i == j ? 1 : 0);
        }
    }

    friend Matrix operator * (const Matrix &a, const Matrix &b) {
        Matrix res;
        memset(res.m, 0, sizeof(res.m));
        for (int i = 1; i <= 2; i++) {
            for (int j = 1; j <= 2; j++) {
                for (int k = 1; k <= 2; k++) {
                    res.m[i][j] += a.m[i][k] * b.m[k][j] % P;
                    res.m[i][j] %= P;
                }
            }
        }
        return res;
    }
} ans, bas;

void init() {
    bas.m[1][1] = bas.m[1][2] = 1;
    bas.m[2][1] = 1;
    ans.m[1][1] = 1;
    ans.m[2][1] = 1;
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

    std::cin >> n;
    if (n <= 2) {
        std::cout << "1\n";
        exit(0);
    }
    init();
    expow(n - 2);
    std::cout << ans.m[1][1] << "\n";
    return 0;
}
