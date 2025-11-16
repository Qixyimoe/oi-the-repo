#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5007;

int n;
int ind[N], ans[N];

std::vector<int> adj[N];

void bfs() {
	std::queue<int> q;
	for (int i = 1; i <= n; i++) {
		if (ind[i] == 1)
			q.push(i);
	}
	for (int i = 1; i <= (n / 2); i++) {
		int u1 = q.front(); q.pop();
		int u2 = q.front(); q.pop();
		ans[u1] = u2; ans[u2] = u1;
		for (auto v : adj[u1]) {
			ind[v]--;
			if (ind[v] == 1)
				q.push(v);
		}
		for (auto v : adj[u2]) {
			ind[v]--;
			if (ind[v] == 1)
				q.push(v);
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1, u, v; i < n; i++) {
		std::cin >> u >> v;
		adj[u].push_back(v); ind[v]++;
		adj[v].push_back(u); ind[u]++;
	}
	bfs();
	for (int i = 1; i <= n; i++) {
		if (ans[i])
			std::cout << ans[i] << " ";
		else
			std::cout << i << " ";
	}
	std::cout << "\n";
	return 0;
}
