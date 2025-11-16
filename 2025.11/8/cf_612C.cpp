#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	std::string s;
	std::cin >> s;
	int n = s.size(); s = " " + s;
	std::stack<char> stc;
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (s[i] == '[' || s[i] == '<' || s[i] == '{' || s[i] == '(')
			stc.push(s[i]);
		else {
			if (!stc.size()) {
				std::cout << "Impossible\n";
				return;
			}
			if (s[i] == ']') {
				if (stc.top() != '[')
					ans++;
			} else if (s[i] == ')') {
				if (stc.top() != '(')
					ans++;
			} else if (s[i] == '}') {
				if (stc.top() != '{')
					ans++;
			} else if (s[i] == '>') {
				if (stc.top() != '<')
					ans++;
			}
			stc.pop();
		}
	}
	if (stc.size())
		std::cout << "Impossible\n";
	else
		std::cout << ans << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	solve();
	return 0;
}
