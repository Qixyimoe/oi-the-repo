#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1e9;

struct node {
	int t, c, i;
	i64 v;

	bool operator < (const node &rhs) const {
		return v < rhs.v;
	}
};

struct elem {
	int d, i;
};

void solve() {
	int n, m, k; i64 s;
	std::cin >> n >> m >> k >> s;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	std::vector<int> b(n + 1);
	for (int i = 1; i <= n; i++) {
		std::cin >> b[i];
	}
	std::vector<node> c(m + 1);
	for (int i = 1; i <= m; i++) {
		std::cin >> c[i].t >> c[i].c;
		c[i].i = i;
	}
	std::vector<elem> g(k + 1);
	auto check = [&](int x) -> bool {
		int ia = inf, ib = inf;
		int pa = 1, pb = 1;
		for (int i = 1; i <= x; i++) {
			if (a[i] < ia) { ia = a[i]; pa = i; }
			if (b[i] < ib) { ib = b[i]; pb = i; }
		}
		auto _c = c;
		for (int i = 1; i <= m; i++) {
			if (_c[i].t == 1)
				_c[i].v = 1ll * ia * _c[i].c;
			else
				_c[i].v = 1ll * ib * _c[i].c;
		}
		std::sort(_c.begin() + 1, _c.end());
		i64 res = 0;
		for (int i = 1; i <= k; i++) {
			res += _c[i].v;
		}
		if (res > s)
			return 0;
		for (int i = 1; i <= k; i++) {
			g[i].i = _c[i].i;
			g[i].d = (_c[i].t == 1 ? pa : pb);
		}
		return 1;
	};
	int l = 0, r = n;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (check(mid))
			r = mid;
		else
			l = mid + 1;
	}
	if (check(l)) {
		std::cout << l << "\n";
		for (int i = 1; i <= k; i++)
			std::cout << g[i].i << " " << g[i].d << "\n";
	} else {
		std::cout << "-1\n";
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	solve();
	return 0;
}
