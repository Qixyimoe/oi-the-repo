#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 7;

int n, bsiz;
int bid[N];
i64 a[N], lzy[N], sum[N];

void add(int l, int r, int x) {
	int sid = bid[l], eid = bid[r];
	if (sid == eid) {
		for (int i = l; i <= r; i++) {
			a[i] += x;
			sum[sid] += x;
		}
		return;
	}
	for (int i = l; bid[i] == sid; i++) { a[i] += x; sum[sid] += x; }
	for (int i = sid + 1; i != eid; i++) { lzy[i] += x; sum[i] += bsiz * x; }
	for (int i = r; bid[i] == eid; i--) { a[i] += x; sum[eid] += x; }
}

i64 query(int l, int r, const int P) {
	int sid = bid[l], eid = bid[r];
	i64 res = 0;
	if (sid == eid) {
		for (int i = l; i <= r; i++) {
			res = (res + a[i] + lzy[sid]) % P;
		}
		return res;
	}
	for (int i = l; bid[i] == sid; i++) { res = (res + a[i] + lzy[sid]) % P; }
	for (int i = sid + 1; i != eid; i++) { res = (res + sum[i]) % P; }
	for (int i = r; bid[i] == eid; i--) { res = (res + a[i] + lzy[eid]) % P; }
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
		sum[bid[i]] += a[i];
	}
	for (int i = 1; i <= n; i++) {
		int op, l, r, c;
		std::cin >> op >> l >> r >> c;
		if (op == 0) {
			add(l, r, c);
		} else {
			std::cout << query(l, r, c + 1) << "\n";
		}
	}
	return 0;
}
