#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e4 + 7;
constexpr int inf = 1e9;

int n, q;
int ncnt;
int w[N];
int fa[N], dep[N], siz[N], son[N];
int top[N], dfn[N], rnk[N];

std::vector<int> G[N];

struct SegTree {
    struct node {
        int sum, mxn;
    } tr[N << 2];

    #define ls(o) (o << 1)
    #define rs(o) (o << 1 | 1)

    void pushup(int o) {
        tr[o] = {
            tr[ls(o)].sum + tr[rs(o)].sum,
            std::max(tr[ls(o)].mxn, tr[rs(o)].mxn)
        };
    }

    void build(int o, int l, int r) {
        if (l == r) {
            tr[o] = {w[rnk[l]], w[rnk[l]]};
            return;
        }
        int mid = (l + r) >> 1;
        build(ls(o), l, mid);
        build(rs(o), mid + 1, r);
        pushup(o);
    }

    void update(int o, int l, int r, int p, int v) {
        if (l == r) {
            tr[o] = {v, v};
            return;
        }
        int mid = (l + r) >> 1;
        if (p <= mid)
            update(ls(o), l, mid, p, v);
        else
            update(rs(o), mid + 1, r, p, v);
        pushup(o);
    }

    int queryMax(int o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tr[o].mxn;
        int mid = (l + r) >> 1,
            res = -inf;
        if (ql <= mid)
            res = std::max(res, queryMax(ls(o), l, mid, ql, qr));
        if (qr > mid)
            res = std::max(res, queryMax(rs(o), mid + 1, r, ql, qr));
        return res;
    }

    int querySum(int o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tr[o].sum;
        int mid = (l + r) >> 1,
            res = 0;
        if (ql <= mid)
            res += querySum(ls(o), l, mid, ql, qr);
        if (qr > mid)
            res += querySum(rs(o), mid + 1, r, ql, qr);
        return res;
    }
} seg;

void dfs1(int u) {
    son[u] = -1, siz[u] = 1;
    for (auto v : G[u]) {
        if (v == fa[u]) continue;
        fa[v] = u;
        dep[v] = dep[u] + 1;
        dfs1(v);
        siz[u] += siz[v];
        if (son[u] == -1 || siz[v] > siz[son[u]])
            son[u] = v;
    }
}

void dfs2(int u, int t) {
    ncnt++;
    top[u] = t, dfn[u] = ncnt, rnk[ncnt] = u;
    if (son[u] == -1) return;
    dfs2(son[u], t);
    for (auto v : G[u]) {
        if (v != son[u] && v != fa[u])
            dfs2(v, v);
    }
}

void solve2(int u, int v) {
    int res = -inf;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            std::swap(u, v);
        res = std::max(res, seg.queryMax(1, 1, n, dfn[top[u]], dfn[u]));
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        std::swap(u, v);
    res = std::max(res, seg.queryMax(1, 1, n, dfn[u], dfn[v]));
    std::cout << res << "\n";
}

void solve3(int u, int v) {
    int res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])
            std::swap(u, v);
        res += seg.querySum(1, 1, n, dfn[top[u]], dfn[u]);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v])
        std::swap(u, v);
    res += seg.querySum(1, 1, n, dfn[u], dfn[v]);
    std::cout << res << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1, u, v; i < n; i++) {
        std::cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> w[i];
    }
    dfs1(1);
    dfs2(1, 1);
    seg.build(1, 1, n);
    std::cin >> q;
    for (int i = 1, x, y; i <= q; i++) {
        std::string s;
        std::cin >> s >> x >> y;
        if (s == "CHANGE")
            seg.update(1, 1, n, dfn[x], y);
        if (s == "QMAX")
            solve2(x, y);
        if (s == "QSUM")
            solve3(x, y);
    }
    return 0;
}
