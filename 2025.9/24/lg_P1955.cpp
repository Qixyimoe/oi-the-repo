#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;

struct DSU {
	int fa[N], siz[N];

	void init(const int n) {
		for (int i = 1; i <= n; i++) {
			fa[i] = i;
			siz[i] = 1;
		}
	}

	int find(int x) {
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}

	void merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y)
			return;
		if (siz[x] > siz[y])
			std::swap(x, y);
		fa[y] = x;
		siz[x] += siz[y];
	}
} uni;

void solve() {
	int n;
	std::cin >> n;
	uni.init(2 * n);
	std::set<int> st;
	std::vector<int> x(n + 1), y(n + 1), e(n + 1);
	for (int i = 1; i <= n; i++) {
		std::cin >> x[i] >> y[i] >> e[i];
		st.insert(x[i]);
		st.insert(y[i]);
	}
	int idx = 0;
	std::map<int, int> mp;
	for (auto i : st) {
		mp[i] = ++idx;
	}
	std::vector<std::pair<int, int>> vec;
	for (int i = 1; i <= n; i++) {
		if (e[i])
			uni.merge(mp[x[i]], mp[y[i]]);
		else
			vec.push_back({mp[x[i]], mp[y[i]]});
	}
	int flg = 0;
	for (auto [i, j] : vec) {
		if (uni.find(i) == uni.find(j)) {
			std::cout << "NO\n";
			return;
		}
	}
	std::cout << "YES\n";
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
