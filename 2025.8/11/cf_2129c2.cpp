#include <bits/stdc++.h>

using i64 = long long;

int ask(int l, int r) {
    std::cout << "? " << r - l + 1 << " ";
    for (int i = l; i <= r; i++)
        std::cout << i << " ";
    std::cout << std::endl;
    int x;
    std::cin >> x;
    return x;
}

std::pair<int, int> get(int n) {
    if (!ask(1, n))
        return {n, 1};
    int l = 2, r = n;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (ask(1, mid))
            r = mid;
        else
            l = mid + 1;
    }
    return {r - 1, r};
}

void solve() {
    int n;
    std::cin >> n;
    auto p = get(n);
    std::vector<char> s(n + 1);
    s[p.first] = '(', s[p.second] = ')';
    int tot = 0;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        if (i != p.first && i != p.second)
            a[++tot] = i;
    }
    for (int i = 1; i <= tot; i += 8) {
        std::vector<int> vec;
        for (int j = i; j <= std::min(i + 7, tot); j++) {
            for (int k = 1; k <= (1 << (j - i)); k++)
                vec.push_back(a[j]);
            for (int k = 1; k <= (1 << (j - i)); k++)
                vec.push_back(p.second);
            vec.push_back(p.second);
        }
        std::cout << "? " << vec.size() << " ";
        for (auto j : vec)
            std::cout << j << " ";
        std::cout << std::endl;
        int x;
        std::cin >> x;
        for (int j = i; j <= std::min(i + 7, tot); j++) {
            if ((x >> (j - i)) & 1)
                s[a[j]] = '(';
            else
                s[a[j]] = ')';
        }
    }
    std::cout << "! ";
    for (int i = 1; i <= n; i++)
        std::cout << s[i];
    std::cout << std::endl;
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
