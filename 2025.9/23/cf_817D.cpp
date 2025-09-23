#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 7;

int n;
i64 ans;
i64 f[N], g[N];

std::stack<std::pair<int, i64>> h1, h2;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1, x; i <= n; i++) {
		std::cin >> x;
		while (h1.size() && x >= h1.top().first)
			h1.pop();
		while (h2.size() && x <= h2.top().first)
			h2.pop();
		int j1 = h1.empty() ? 0 : h1.top().second,
			j2 = h2.empty() ? 0 : h2.top().second;
		f[i] = f[j1] + (i64) x * (i - j1);
		g[i] = g[j2] + (i64) x * (i - j2);
		ans += f[i] - g[i];
		h1.push({x, i});
		h2.push({x, i});
	}
	std::cout << ans << "\n";
	return 0;
}
