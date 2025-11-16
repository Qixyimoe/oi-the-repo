#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e6 + 7;

int n, k;
int s, l, len, cnt;

std::pair<int, int> ans[N];

struct elem {
	int i, t;
} a[N];

bool cmp(const elem &x, const elem &y) {
	return (x.i == y.i ? x.t < y.t : x.i < y.i);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[++len].i >> a[++len].i;
		a[len].t = 1;
	}
	n = n * 2;
	std::sort(a + 1, a + n + 1, cmp);
	for (int i = 1; i <= n; i++) {
		if (a[i].t == 0) {
			s++;
			if (s == k)
				l = a[i].i;
		} else {
			if (s == k)
				ans[++cnt] = {l, a[i].i};
			s--;
		}
	}
	std::cout << cnt << "\n";
	for (int i = 1; i <= cnt; i++) {
		std::cout << ans[i].first << " " << ans[i].second << "\n";
	}
	return 0;
}
