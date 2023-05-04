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

static const int N = 605, P = 998244353;
static const int dx[] = {1, 1, -1, -1};
static const int dy[] = {1, -1, 1, -1};

[[nodiscard]] int inc(int x, int y) { return (x + y) % P; }
[[nodiscard]] int dec(int x, int y) { return (x + P - y) % P; }
[[nodiscard]] int mul(int x, int y) { return 1LL * x * y % P; }
[[nodiscard]] int qpow(int x, int y) {
    int ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
        if (y & 1) ans = mul(ans, x);
    return ans;
}
[[nodiscard]] int inv(int x) { return qpow(x, P - 2); }

int n, cnt, ans;
int x[N], y[N], fa[N];
int id[N][N];
bool map[N][N];
bool vis[N][N];
std::vector<PII> Union[N];
std::vector<PII> e[N][N];

void dfs(int x, int y, int bel) {
    if (vis[x][y]) return void();
    vis[x][y] = true;
    Union[bel].eb(x, y);
    for (auto [xx, yy] : e[x][y])
        dfs(xx, yy, bel);
    return void();
}

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return void();
    fa[fx] = fy;
    return void();
}

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("input.in", "r");
    // fout = fopen("output.out", "w+");
    // ferr = fopen("debug.out", "w+");
    n = read();
    for (int i = 1; i <= n; ++i) {
        x[i] = read() + 1, y[i] = read() + 1;
        map[x[i]][y[i]] = true;
    }
    for (int i = 1; i <= n; ++i)
        for (int d = 0; d < 4; ++d) {
            int xx = x[i] + dx[d], yy = y[i] + dy[d];
            if (map[xx][yy]) e[x[i]][y[i]].eb(xx, yy);
        }
    for (int i = 1; i <= n; ++i)
        if (!vis[x[i]][y[i]]) dfs(x[i], y[i], ++ cnt);
    for (int i = 1; i <= cnt; ++i) {
        int size = static_cast<int>(Union[i].size());
        for (int j = 0; j < size; ++j) id[Union[i][j].fi][Union[i][j].se] = j + 1;
        for (int sta = 1; sta < (1 << size); ++sta) {
            int res = 0;
            for (int j = 1; j <= size; ++j) fa[j] = j;
            for (auto [nx, ny] : Union[i])
                if (sta >> (id[nx][ny] - 1) & 1)
                    for (int d = 0; d < 4; ++d) {
                        int tx = nx + dx[d], ty = ny + dy[d];
                        if (map[tx][ty] && sta >> (id[tx][ty] - 1) & 1)
                            merge(id[nx][ny], id[tx][ty]);
                    }
            for (auto [nx, ny] : Union[i])
                if (sta >> (id[nx][ny] - 1) & 1)
                    res = inc(res, fa[id[nx][ny]] == id[nx][ny]);
            ans = inc(ans, mul(res, qpow(2, n - size)));
        }
    }
    return fprintf(fout, "%d\n", ans), 0;
}