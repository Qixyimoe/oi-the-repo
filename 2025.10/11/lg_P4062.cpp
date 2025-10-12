#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 7;
constexpr int inf = 1e9;

int n, k;
i64 ans;
int a[N], vis[N], suf[N];
int b[N * 2], cnt[N * 2];

void update(int l, int r, int x, int p) {
	suf[p + 1] = 0;
	int mn = inf, mx = -inf;
	for (int i = p; i >= l; i--) {
		suf[i] = suf[i + 1];
		if (a[i] == x)
			suf[i]++;
		else
			suf[i]--;
		b[N + suf[i]]++;
		mn = std::min(mn, suf[i]);
		mx = std::max(mx, suf[i]);
	}
	for (int i = mn; i <= mx; i++) {
		b[N + i] += b[i + N - 1];
	}
	int cot = 0;
	for (int i = p + 1; i <= r; i++) {
		if (a[i] == x)
			cot++;
		else
			cot--;
		int _l = -cot + 1;
		if (_l <= mx)
			ans += b[mx + N] - b[_l + N - 1];
	}
	for (int i = mn; i <= mx; i++) {
		b[i + N] = 0;
	}
}

void solve(int l, int r) {
	if (l == r) { ans++; return; }
	int mid = (l + r) >> 1;
	solve(l, mid);
	solve(mid + 1, r);
	for (int i = l; i <= r; i++) {
		cnt[a[i]]++;
	}
	for (int i = l; i <= r; i++) {
		if (!vis[a[i]]) {
			int dl = mid - cnt[a[i]] * 2 + 1,
				dr = mid + 1 + cnt[a[i]] * 2 - 1;
			dl = std::max(dl, l);
			dr = std::min(dr, r);
			update(dl, dr, a[i], mid);
			vis[a[i]] = 1;
		}
	}
	for (int i = l; i <= r; i++) {
		cnt[a[i]]--;
		vis[a[i]] = 0;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	solve(1, n);
	std::cout << ans << "\n";
	return 0;
}
