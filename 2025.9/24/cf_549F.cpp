#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 7;

int n, m;
int a[N], cnt[N];
i64 ans;
i64 p[N];

void solve(int l, int r) {
	if (l == r) {
		return;
	}
	int mid = (l + r) >> 1;
	solve(l, mid);
	solve(mid + 1, r);
	int k = mid, mx = 0;
	for (int i = mid; i >= l; i--) {
		mx = std::max(mx, a[i]);
		while (k != r && a[k + 1] <= mx) {
			k++;
			cnt[p[k] % m]++;
		}
		ans += cnt[(p[i - 1] + mx) % m];
	}
	for (int i = mid + 1; i <= r; i++) {
		cnt[p[i] % m] = 0;
	}
	k = mid + 1, mx = 0;
	for (int i = mid + 1; i <= r; i++) {
		mx = std::max(mx, a[i]);
		while (k != l && a[k - 1] < mx) {
			k--;
			cnt[p[k - 1] % m]++;
		}
		ans += cnt[((p[i] - mx) % m + m) % m];
	}
	for (int i = l; i <= mid; i++) {
		cnt[p[i - 1] % m] = 0;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		p[i] = p[i - 1] + a[i];
	}
	solve(1, n);
	std::cout << ans << "\n";
	return 0;
}
