#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e4 + 7;
constexpr int S = 250;

int n, bsiz;
int bid[N];
i64 a[N], lzy[N];

std::vector<int> vec[S];

void reset(int x) {
	vec[x].clear();
	for (int i = (x - 1) * bsiz + 1; i <= std::min(x * bsiz, n); i++) {
		vec[x].push_back(a[i]);
	}
	std::sort(vec[x].begin(), vec[x].end());
}

void add(int l, int r, int x) {
	int sid = bid[l], eid = bid[r];
	if (sid == eid) {
		for (int i = l; i <= r; i++) {
			a[i] += x;
		}
		reset(sid);
		return;
	}
	for (int i = l; bid[i] == sid; i++) { a[i] += x; }
	reset(sid);
	for (int i = sid + 1; i != eid; i++) { lzy[i] += x;  }
	for (int i = r; bid[i] == eid; i--) { a[i] += x;  }
	reset(eid);
}

i64 query(int l, int r, int x) {
	int sid = bid[l], eid = bid[r];
	i64 res = 0;
	if (sid == eid) {
		for (int i = l; i <= r; i++) {
			if (a[i] + lzy[sid] < x)
				res++;
		}
		return res;
	}
	for (int i = l; bid[i] == sid; i++) {
		if (a[i] + lzy[sid] < x)
			res++;
	}
	for (int i = sid + 1; i != eid; i++) {
		res += std::lower_bound(vec[i].begin(), vec[i].end(), x - lzy[i]) - vec[i].begin();
	}
	for (int i = r; bid[i] == eid; i--) {
		if (a[i] + lzy[eid] < x)
			res++;
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
		vec[bid[i]].push_back(a[i]);
	}
	for (int i = 1; i <= bid[n]; i++) {
		std::sort(vec[i].begin(), vec[i].end());
	}
	for (int i = 1; i <= n; i++) {
		int op, l, r, c;
		std::cin >> op >> l >> r >> c;
		if (op == 0) {
			add(l, r, c);
		} else {
			std::cout << query(l, r, c * c) << "\n";
		}
	}
	return 0;
}
