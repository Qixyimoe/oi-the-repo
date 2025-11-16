#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int M = 2e5 + 7;

int n, m, q;
int fa[M][30], siz[M], val[M];

std::vector<int> adj[M];

struct DSU {
	int fa[M];

	void init(const int _n) {
		for (int i = 1; i <= _n; i++) {
			fa[i] = i;
		}
	}

	int find(int x) {
		return (fa[x] == x ? x : fa[x] = find(fa[x]));
	}
} uni;

void dfs(int u, int from) {
	fa[u][0] = from;
	if (u <= n) { siz[u] = 1; return; }
	siz[u] = 0;
	for (auto v : adj[u]) {
		dfs(v, u);
		siz[u] += siz[v];
	}
}

void init(int u) {
	dfs(u, 0);
	val[0] = m + 1;
	for (int j = 1; j < 20; j++) {
		for (int i = 1; i <= u; i++)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
	}
}

int check(int k, int u, int v) {
	for (int i = 19; ~i; i--) {
		if (val[fa[u][i]] <= k)
			u = fa[u][i];
		if (val[fa[v][i]] <= k)
			v = fa[v][i];
	}
	if (u == v)
		return siz[u];
	return siz[u] + siz[v];
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	uni.init(n * 2); int ncnt = n;
	for (int i = 1; i <= m; i++) {
		int u, v; std::cin >> u >> v;
		u = uni.find(u), v = uni.find(v);
		if (ncnt < n * 2 - 1 && u != v) {
			ncnt++;
			val[ncnt] = i;
			uni.fa[u] = uni.fa[v] = ncnt;
			adj[ncnt].push_back(u);
			adj[ncnt].push_back(v);
		}
	}
	init(ncnt);
	std::cin >> q;
	while (q--) {
		int u, v, z; std::cin >> u >> v >> z;
		int l = 1, r = m;
		while (l < r) {
			int mid = (l + r) >> 1;
			if (check(mid, u, v) >= z)
				r = mid;
			else
				l = mid + 1;
		}
		std::cout << l << "\n";
	}
	return 0;
}
