#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 7;
constexpr int M = 1e6 + 7;

int n, k;
int ans, _l, _r;
int a[N], cnt[M];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	int l = 1, s = 0;
	for (int i = 1; i <= n; i++) {
		++cnt[a[i]];
		if (cnt[a[i]] == 1)
			s++;
		while (s > k) {
			cnt[a[l++]]--;
			if (!cnt[a[l - 1]])
				s--;
		}
		if (s <= k && ans < i - l + 1) {
			ans = i - l + 1;
			_l = l, _r = i;
		}
	}
	std::cout << _l << " " << _r  << "\n";
	return 0;
}
