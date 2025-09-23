#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n;
int w[N], f[N];

std::vector<int> adj[N];

int dfs(int u) {
	if (!adj[u].size()) {
		f[u] = w[u];
		return 0;
	}
	std::vector<std::pair<int, int>> vec;
	for (auto v : adj[u]) {
		int _w = dfs(v);
		vec.push_back({_w, w[v]});
	}
	std::sort(vec.begin(), vec.end(), std::greater<std::pair<int, int>>());
	int cst = 0, res = 0;
	for (auto [x, y] : vec) {
		if (res < x + y) {
			cst += x + y - res;
			res = x;
		} else {
			res -= y;
		}
	}
	if (res < w[u])
		cst += w[u] - res;
	f[u] = cst;
	return cst - w[u];
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 2, x; i <= n; i++) {
		std::cin >> x;
		adj[x].push_back(i);
	}
	for (int i = 1; i <= n; i++) {
		std::cin >> w[i];
	}
	dfs(1);
	for (int i = 1; i <= n; i++) {
		std::cout << f[i] << " ";
	}
	std::cout << "\n";
	return 0;
}
