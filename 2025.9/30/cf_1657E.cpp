#include <bits/stdc++.h>

#define int long long

constexpr int N = 507;
constexpr int P = 998244353;

int n, k;
int c[N][N], f[N][N];

template <typename T>
T expow(T a, T b) {
	T res = 1;
	for (; b; b >>= 1) {
		if (b & 1)
			res = 1ll * res * a % P;
		a = 1ll * a * a % P;
	}
	return res;
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> k;
	n--;
	f[k + 1][0] = 1;
	for (int i = 0; i <= 300; i++) {
		c[i][i] = c[i][0] = 1;
		for (int j = 1; j < i; j++) {
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % P;
		}
	}
	for (int i = k; i; i--) {
		for (int j = 0; j <= n; j++)
			for (int k = 0; k + j <= n; k++)
				f[i][j + k] = (f[i][j + k] + f[i + 1][j] * expow(i, j * k + k * (k - 1) / 2) % P * c[n - j][k]) % P;
	}
	std::cout << f[1][n] << "\n";
	return 0;
}
