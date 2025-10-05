#include <bits/stdc++.h>

using i64 = long long;
using f64 = double;

constexpr int N = 1e5 + 7;

int n;
f64 p[N];
f64 x1[N], x2[N], ans[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> p[i];
	}
	for (int i = 1; i <= n; i++) {
		x1[i] = (x1[i - 1] + 1) * p[i];
		x2[i] = (x2[i - 1] + 2 * x1[i - 1] + 1) * p[i];
		ans[i] = ans[i - 1] + (3 * (x1[i - 1] + x2[i - 1]) + 1) * p[i];
	}
	std::cout << std::fixed << std::setprecision(1)
		<< ans[n] << "\n";
	return 0;
}
