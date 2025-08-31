#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	int n;
	std::cin >> n;
	std::vector<int> G[n + 1];
	for (int i = 1, u, v; i < n; i++) {
		std::cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	int c = 0;
	std::vector<int> fa(n + 1), dis(n + 1);
	std::function<void(int, int)> dfs = [&](int u, int pa) {
		fa[u] = pa;
		for (auto v : G[u]) {
			if (v == pa)
				continue;
			dis[v] = dis[u] + 1;
			if (dis[v] > dis[c])
				c = v;
			dfs(v, u);
		}
	};
	dfs(1, -1);
	dis[c] = 0;
	dfs(c, -1);
	if (dis[c] == n - 1) {
		std::cout << "-1\n";
		return;
	} else {
		std::vector<int> od(n + 1);
		int t = c;
		while (t != -1) {
			od[t] = 1;
			t = fa[t];
		}
		int x = -1, y = -1, z = -1;
		for (int u = 1; u <= n; u++) {
			for (auto v : G[u]) {
				if (od[u] && !od[v]) {
					x = fa[u], y = u, z = v;
					break;
				}
			}
			if (x != -1)
				break;
		}
		std::cout << x << " " << y << " " << z << "\n";
	}
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