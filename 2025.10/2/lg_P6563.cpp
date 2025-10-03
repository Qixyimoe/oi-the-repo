#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e4 + 7;

void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	std::vector<std::vector<int>> f(n + 1, std::vector<int>(n + 1));
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	for (int r = 2; r <= n; r++) {
		int k = r;
		std::deque<int> q;
		q.push_back(r);
		for (int l = r - 1; l >= 1; l--) {
			if (l + 1 == r) { f[l][r] = a[l]; continue; }
			while (l < k && f[l][k - 1] > f[k][r])
				k--;
			f[l][r] = f[l][k] + a[k];
			while (q.size() && q.front() >= k)
				q.pop_front();
			if (q.size())
				f[l][r] = std::min(f[l][r], f[q.front() + 1][r] + a[q.front()]);
			while (q.size() && f[l + 1][r] + a[l] <= f[q.back() + 1][r] + a[q.back()])
				q.pop_back();
			q.push_back(l);
		}
	}
	std::cout << f[1][n] << "\n";
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
