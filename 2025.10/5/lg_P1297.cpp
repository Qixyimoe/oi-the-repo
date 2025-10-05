#include <bits/stdc++.h>

using i64 = long long;
using f64 = double;

constexpr int N = 1e7 + 7;
constexpr int P = 100000001;

int n, a, b, c;
int arr[N];
f64 ans;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> a >> b >> c >> arr[1];
	for (int i = 2; i <= n; i++) {
		arr[i] = ((i64) arr[i - 1] * a + b) % P;
	}
	for (int i = 1; i <= n; i++) {
		arr[i] = arr[i] % c + 1;
	}
	arr[n + 1] = arr[1];
	for (int i = 1; i <= n; i++) {
		ans += 1 / (f64) std::max(arr[i], arr[i + 1]);
	}
	std::cout << std::fixed << std::setprecision(3)
		<< ans << "\n";
	return 0;
}
