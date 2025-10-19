#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;

int n;
i64 t;
int fa[N][20];
i64 dis[N], val[N];

void jmp(int x) {
	for (int i = 1; i <= 19; i++) {
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	}
}

void work(int x) {
	val[x]++;
	i64 res = t;
	int cur = x;
	for (int i = 19; ~i; i--) {
		if (fa[cur][i] != 0 && dis[cur] - dis[fa[cur][i]] <= res) {
			res -= dis[cur] - dis[fa[cur][i]];
			cur = fa[cur][i];
		}
	}
	if (cur != 1)
		val[fa[cur][0]]--;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> t;
	fa[1][0] = 1;
	dis[1] = 0;
	for (int i = 2; i <= n; i++) {
		i64 w;
		std::cin >> fa[i][0] >> w;
		dis[i] = dis[fa[i][0]] + w;
		jmp(i);
	}
	for (int i = 1; i <= n; i++) {
		work(i);
	}
	for (int i = n; i > 1; i--) {
		val[fa[i][0]] += val[i];
	}
	for (int i = 1; i <= n; i++) {
		std::cout << val[i] << "\n";
	}
	return 0;
}
