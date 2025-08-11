#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, m1, m2;
int ans;
int ans1[N], ans2[N];

struct node {
    int x, y;
} a[N], b[N];

bool cmp(const node &a, const node &b) { return a.x < b.x; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    freopen("airport.in", "r", stdin);
    freopen("airport.out", "w", stdout);

    std::cin >> n >> m1 >> m2;
    for (int i = 1; i <= m1; i++)
        std::cin >> a[i].x >> a[i].y;
    for (int i = 1; i <= m2; i++)
        std::cin >> b[i].x >> b[i].y;
    std::sort(a + 1, a + m1 + 1, cmp);
    std::sort(b + 1, b + m2 + 1, cmp);

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pl1;
    std::priority_queue<int, std::vector<int>, std::greater<int>> lq1;
    for (int i = 1; i <= n; i++)
        lq1.push(i);
    for (int i = 1; i <= m1; i++) {
        while (!pl1.empty() && a[i].x >= pl1.top().first) {
            lq1.push(pl1.top().second);
            pl1.pop();
        }
        if (lq1.empty())
            continue;
        ans1[lq1.top()]++;
        pl1.push({a[i].y, lq1.top()});
        lq1.pop();
    }
    for (int i = 1; i <= n; i++)
        ans1[i] += ans1[i - 1];

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pl2;
    std::priority_queue<int, std::vector<int>, std::greater<int>> lq2;
    for (int i = 1; i <= n; i++)
        lq2.push(i);
    for (int i = 1; i <= m2; i++) {
        while (!pl2.empty() && b[i].x >= pl2.top().first) {
            lq2.push(pl2.top().second);
            pl2.pop();
        }
        if (lq2.empty())
            continue;
        ans2[lq2.top()]++;
        pl2.push({b[i].y, lq2.top()});
        lq2.pop();
    }
    for (int i = 1; i <= n; i++)
        ans2[i] += ans2[i - 1];

    for (int i = 0; i <= n; i++)
        ans = std::max(ans, ans1[i] + ans2[n - i]);
    std::cout << ans << "\n";
    return 0;
}
