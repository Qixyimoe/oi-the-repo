#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, m;

struct req {
	int op;
	i64 x;
} q[N];

struct SegTree {
	i64 tr[N << 2];

	#define ls(o) (o << 1)
	#define rs(o) (o << 1 | 1)

	void pushup(const int o) {
		tr[o] = tr[ls(o)] * tr[rs(o)] % m;
	}

	void build(int o, int l, int r) {
		if (l == r) {
			tr[o] = q[l].op == 1 ? q[l].x % m : 1;
			return;
		}
		int mid = (l + r) >> 1;
		build(ls(o), l, mid);
		build(rs(o), mid + 1, r);
		pushup(o);
	}

	void update(int o, int l, int r, int p) {
		if (l == r) { tr[o] = 1; return; }
		int mid = (l + r) >> 1;
		if (p <= mid)
			update(ls(o), l, mid, p);
		else
			update(rs(o), mid + 1, r, p);
		pushup(o);
	}

	i64 query(int o, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) { return tr[o]; }
		int mid = (l + r) >> 1;
		i64 res = 1;
		if (ql <= mid)
			res = (res * query(ls(o), l, mid, ql, qr)) % m;
		if (qr > mid)
			res = (res * query(rs(o), mid + 1, r, ql, qr)) % m;
		return res;
	}
} seg;

void solve() {
	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		std::cin >> q[i].op >> q[i].x;
	}
	seg.build(1, 1, n);
	for (int i = 1; i <= n; i++) {
		if (q[i].op == 1) {
			std::cout << seg.query(1, 1, n, 1, i) << "\n";
		} else {
			seg.update(1, 1, n, q[i].x);
			std::cout << seg.query(1, 1, n, 1, i) << "\n";
		}
	}
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
