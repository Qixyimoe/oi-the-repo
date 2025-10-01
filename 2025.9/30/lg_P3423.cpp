#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 207;
constexpr int M = 2e4 + 7;

int n, m;
int w[N], c[N];
int q[M], g[M], f[M], o[N][M];

void lgout(int x, int y) {
	if (!x) return;
	lgout(x - 1, y - o[x][y] * w[x]);
	std::cout << o[x][y] << " ";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> w[i];
	}
	for (int i = 1; i <= n; i++) {
		std::cin >> c[i];
	}
	std::cin >> m;
	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int b = 0; b < w[i]; b++) {
			int l = 1, r = 0;
			for (int k = 0; k <= (m - b) / w[i]; k++) {
				while (l <= r && b + k * w[i] - q[l] > c[i] * w[i])
					l++;
				while (l <= r && g[r] >= f[b + k * w[i]] - k)
					r--;
				r++;
				q[r] = b + k * w[i];
				g[r] = f[b + k * w[i]] - k;
				f[b + k * w[i]] = g[l] + k;
				o[i][b + k * w[i]] = (q[r] - q[l]) / w[i];
			}
		}
	}
	std::cout << f[m] << "\n";
	lgout(n, m);
	std::cout << "\n";
	return 0;
}
