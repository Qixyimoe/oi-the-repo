#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;

int n, k;
i64 a[N], s[N], f[N][2];

std::deque<i64> q;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		s[i] = s[i - 1] + a[i];
	}
	q.push_back(0);
	for (int i = 1; i <= n; i++) {
		f[i][0] = std::max(f[i - 1][0], f[i - 1][1]);
		while (q.size() && q.front() < i - k)
			q.pop_front();
		f[i][1] = f[q.front()][0] - s[q.front()] + s[i];
		while (q.size() && f[q.back()][0] - s[q.back()] < f[i][0] - s[i])
			q.pop_back();
		q.push_back(i);
	}
	std::cout << std::max(f[n][0], f[n][1]) << "\n";
	return 0;
}
