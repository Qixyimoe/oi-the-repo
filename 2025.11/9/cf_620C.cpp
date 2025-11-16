#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e5 + 7;

int n, lst, ans;
int a[N];

std::vector<std::pair<int, int>> vec;
std::map<int, int> mp;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		mp[a[i]]++;
		if (mp[a[i]] > 1) {
			ans++;
			vec.push_back({lst + 1, i});
			lst = i;
			mp.clear();
		}
	}
	if (!lst) {
		std::cout << "-1\n";
	} else {
		std::cout << ans << "\n";`
		vec.back().second = n;
		for (auto i : vec) {
			std::cout << i.first << " " << i.second << "\n";
		}
	}
	return 0;
}
