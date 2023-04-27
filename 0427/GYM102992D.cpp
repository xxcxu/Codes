#include <bits/stdc++.h>

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

static const int N = 200005;
int n, m;
int fa[N], deg[N], choose[N];
std::map<PII, int> map;
std::vector<int> e[N];
std::vector<PII> edge;

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

void dfs(int x, int pre, int bel) {
    fa[x] = bel;
    for (int y : e[x]) if (y != pre) dfs(y, x, bel);
}

void print() {
    fputs("Yes\n", fout);
    for (int i = 0; i < m; ++i) {
        if (!choose[i]) continue;
        fprintf(fout, "%d %d\n", edge[i].fi, edge[i].se);
    }
    return void();
}

void solve() {
    n = read(), m = read();
    map.clear(), edge.clear();
    std::iota(fa + 1, fa + n + 1, 1);
    std::memset(deg, 0, (n + 1) * sizeof(int));
    std::memset(choose, 0, (m + 1) * sizeof(int));
    for (int i = 1; i <= n; ++i) e[i].clear();
    for (int i = 1; i <= m; ++i) {
        static int u, v;
        u = read(), v = read();
        if (u > v) std::swap(u, v);
        edge.eb(u, v);
    }
    std::sort(all(edge));
    edge.erase(std::unique(all(edge)), edge.end());
    
    m = (int)edge.size();
    for (int i = 0; i < m; ++i) {
        auto [u, v] = edge[i];
        map[PII(u, v)] = map[PII(v, u)] = i;
        int fu = find(u), fv = find(v);
        if (fu == fv) continue;
        fa[fu] = fv;
        ++ deg[u], ++ deg[v];
        e[u].eb(v), e[v].eb(u);
        choose[i] = true;
    }

    bool Union = true;
    for (int i = 2; i <= n; ++i)
        if (find(i) != find(1)) Union = false;
    if (!Union) return fputs("No\n", fout), void();

    int root = -1;
    for (int i = 1; i <= n; ++i)
        if (deg[i] > n / 2) root = i;
    if (root == -1) return print(), void();

    std::iota(fa + 1, fa + n + 1, 1); 
    for (int i : e[root]) dfs(i, root, i);

    for (int i = 0; i < m; ++i) {
        if (choose[i]) continue;
        auto [u, v] = edge[i];
        int fu = find(u), fv = find(v);
        if (u == root || v == root) continue;
        if (fu == fv) continue;
        -- deg[root];
        -- deg[fu];
        ++ deg[u], ++ deg[v];
        if (deg[u] > n / 2 || deg[v] > n / 2) {
            ++ deg[fu];
            -- deg[fv];
            if (deg[u] > n / 2 || deg[v] > n / 2) {
                ++ deg[root];
                ++ deg[fv];
                -- deg[u], -- deg[v];
            } else {
                fa[fv] = fu;
                choose[i] = true;
                choose[map[PII(root, fv)]] = false;
            }
        } else {
            fa[fu] = fv;
            choose[i] = true;
            choose[map[PII(root, fu)]] = false;
        }
        if (deg[root] <= n / 2) break;
    }
    if (deg[root] <= n / 2) print();
    else fputs("No\n", fout);
    return void();
}

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("input.in", "r");
    // fout = fopen("output.out", "w+");
    // ferr = fopen("debug.out", "w+");
    int t = read();
    while (t--) solve();
    return 0;
}