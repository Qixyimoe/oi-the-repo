#include <bits/stdc++.h>

#define int long long

constexpr int N = 5e5 + 7;
constexpr int inf = 1e18;

struct SegTree {
	int n;
	int tr[N << 2];

	#define ls(o) (o << 1)
	#define rs(o) (o << 1 | 1)

	void init(int _n) {
		if (_n <= 0) return;
		n = 4 * _n;
		for (int i = 1; i <= n; i++)
			tr[i] = -inf;
	}

	void update(int o, int l, int r, int ql, int qr, int v) {
		if (ql <= l && r <= qr) {
			tr[o] = std::max(tr[o], v);
			return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid)
			update(ls(o), l, mid, ql, qr, v);
		if (qr > mid)
			update(rs(o), mid + 1, r, ql, qr, v);
		tr[o] = std::max(tr[ls(o)], tr[rs(o)]);
	}

	int query(int o, int l, int r, int ql, int qr) {
		if (ql > qr) {
			return -inf;
		}

		if (ql <= l && r <= qr) {
			return tr[o];
		}
		int mid = (l + r) >> 1,
			ans = -inf;
		if (ql <= mid)
			ans = std::max(ans, query(ls(o), l, mid, ql, qr));
		if (qr > mid)
			ans = std::max(ans, query(rs(o), mid + 1, r, ql, qr));
		return ans;
	}
} seg1, seg2;

void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	std::vector<int> s(n + 1);
	std::vector<int> g(n + 2);
	s[0] = 0;
	g[0] = 0;
	for (int i = 1; i <= n; i++) {
		s[i] = s[i - 1] + a[i];
		g[i] = s[i];
	}
	std::sort(g.begin(), g.begin() + n + 1);
	int len = std::unique(g.begin(), g.begin() + n + 1) - g.begin();
	std::map<int, int> idx;
	for (int i = 0; i < len; i++) {
		idx[g[i]] = i + 1;
	}
	std::vector<int> t(len + 1, -inf);
	std::vector<int> f(n + 1, -inf);
	seg1.init(len);
	seg2.init(len);
	f[0] = 0;
	t[idx[s[0]]] = 0;
	seg1.update(1, 1, len, idx[s[0]], idx[s[0]], f[0] - 0);
	seg2.update(1, 1, len, idx[s[0]], idx[s[0]], f[0] + 0);
	for (int i = 1; i <= n; i++) {
        int x = idx[s[i]];
		if (t[x] > -inf) {
            f[i] = std::max(f[i], t[x]);
        }
		f[i] = std::max(f[i], seg1.query(1, 1, len, 1, x - 1) + i);
		f[i] = std::max(f[i], seg2.query(1, 1, len, x + 1, len) - i);
		t[x] = std::max(t[x], f[i]);
		seg1.update(1, 1, len, x, x, f[i] - i);
		seg2.update(1, 1, len, x, x, f[i] + i);
	}
	std::cout << f[n] << "\n";
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