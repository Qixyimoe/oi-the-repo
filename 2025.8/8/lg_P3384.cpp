#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e5 + 7;

int n, m, r, P;
int tot;
int w[N];
int fa[N], dep[N], siz[N], son[N];
int top[N], dfn[N], rnk[N];

std::vector<int> G[N];

struct SegTree {
    struct node {
        int val, add;
    } tr[N << 2];

    #define ls(o) (o << 1)
    #define rs(o) (o << 1 | 1)

    void maketag(int o, int l, int r, int v) {
        tr[o].add = (tr[o].add + v) % P;
        tr[o].val = (tr[o].val + (r - l + 1) * v) % P;
    }

    void pushup(int o) {
        tr[o].val = (tr[ls(o)].val + tr[rs(o)].val) % P;
    }

    void pushdown(int o, int l, int r) {
        int mid = (l + r) >> 1;
        maketag(ls(o), l, mid, tr[o].add);
        maketag(rs(o), mid + 1, r, tr[o].add);
        tr[o].add = 0;
    }

    void build(int o, int l, int r) {
        if (l == r) {
            tr[o] = {w[rnk[l]], 0};
            return;
        }
        int mid = (l + r) >> 1;
        build(ls(o), l, mid);
        build(rs(o), mid + 1, r);
        pushup(o);
    }

    void update(int o, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) {
            maketag(o, l, r, v);
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(o, l, r);
        if (ql <= mid)
            update(ls(o), l, mid, ql, qr, v);
        if (qr > mid)
            update(rs(o), mid + 1, r, ql, qr, v);
        pushup(o);
    }

    int query(int o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tr[o].val % P;
        int mid = (l + r) >> 1, res = 0;
        pushdown(o, l, r);
        if (ql <= mid)
            res = (res + query(ls(o), l, mid, ql, qr)) % P;
        if (qr > mid)
            res = (res + query(rs(o), mid + 1, r, ql, qr)) % P;
        return res % P;
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

void solve1(int x, int y, int z) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]])
            std::swap(x, y);
        seg.update(1, 1, n, dfn[top[x]], dfn[x], z);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        std::swap(x, y);
    seg.update(1, 1, n, dfn[x], dfn[y], z);
}

int solve2(int x, int y) {
    int res = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]])
            std::swap(x, y);
        res = (res + seg.query(1, 1, n, dfn[top[x]], dfn[x])) % P;
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        std::swap(x, y);
    res = (res + seg.query(1, 1, n, dfn[x], dfn[y])) % P;
    return res;
}

void solve3(int x, int z) {
    seg.update(1, 1, n, dfn[x], dfn[x] + siz[x] - 1, z);
}

int solve4(int x) {
    return seg.query(1, 1, n, dfn[x], dfn[x] + siz[x] - 1);
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m >> r >> P;
    for (int i = 1; i <= n; i++) {
        std::cin >> w[i];
    }
    for (int i = 1, x, y; i < n; i++) {
        std::cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs1(r);
    dfs2(r, r);
    seg.build(1, 1, n);
    for (int i = 1, t, x, y, z; i <= m; i++) {
        std::cin >> t;
        if (t == 1) { std::cin >> x >> y >> z; solve1(x, y, z); }
        if (t == 2) { std::cin >> x >> y; std::cout << solve2(x, y) << "\n"; }
        if (t == 3) { std::cin >> x >> z; solve3(x, z); }
        if (t == 4) { std::cin >> x; std::cout << solve4(x) << "\n"; }
    }
    return 0;
}
