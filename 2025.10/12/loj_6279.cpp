#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int S = 350;

int n, bsiz;
int bid[N];
i64 a[N], lzy[N];

std::set<int> st[S];

void add(int l, int r, int x) {
	int sid = bid[l], eid = bid[r];
	if (sid == eid) {
		for (int i = l; i <= r; i++) {
			st[sid].erase(a[i]);
			a[i] += x;
			st[sid].insert(a[i]);
		}
		return;
	}
	for (int i = l; bid[i] == sid; i++) { st[sid].erase(a[i]); a[i] += x; st[sid].insert(a[i]); }
	for (int i = sid + 1; i != eid; i++) { lzy[i] += x;  }
	for (int i = r; bid[i] == eid; i--) { st[eid].erase(a[i]); a[i] += x; st[eid].insert(a[i]); }
}

i64 query(int l, int r, int x) {
	int sid = bid[l], eid = bid[r];
	i64 res = -1;
	if (sid == eid) {
		for (int i = l; i <= r; i++) {
			if (a[i] + lzy[sid] < x)
				res = std::max(res, a[i] + lzy[sid]);
		}
		return res;
	}
	for (int i = l; bid[i] == sid; i++) {
		if (a[i] + lzy[sid] < x)
			res = std::max(res, a[i] + lzy[sid]);
	}
	for (int i = sid + 1; i != eid; i++) {
		auto it = st[i].lower_bound(x - lzy[i]);
		if (it == st[i].begin())
			continue;
		res = std::max(res, *std::prev(it) + lzy[i]);
	}
	for (int i = r; bid[i] == eid; i--) {
		if (a[i] + lzy[eid] < x)
			res = std::max(res, a[i] + lzy[eid]);
	}
	return res;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	bsiz = std::sqrt(n);
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		bid[i] = (i - 1) / bsiz + 1;
		st[bid[i]].insert(a[i]);
	}
	for (int i = 1; i <= n; i++) {
		int op, l, r, c;
		std::cin >> op >> l >> r >> c;
		if (op == 0) {
			add(l, r, c);
		} else {
			std::cout << query(l, r, c) << "\n";
		}
	}
	return 0;
}
