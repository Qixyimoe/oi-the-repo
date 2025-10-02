#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 207;
const int dx[] = {0, -1, 1, 0, 0};
const int dy[] = {0, 0, 0, -1, 1};

int n, m, sx, sy, k;
int ans;
int f[N][N];
std::string a[N];

void dp(int x, int y, int len, int d) {
	std::deque<std::pair<int, int>> q;
	for (int i = 1; 1 <= x && x <= n && 1 <= y && y <= m; i++, x += dx[d], y += dy[d]) {
		if (a[x][y] == 'x')
			q.clear();
		else {
			while (q.size() && q.back().first + i - q.back().second < f[x][y])
				q.pop_back();
			q.push_back({f[x][y], i});
			if (q.back().second - q.front().second > len)
				q.pop_front();
			f[x][y] = q.front().first + i - q.front().second;
			ans = std::max(ans, f[x][y]);
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m >> sx >> sy >> k;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		a[i] = '$' + a[i];
	}
	memset(f, -0x3f, sizeof(f));
	f[sx][sy] = 0;
	for (int _t = 1, s, t, d, len; _t <= k; _t++) {
		std::cin >> s >> t >> d;
		len = t - s + 1;
		if (d == 1)
			for (int i = 1; i <= m; i++)
				dp(n, i, len, d);
		if (d == 2)
			for (int i = 1; i <= m; i++)
				dp(1, i, len, d);
		if (d == 3)
			for (int i = 1; i <= n; i++)
				dp(i, m, len, d);
		if (d == 4)
			for (int i = 1; i <= n; i++)
				dp(i, 1, len, d);
	}
	std::cout << ans << "\n";
	return 0;
}
