#include <bits/stdc++.h>

namespace Header { // Header
    using PII = std::pair<int, int>;
    using LL = long long;
    using DB = double;
    using LD = long double;

    #define fi first
    #define se second
    #define ep emplace
    #define eb emplace_back
    #define all(x) x.begin(), x.end()
    #define debug(i, a, n) for (int i : Range<int>(1, n)) fprintf(ferr, "%d%c", a[i], " \n"[i == n]);

    FILE* fin, * fout, * ferr;
    int read() {
        int t = 0, f = 0;
        char ch = fgetc(fin);
        for (; !isdigit(ch); ch = fgetc(fin)) f ^= (ch == '-');
        for (; isdigit(ch); ch = fgetc(fin)) t = (t << 1) + (t << 3) + (ch ^ 48);
        return f ? ~t + 1 : t;
    }

    template<typename T>
    class Iterator {
    public:
        Iterator(T _val = 0): _value(_val) {}
        bool operator != (const Iterator& other) const { return this->_value != other._value; }
        const T& operator *() { return _value; }
        T operator ++() { return ++_value; }
    private:
        T _value;
    };
    template<typename T>
    class Range {
    public:
        Range(T l = 0, T r = 0): __begin(l), __end(r + 1) {}
        Iterator<T> begin() { return Iterator<T>(__begin); }
        Iterator<T> end() { return Iterator<T>(__end); }
    private:
        T __begin;
        T __end;
    };
};
using namespace Header;

static const int N = 100005, M = 1000005, P = 1000000007;

namespace MathMoudle { // Moudle
    int inc(int x, int y) { return (x + y) % P; }
    int dec(int x, int y) { return (x + P - y) % P; }
    int mul(int x, int y) { return 1LL * x * y % P; }
}
using namespace MathMoudle;

int n, qs, B, now;
int a[N], ans[N];
int cnt[M], ind[N][205];
int dep[N], anc[N][32];
int tot, eu[N << 1], s[N], t[N];
std::vector<int> e[N];
struct query {
    int l, r, id, x;
    query() = default;
    query(int l, int r, int x, int id):
        l(l), r(r), x(x), id(id) {}
} q[N];
int pc, max[M], inv[M], prime[N];
bool vis[M];

void init(int n) {
    for (int i = 2; i <= n; ++i)
        if (!vis[i]) {
            if (i <= 1000) prime[++pc] = i;
            for (int j = i; j <= n; j += i) vis[j] = true, max[j] = i;
        }
    inv[0] = inv[1] = 1;
    for (int i = 2; i <= n; ++i)
        inv[i] = mul(P - P / i, inv[P % i]);
}
int count(int x, int p) {
    int res = 0;
    while (x % p == 0) ++ res, x /= p;
    return res;
}
void dfs(int x, int fa) {
    dep[x] = dep[fa] + 1;
    anc[x][0] = fa;
    for (int i = 1; i <= 25; ++i)
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
    for (int i = 1; i <= pc; ++i)
        ind[x][i] = ind[fa][i] + count(a[x], prime[i]);
    eu[++ tot] = x, s[x] = tot;
    for (int y : e[x]) if (y != fa) dfs(y, x);
    eu[++ tot] = x, t[x] = tot;
}
int Lca(int x, int y) {
    if (dep[x] < dep[y]) std::swap(x, y);
    for (int i = 25; i >= 0; --i)
        if (dep[anc[x][i]] >= dep[y]) x = anc[x][i];
    if (x == y) return x;
    for (int i = 25; i >= 0; --i)
        if (anc[x][i] != anc[y][i])
            x = anc[x][i], y = anc[y][i];
    return anc[x][0];
}
void add(int x) {
    vis[x] ^= 1;
    int v = max[a[x]];
    if (v > 1000) {
        now = mul(now, inv[cnt[v]]);
        now = mul(now, ++ cnt[v]);
    }
    return void();
}
void del(int x) {
    vis[x] ^= 1;
    int v = max[a[x]];
    if (v > 1000) {
        now = mul(now, inv[cnt[v]]);
        now = mul(now, -- cnt[v]);
    }
    return void();
}
void upd(int x) {
    vis[x] ? (del(x), 0) : (add(x), 0);
    return void();
}

void solve() {
    n = read(), B = static_cast<int>(std::sqrt(n));
    [&]() {
        tot = 0, now = 1;
        for (int i = 1; i <= n; ++i) e[i].clear();
        for (int i = 1; i <= n; ++i) vis[i] = false;
    } ();
    for (int i = 1; i < n; ++i) {
        static int u, v;
        u = read(), v = read();
        e[u].eb(v), e[v].eb(u);
    }
    for (int i = 1; i <= n; ++i) {
        a[i] = read();
        cnt[max[a[i]]] = 1;
    }
    dfs(1, 0);

    qs = read();
    for (int i = 1; i <= qs; ++i) {
        static int u, v;
        u = read(), v = read();
        int lca = Lca(u, v);
        ans[i] = 1;
        for (int j = 1; j <= pc; ++j)
            ans[i] = mul(ans[i], ind[u][j] + ind[v][j] - ind[lca][j] - ind[anc[lca][0]][j] + 1);
        if (s[u] > s[v]) std::swap(u, v);
        q[i] = query(u == 1 ? s[u] : t[u], s[v], lca, i);
    }
    std::sort(q + 1, q + qs + 1, [&](const query &a, const query &b) {
        if (a.l / B != b.l / B) return a.l / B < b.l / B;
        return a.r < b.r;
    });
    int l = 1, r = 0;
    for (int i = 1; i <= qs; ++i) {
        while (l > q[i].l) upd(eu[--l]);
        while (r < q[i].r) upd(eu[++r]);
        while (l < q[i].l) upd(eu[l++]);
        while (r > q[i].r) upd(eu[r--]);
        if (!vis[q[i].x]) add(q[i].x), vis[q[i].x] ^= 1;
        ans[q[i].id] = mul(ans[q[i].id], now);
        if (!vis[q[i].x]) del(q[i].x), vis[q[i].x] ^= 1;
    }
    for (int i = 1; i <= qs; ++i) fprintf(fout, "%d\n", ans[i]);
    return void();
}

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("input.in", "r");
    fout = fopen("output.out", "w+");
    ferr = fopen("debug.out", "w+");
    init(M - 1);
    int t = read();
    while (t--) solve();
    return 0;
}