#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n;
i64 ans, g[N];

std::queue<int> q, p;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	g[0] = -1;
	for (int i = 1; i <= n; i++) {
		std::cin >> g[i];
		int lst = 0;
		while (q.size()) {
			int x = q.front();
			q.pop();
			g[x] = std::__gcd(g[x], g[i]);
			ans = std::max(ans, g[x] * (i - x + 1));
			if (g[x] == g[lst])
				continue;
			p.push(x);
			lst = x;
		}
		ans = std::max(ans, g[i]);
		while (p.size()) {
			q.push(p.front());
			p.pop();
		}
		if (g[lst] != g[i])
			q.push(i);
	}
	std::cout << ans << "\n";
	return 0;
}
