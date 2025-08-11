#include <bits/stdc++.h>

#define int long long

constexpr int N = 3e5 + 7;
constexpr int inf = 1e9;

int n, ncnt;
std::string s;
int w[N];
int fa[N], dep[N], siz[N], son[N];
int top[N], dfn[N], rnk[N];

std::vector<std::pair<int, int>> G[N];

struct edge {
    int u, v, w, x;
} E[N << 1];

struct SegTree {
    struct node {
        int val, mxn;
    } tr[N << 2];

    #define ls(o) (o << 1)
    #define rs(o) (o << 1 | 1)

    void pushup(int o) {
        tr[o].mxn = std::max(tr[ls(o)].mxn, tr[rs(o)].mxn);
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

    int query(int o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tr[o].mxn;
        int mid = (l + r) >> 1,
            res = -inf;
        if (ql <= mid)
            res = std::max(res, query(ls(o), l, mid, ql, qr));
        if (qr > mid)
            res = std::max(res, query(rs(o), mid + 1, r, ql, qr));
        return res;
    }
} seg;

void dfs0(int u, int pa, int k) {
    w[u] = k;
    for (auto i : G[u]) {
        auto [v, w] = i;
        if (v == pa)
            continue;
        dfs0(v, u, w);
    }
}

void dfs1(int u) {
    son[u] = -1, siz[u] = 1;
    for (auto i : G[u]) {
        auto [v, w] = i;
        if (v == fa[u])
            continue;
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
    for (auto i : G[u]) {
        auto [v, w] = i;
        if (v != son[u] && v != fa[u])
            dfs2(v, v);
    }
}

int solve(int x, int y) {
    int res = -inf;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]])
            std::swap(x, y);
        res = std::max(res, seg.query(1, 1, n, dfn[top[x]], dfn[x]));
        x = fa[top[x]];
    }
    if (dep[x] > dep[y])
        std::swap(x, y);
    res = std::max(res, seg.query(1, 1, n, dfn[x] + 1, dfn[y]));
    return res;
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i < n; i++) {
        std::cin >> E[i].u >> E[i].v >> E[i].w;
        G[E[i].u].push_back({E[i].v, E[i].w});
        G[E[i].v].push_back({E[i].u, E[i].w});
    }
    dfs0(1, 0, -inf);
    dfs1(1);
    dfs2(1, 1);
    seg.build(1, 1, n);
    for (int i = 1; i < n; i++) {
        if (fa[E[i].u] == E[i].v)
            E[i].x = E[i].u;
        else
            E[i].x = E[i].v;
    }
    while (std::cin >> s) {
        int a, b;
        if (s == "DONE")
            break;
        if (s == "CHANGE") {
            std::cin >> a >> b;
            seg.update(1, 1, n, dfn[E[a].x], b);
        }
        if (s == "QUERY") {
            std::cin >> a >> b;
            if (a == b)
                std::cout << "0\n";
            else
                std::cout << solve(a, b) << "\n";
        }
    }
    return 0;
}
