#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;
constexpr int S = 550;

int n, bsiz, bid, cnt;

std::vector<int> vec[S];

void rebuild() {
	std::vector<i64> tmp;
	tmp.reserve(n);
	for (int i = 1; i <= bid; i++) {
		tmp.insert(tmp.end(), vec[i].begin(), vec[i].end());
		vec[i].clear();
	}
	n = tmp.size();
	bsiz = std::sqrt(n);
	bid = 0;
	for (int i = 0; i < tmp.size(); i++) {
		if (i % bsiz == 0)
			bid++;
		vec[bid].push_back(tmp[i]);
	}
}

void upd(int p, int x) {
	int cur = 1;
	while (p > vec[cur].size() && cur < bid) {
		p -= vec[cur].size();
		cur++;
	}
	vec[cur].insert(vec[cur].begin() + p - 1, x);
	n++;
}

int query(int p) {
	int cur = 1;
	while (p > vec[cur].size()) {
		p -= vec[cur].size();
		cur++;
	}
	return vec[cur][p - 1];
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	bsiz = std::sqrt(n);
	bid = (n - 1) / bsiz + 1;
	for (int i = 1, x; i <= n; i++) {
		std::cin >> x;
		vec[(i - 1) / bsiz + 1].push_back(x);
	}
	int _n = n;
	for (int i = 1; i <= _n; i++) {
		int op, l, r, c;
		std::cin >> op >> l >> r >> c;
		if (op == 0) {
			upd(l, r);
			cnt++;
			if (cnt >= bsiz) {
				cnt = 0;
				rebuild();
			}
		} else {
			std::cout << query(r) << "\n";
		}
	}
	return 0;
}
