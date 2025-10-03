#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e3 + 7;

int t, maxp, w;
int ans;
int f[N][N];

std::deque<int> q;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> t >> maxp >> w;
	memset(f, -0x3f, sizeof(f));
	f[0][0] = 0;
	for (int i = 1, ap, bp, as, bs; i <= t; i++) {
		std::cin >> ap >> bp >> as >> bs;
		q.clear();
		int c = std::max(0, i - w - 1);
		for (int j = maxp; ~j; j--) {
			f[i][j] = std::max(f[i][j], f[i - 1][j]);
			while (q.size() && (j + bs < q.front()))
				q.pop_front();
			while (q.size() && f[c][q.back()] + q.back() * bp < f[c][j] + j * bp)
				q.pop_back();
			q.push_back(j);
			f[i][j] = std::max(f[i][j], f[c][q.front()] + q.front() * bp - j * bp);
		}
		q.clear();
		for (int j = 0; j <= maxp; j++) {
			f[i][j] = std::max(f[i][j], f[i - 1][j]);
			while (q.size() && (j - as > q.front()))
				q.pop_front();
			while (q.size() && f[c][q.back()] + q.back() * ap < f[c][j] + j * ap)
				q.pop_back();
			q.push_back(j);
			f[i][j] = std::max(f[i][j], f[c][q.front()] + q.front() * ap - j * ap);
		}
	}
	std::cout << *std::max_element(f[t], f[t] + maxp + 1) << "\n";
	return 0;
}
