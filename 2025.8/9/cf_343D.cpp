#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 7;

int n, q;
int tot;
int fa[N], dep[N], siz[N], son[N];
int top[N], dfn[N], rnk[N];

std::vector<int> G[N];

struct SegTree {
    struct node {
        int val, lzy;
    } tr[N << 2];

    #define ls(o) (o << 1)
    #define rs(o) (o << 1 | 1)

    void build(int o, int l, int r) {
        if (l == r) {
            tr[o] = {0, -1};
            return;
        }
        int mid = (l + r) >> 1;
        build(ls(o), l, mid);
        build(rs(o), mid + 1, r);
    }

    void pushdown(int o) {
        if (tr[o].lzy != -1) {
            tr[ls(o)] = {tr[o].lzy, tr[o].lzy};
            tr[rs(o)] = {tr[o].lzy, tr[o].lzy};
            tr[o].lzy = -1;
        }
    }

    void update(int o, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) {
            tr[o] = {v, v};
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(o);
        if (ql <= mid)
            update(ls(o), l, mid, ql, qr, v);
        if (qr > mid)
            update(rs(o), mid + 1, r, ql, qr, v);
    }

    int query(int o, int l, int r, int x) {
        if (l == r)
            return tr[o].val;
        pushdown(o);
        int mid = (l + r) >> 1;
        if (x <= mid)
            return query(ls(o), l, mid, x);
        else
            return query(rs(o), mid + 1, r, x);
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
    tot++;
    top[u] = t, dfn[u] = tot, rnk[tot] = u;
    if (son[u] == -1) return;
    dfs2(son[u], t);
    for (auto v : G[u]) {
        if (v != son[u] && v != fa[u])
            dfs2(v, v);
    }
}

void solve1(int x) {
    seg.update(1, 1, n, dfn[x], dfn[x] + siz[x] - 1, 1);
}

void solve2(int x) {
    while (x) {
        seg.update(1, 1, n, dfn[top[x]], dfn[x], 0);
        x = fa[top[x]];
    }
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
    dfs1(1);
    dfs2(1, 1);
    seg.build(1, 1, n);
    std::cin >> q;
    for (int i = 1, c, v; i <= q; i++) {
        std::cin >> c >> v;
        if (c == 1) { solve1(v); }
        if (c == 2) { solve2(v); }
        if (c == 3) { std::cout << seg.query(1, 1, n, dfn[v]) << "\n"; }
    }
    return 0;
}
