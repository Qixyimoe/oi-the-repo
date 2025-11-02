#include <bits/stdc++.h>

#define int long long

constexpr int N = 3e6 + 7;
constexpr int R = 2e6;
constexpr int P = 998244353;

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

int fac[N], inv[N];
void init() {
	fac[0] = 1;
	for (int i = 1; i <= R; i++)
		fac[i] = fac[i - 1] * i % P;
	inv[R] = expow(fac[R], P - 2);
	for (int i = R; i; i--)
		inv[i - 1] = inv[i] * i % P;
}

int C(int n, int m) {
	if (n < m || n < 0 || m < 0)
		return 0;
	return (fac[n] * inv[m] % P * inv[n - m] % P) % P;
}

void solve() {
	int n; std::cin >> n;
	int res1 = (n - 1) * C(2 * n - 3, n - 1) % P,
		res2 = -(n - 3) * C(2 * n - 4, n - 3) % P;
	std::cout << (res1 + res2 + P) % P << "\n";
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	init();
	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
