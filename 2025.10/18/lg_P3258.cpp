#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e5 + 7;
constexpr int LOG_N = 19;

int n;
int a[N], dep[N], d[N], ans[N];
int fa[N][LOG_N + 1];

std::vector<int> adj[N];

void addedge(int u, int v) { adj[u].push_back(v); }

void dfs(int u, int from) {
	fa[u][0] = from;
	dep[u] = dep[from] + 1;
	for (auto v : adj[u]) {
		if (v == from)
			continue;
		dfs(v, u);
	}
}

void init() {
	for (int j = 1; j <= LOG_N; j++) {
		for (int i = 1; i <= n; i++)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
	}
}

int lca(int u, int v) {
	if (dep[u] < dep[v])
		std::swap(u, v);
        
	for (int i = LOG_N; ~i; i--) {
		if (fa[u][0] != 0 && dep[fa[u][i]] >= dep[v])
			u = fa[u][i];
	}
    
	if (u == v)
		return u;
        
	for (int i = LOG_N; ~i; i--) {
		if (fa[u][0] != 0 && fa[u][i] != fa[v][i]) {
			u = fa[u][i];
			v = fa[v][i];
		}
	}
	return fa[u][0];
}

void upd(int u, int v, int w) {
    int _lca = lca(u, v);
    d[u] += w;
    d[v] += w;
    d[_lca] -= w;
    if (fa[_lca][0] != 0) {
        d[fa[_lca][0]] -= w;
    }
}

void dfs0(int u, int from) {
    ans[u] = d[u];
    for (auto v : adj[u]) {
        if (v != from) {
            dfs0(v, u);
            ans[u] += ans[v];
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    for (int i = 1, x, y; i < n; i++) {
        std::cin >> x >> y;
        addedge(x, y);
        addedge(y, x);
    }
    dep[0] = 0;
    dfs(1, 0);
    init();
    for (int i = 1; i < n; i++) {
        upd(a[i], a[i + 1], 1);
        upd(a[i + 1], a[i + 1], -1);
    }
    dfs0(1, 0);
    for (int i = 1; i <= n; i++) {
        std::cout << ans[i] << "\n";
    }
    
    return 0;
}
