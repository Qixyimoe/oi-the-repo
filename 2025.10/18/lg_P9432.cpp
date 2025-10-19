#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int inf = 1e9;

int n, p, k;
int len[N], dis[N], dep[N];
int fa[N][20], st[N][20];

std::vector<std::pair<int, int>> adj[N];

struct elem {
	int u, d;

	bool operator < (const elem &rhs) const {
		return d > rhs.d;
	}
};

void addedge(int u, int v, int w) { adj[u].push_back({v, w}); }

void dij() {
	std::priority_queue<elem> q;
	memset(dis, 0x3f, sizeof(dis));
	for (int i = 1, x; i <= k; i++) {
		std::cin >> x;
		dis[x] = 0;
		q.push({x, 0});
	}
	while (q.size()) {
		auto [u, d] = q.top(); q.pop();
		if (d > dis[u])
			continue;
		for (auto [v, w] : adj[u]) {
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				q.push({v, dis[v]});
			}
		}
	}
}

void dfs(int u, int from) {
	fa[u][0] = from, st[u][0] = dis[u], dep[u] = dep[from] + 1;
	for (int j = 1; (1 << j) <= dep[u]; j++) {
		fa[u][j] = fa[fa[u][j - 1]][j - 1];
		st[u][j] = std::min(st[u][j - 1], st[fa[u][j - 1]][j - 1]);
	}
	for (auto [v, w] : adj[u]) {
		if (v == from)
			continue;
		len[v] = len[u] + w;
		dfs(v, u);
	}
}

int lca(int u, int v) {
	if (dep[u] < dep[v])
		std::swap(u, v);
	for (int i = 19; ~i; i--) {
		if (dep[fa[u][i]] >= dep[v])
			u = fa[u][i];
	}
	if (u == v)
		return u;
	for (int i = 19; ~i; i--) {
		if (fa[u][i] != fa[v][i]) {
			u = fa[u][i];
			v = fa[v][i];
		}
	}
	return fa[u][0];
}

int req(int u, int v) {
	if (u == v) { return dis[u]; }
	int ans = inf;
	for (int i = 19; ~i; i--) {
		if (dep[fa[u][i]] >= dep[v]) {
			ans = std::min(ans, st[u][i]);
			u = fa[u][i];
		}
	}
	ans = std::min(ans, dis[v]);
	return ans;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> p >> k;
	for (int i = 1, u, v, w; i < n; i++) {
		std::cin >> u >> v >> w;
		addedge(u, v, w);
		addedge(v, u, w);
	}
	dij();
	dep[0] = 0;
	for (int i = 0; i < 20; i++) {
		fa[0][i] = 0;
		st[0][i] = inf;
	}
	dfs(1, 0);
	for (int i = 1, u, v; i <= p; i++) {
		std::cin >> u >> v;
		int pa = lca(u, v);
		int ans = (len[u] - len[pa]) + (len[v] - len[pa]) + 2 * std::min(req(u, pa), req(v, pa));
		std::cout << ans << "\n";
	}
	return 0;
}
