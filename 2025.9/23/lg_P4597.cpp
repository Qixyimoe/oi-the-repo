#include <bits/stdc++.h>

using i64 = long long;

int n;
i64 ans;

std::priority_queue<int> q;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1, x; i <= n; i++) {
		std::cin >> x;
		q.push(x);
		if (q.top() > x) {
			ans += (q.top() - x);
			q.pop();
			q.push(x);
		}
	}
	std::cout << ans << "\n";
	return 0;
}
