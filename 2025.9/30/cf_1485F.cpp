#include <bits/stdc++.h>

using i64 = long long;

constexpr int P = 1e9 + 7;

void solve() {
	int n;
	std::cin >> n;
	std::vector<int> b(n + 1);
	for (int i = 1; i <= n; i++) {
		std::cin >> b[i];
	}
	std::map<i64, i64> f;
	f[0] = 1;
	i64 mov = 0, ans = 1;
	for (int i = 1; i <= n; i++) {
		i64 res = (ans - f[mov] + P) % P;
		ans = (ans + res) % P;
		f[mov] = (f[mov] + res) % P;
		mov -= b[i];
	}
	ans = (ans + P) % P;
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
