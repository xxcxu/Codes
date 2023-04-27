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

static const int N = 2005, M = 200005;
static const int dx[] = {0, 0, 1, -1};
static const int dy[] = {1, -1, 0, 0};
int n, m, p, q;
int fa[M], dep[M];
int bel[N][N], dis[N][N];
int anc[M][32], max[M][32];
char mat[N][N];
bool vis[M];
std::vector<PII> e[M], edge[N * N];
std::queue<PII> que;

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
bool merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    fa[x] = y;
    return true;
}
void dfs(int x, int pre) {
    dep[x] = dep[pre] + 1;
    anc[x][0] = pre;
    vis[x] = true;
    for (int i = 1; i <= 25; ++i) {
        anc[x][i] = anc[anc[x][i - 1]][i - 1];
        max[x][i] = std::max(max[anc[x][i - 1]][i - 1], max[x][i - 1]);
    }
    for (auto& [y, z] : e[x])
        if (y != pre) max[y][0] = z, dfs(y, x);
    return void();
}
int Lca(int x, int y) {
    int ans = 0;
    if (dep[x] < dep[y]) std::swap(x, y);
    for (int i = 25; i >= 0; --i)
        if (dep[anc[x][i]] >= dep[y])
            ans = std::max(ans, max[x][i]), x = anc[x][i];
    if (x == y) return ans;
    for (int i = 25; i >= 0; --i)
        if (anc[x][i] != anc[y][i]) {
            ans = std::max(ans, max[x][i]);
            ans = std::max(ans, max[y][i]);
            x = anc[x][i], y = anc[y][i];
        }
    return std::max({ans, max[x][0], max[y][0]});
}

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("input.in", "r");
    // fout = fopen("output.out", "w+");
    // ferr = fopen("debug.out", "w+");
    n = read(), m = read(), p = read(), q = read();
    for (int i = 1; i <= n; ++i) fscanf(fin, "%s", mat[i] + 1);
    for (int i = 1; i <= p; ++i) {
        static int x, y;
        x = read(), y = read();
        bel[x][y] = i;
        que.ep(x, y);
    }
    while (que.size()) {
        auto& [x, y] = que.front(); que.pop();
        for (int d = 0; d < 4; ++d) {
            int xx = x + dx[d], yy = y + dy[d];
            if (xx < 1 || xx > n || yy < 1 || yy > m) continue;
            if (mat[xx][yy] == '#') continue;
            if (!bel[xx][yy]) {
                bel[xx][yy] = bel[x][y];
                dis[xx][yy] = dis[x][y] + 1;
                que.ep(xx, yy);
            } else if (bel[xx][yy] != bel[x][y]) {
                edge[dis[xx][yy] + dis[x][y]].eb(bel[xx][yy], bel[x][y]);
            }
        }
    }
    std::iota(fa + 1, fa + p + 1, 1);
    for (int i = 0; i <= n * m; ++i)
        for (auto& [u, v] : edge[i])
            if (merge(u, v)) e[u].eb(v, i), e[v].eb(u, i);
    for (int i = 1; i <= p; ++i) if (!vis[i]) dfs(i, 0);

    for (int i = 1; i <= q; ++i) {
        static int x, y;
        x = read(), y = read();
        if (find(x) != find(y)) fprintf(fout, "%d\n", -1);
        else fprintf(fout, "%d\n", Lca(x, y));
    }
    return 0;
}