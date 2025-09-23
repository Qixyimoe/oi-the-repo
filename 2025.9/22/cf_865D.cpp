#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	int n;
	std::cin >> n;
	std::priority_queue<int, std::vector<int>, std::greater<int>> q;
	i64 ans = 0;
	for (int i = 1, x; i <= n; i++) {
		std::cin >> x;
		if (q.size() && q.top() < x) {
			ans += x - q.top();
			q.pop();
			q.push(x);
		}
		q.push(x);
	}
	std::cout << ans << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	solve();
	return 0;
}
