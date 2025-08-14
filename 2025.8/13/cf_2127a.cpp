#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::set<int> st;
    for (int i = 1, x; i <= n; i++) {
        std::cin >> x;
        st.insert(x);
    }
    st.erase(-1);
    if (st.size() <= 1 && !st.count(0))
        std::cout << "YES\n";
    else
        std::cout << "NO\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
