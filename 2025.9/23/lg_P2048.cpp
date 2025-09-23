#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 7;

int n, k, l, r;
i64 ans;
i64 sum[N];

struct STable {
	int tab[N][20];

	void init(int n) {
		for (int i = 1; i <= n; i++) {
			tab[i][0] = i;
		}
		for (int j = 1; (1 << j) <= n; j++) {
			for (int i = 1; i + (1 << j) - 1 <= n; i++) {
				int x = tab[i][j - 1],
					y = tab[i + (1 << j - 1)][j - 1];
				tab[i][j] = sum[x] > sum[y] ? x : y;
			}
		}
	}

	int query(int l, int r) {
		int k = std::__lg(r - l + 1);
		int x = tab[l][k],
			y = tab[r - (1 << k) + 1][k];
		return sum[x] > sum[y] ? x : y;
	}
} rmq;

struct elem {
	int o, l, r, t;

	elem() {}

	elem(int _o, int _l, int _r) : o(_o), l(_l), r(_r), t(rmq.query(_l, _r)) {}

	bool operator < (const elem &rhs) const {
		return sum[t] - sum[o - 1] < sum[rhs.t] - sum[rhs.o - 1];
	}
};

std::priority_queue<elem> q;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> k >> l >> r;
	for (int i = 1; i <= n; i++) {
		std::cin >> sum[i];
		sum[i] += sum[i - 1];
	}
	rmq.init(n);
	for (int i = 1; i <= n; i++) {
		if (i + l - 1 <= n)
			q.push(elem(i, i + l - 1, std::min(i + r - 1, n)));
	}
	while (k--) {
		auto [o, l, r, t] = q.top();
		q.pop();
		ans += sum[t] - sum[o - 1];
		if (l != t)
			q.push(elem(o, l, t - 1));
		if (r != t)
			q.push(elem(o, t + 1, r));
	}
	std::cout << ans << "\n";
	return 0;
}
