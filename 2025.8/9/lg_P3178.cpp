#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e5 + 7;

int n, m;
int ncnt;
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
        tr[o].val = (tr[o].val + (r - l + 1) * v);
        tr[o].add = (tr[o].add + v);
    }

    void pushup(int o) {
        tr[o].val = tr[ls(o)].val + tr[rs(o)].val;
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

    void modify(int o, int l, int r, int p, int v) {
        if (l == r) {
            tr[o] = {tr[o].val + v, 0};
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(o, l, r);
        if (p <= mid)
            modify(ls(o), l, mid, p, v);
        else
            modify(rs(o), mid + 1, r, p, v);
        pushup(o);
    }

    int query(int o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tr[o].val;
        int mid = (l + r) >> 1, 
            res = 0;
        pushdown(o, l, r);
        if (ql <= mid)
            res += query(ls(o), l, mid, ql, qr);
        if (qr > mid)
            res += query(rs(o), mid + 1, r, ql, qr);
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

void solve1(int x, int a) {
    seg.modify(1, 1, n, dfn[x], a);
}

void solve2(int x, int a) {
    seg.update(1, 1, n, dfn[x], dfn[x] + siz[x] - 1, a);
}

int solve3(int x) {
    int res = 0;
    while (top[1] != top[x]) {
        res += seg.query(1, 1, n, dfn[top[x]], dfn[x]);
        x = fa[top[x]];
    }
    res += seg.query(1, 1, n, dfn[1], dfn[x]);
    return res;
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        std::cin >> w[i];
    for (int i = 1, u, v; i < n; i++) {
        std::cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs1(1);
    dfs2(1, 1);
    seg.build(1, 1, n);
    for (int i = 1, t, x, a; i <= m; i++) {
        std::cin >> t >> x;
        if (t == 1) { std::cin >> a; solve1(x, a); }
        if (t == 2) { std::cin >> a; solve2(x, a); }
        if (t == 3) { std::cout << solve3(x) << "\n"; }
    }
    return 0;
}
