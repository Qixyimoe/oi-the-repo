#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		sum += a[i];
	}
	std::sort(a.begin() + 1, a.end());
	int avg = sum / n, ret = sum % n;
	std::vector<int> b(n + 1);
	for (int i = 1; i <= n - ret; i++) {
		b[i] = avg;
	}
	for (int i = n - ret + 1; i <= n; i++) {
		b[i] = avg + 1;
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i] > b[i]) {
			ans += (a[i] - b[i]);
		}
	}
	std::cout << ans << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	solve();
	return 0;
}
