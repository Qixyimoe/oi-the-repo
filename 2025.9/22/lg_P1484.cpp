#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 7;

int n, m;
int pre[N], nex[N];
i64 ans;
i64 a[N];
bool vis[N];

std::priority_queue<std::pair<int, int>> q;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		q.push({a[i], i});
		pre[i] = i - 1, nex[i] = i + 1;
	}
	nex[0] = 1, pre[0] = 0;
	pre[n + 1] = n, nex[n + 1] = n + 1;
	while (m--) {
		while (q.size() && vis[q.top().second])
			q.pop();
		if (!q.size())
			break;
		auto [v, i] = q.top();
		if (v <= 0)
			break;
		q.pop();
		ans += v;
		int l = pre[i], r = nex[i];
		vis[l] = vis[r] = 1;
		// 带悔
		a[i] = a[l] + a[r] - a[i];
		q.push({a[i], i});
		pre[i] = pre[l];
		nex[pre[l]] = i;
		nex[i] = nex[r];
		pre[nex[r]] = i;
	}
	std::cout << ans << "\n";
	return 0;
}
