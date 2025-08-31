#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		b[i] = a[i] - a[i - 1];
	}
	i64 s1 = 0, s2 = 0;
	for (int i = 2; i <= n; i++) {
		if (b[i] > 0)
			s1 += b[i];
		else
			s2 -= b[i];
	}
	std::cout << std::max(s1, s2) << "\n" << std::abs(s1 - s2) + 1 << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	solve();
	return 0;
}
