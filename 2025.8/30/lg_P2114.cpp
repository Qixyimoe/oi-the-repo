#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, m;
int a, b, ans;

std::string s;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	a = 0, b = -1;
	for (int i = 1, x; i <= n; i++) {
		std::cin >> s >> x;
		if (s == "OR") {
			a |= x, b |= x;
		} else if (s == "XOR") {
			a ^= x, b ^= x;
		} else if (s == "AND") {
			a &= x, b &= x;
		}
	}
	for (int j = 30; j >= 0; j--) {
		if (a >> j & 1) {
			ans += (1 << j);
		}
		else if ((b >> j & 1) && ((1 << j) <= m)) {
			ans += (1 << j);
			m -= (1 << j);
		}
	}
	std::cout << ans << "\n";
	return 0;
}
