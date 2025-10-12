#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e4 + 7;
constexpr int S = 250;

int n, bsiz;
int a[N], bid[N], flg[N];
i64 sum[N];

void upd(int l, int r) {
	int sid = bid[l], eid = bid[r];
	if (sid == eid) {
		for (int i = l; i <= r; i++) {
			sum[bid[i]] -= a[i];
			a[i] = std::sqrt(a[i]);
			sum[bid[i]] += a[i];
		}
		return;
	}
	for (int i = l; bid[i] == sid; i++) { sum[bid[i]] -= a[i]; a[i] = std::sqrt(a[i]); sum[bid[i]] += a[i]; }
	for (int i = sid + 1; i != eid; i++) {
		if (flg[i])
			continue;
		sum[i] = 0;
		flg[i] = 1;
		for (int j = (i - 1) * bsiz + 1; j <= i * bsiz; j++) {
			a[j] = std::sqrt(a[j]);
			sum[i] += a[j];
			if (a[j] > 1)
				flg[i] = 0;
		}
	}
	for (int i = r; bid[i] == eid; i--) { sum[bid[i]] -= a[i]; a[i] = std::sqrt(a[i]); sum[bid[i]] += a[i]; }
}

i64 query(int l, int r) {
	int sid = bid[l], eid = bid[r];
	i64 res = 0;
	if (sid == eid) {
		for (int i = l; i <= r; i++)
			res += a[i];
		return res;
	}
	for (int i = l; bid[i] == sid; i++) { res += a[i]; }
	for (int i = sid + 1; i != eid; i++) { res += sum[i]; }
	for (int i = r; bid[i] == eid; i--) { res += a[i]; }
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
			upd(l, r);
		} else {
			std::cout << query(l, r) << "\n";
		}
	}
	return 0;
}
