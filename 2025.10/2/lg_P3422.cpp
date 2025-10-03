#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e6 + 7;

int n;
int p[N], d[N];
bool ans[N];
i64 s[N];

std::deque<int> q;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++)
		std::cin >> p[i] >> d[i];
	for (int i = 1; i <= n; i++)
		s[i] = s[i + n] = p[i] - d[i];
	for (int i = 1; i <= n * 2; i++)
		s[i] += s[i - 1];
	q.clear();
	for (int i = n * 2; i >= 1; i--) {
		while (!q.empty() && s[q.back()] >= s[i])
			q.pop_back();
		q.push_back(i);
		if (!q.empty() && q.front() > i + n -1)
		    q.pop_front();
		if (i <= n) {
			if (s[q.front()] - s[i - 1] >= 0)
				ans[i] = 1;
		}
	}
	d[0] = d[n];
	for (int i = 1; i <= n; i++)
		s[i + n] = s[i] = p[i] - d[i - 1];
	for (int i = 1; i <= n * 2; i++)
		s[i] += s[i - 1];
	q.clear();
	for (int i = 1; i <= n * 2; i++) {
	    if (!q.empty() && q.front() < i - n)
	        q.pop_front();
		if (i > n) {
			if (s[i] - s[q.front()] >= 0)
				ans[i - n] = 1;
		}
		while (!q.empty() && s[q.back()] <= s[i])
			q.pop_back();
		q.push_back(i);
	}

	for (int i = 1; i <= n; i++) {
		if (ans[i])
			std::cout << "TAK\n";
		else
			std::cout << "NIE\n";
	}
	return 0;
}
