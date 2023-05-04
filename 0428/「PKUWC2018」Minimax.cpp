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

static const int N = 300005, P = 998244353;
int n, m;
int a[N], b[N], p[N], prob[N];
int ch[N][2], size[N];

int inc(int x, int y) { return (x + y) % P; }
int dec(int x, int y) { return (x + P - y) % P; }
int mul(int x, int y) { return 1LL * x * y % P; }
template<typename ...Args>
int mul(int x, Args... args) { return mul(x, mul(args...)); }
int qpow(int x, int y) {
    int ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
        if (y & 1) ans = mul(ans, x);
    return ans;
}

int tot = 0, rt[N];
int dp[N * 20], tag[N * 20], lson[N * 20], rson[N * 20];
void pushup(int x) { return dp[x] = inc(dp[lson[x]], dp[rson[x]]), void(); }
void pushdown(int x) {
    if (tag[x] != 1) {
        dp[lson[x]] = mul(dp[lson[x]], tag[x]);
        dp[rson[x]] = mul(dp[rson[x]], tag[x]);
        tag[lson[x]] = mul(tag[lson[x]], tag[x]);
        tag[rson[x]] = mul(tag[rson[x]], tag[x]);
        tag[x] = 1;
    }
    return void();
}
void insert(int &x, int l, int r, int p) {
    if (!x) x = ++ tot, tag[x] = 1;
    if (l == r) return dp[x] = 1, void();
    int mid = (l + r) >> 1;
    if (p <= mid) insert(lson[x], l, mid, p);
    else insert(rson[x], mid + 1, r, p);
    return pushup(x);
}
int merge(int x, int y, int l, int r, int mulx, int muly, int p, int q) {
    if (!x) return dp[y] = mul(dp[y], muly), tag[y] = mul(tag[y], muly), y;
    if (!y) return dp[x] = mul(dp[x], mulx), tag[x] = mul(tag[x], mulx), x;
    int mid = (l + r) >> 1;
    pushdown(x), pushdown(y);
    int xl = dp[lson[x]], xr = dp[rson[x]];
    int yl = dp[lson[y]], yr = dp[rson[y]];
    lson[x] = merge(lson[x], lson[y], l, mid, inc(mulx, mul(yr, q)), inc(muly, mul(xr, q)), p, q);
    rson[x] = merge(rson[x], rson[y], mid + 1, r, inc(mulx, mul(yl, p)), inc(muly, mul(xl, p)), p, q);
    return pushup(x), x;
}
void solve(int x, int l, int r) {
    if (!x) return void();
    if (l == r) return prob[l] = dp[x], void();
    pushdown(x);
    int mid = (l + r) >> 1;
    solve(lson[x], l, mid);
    solve(rson[x], mid + 1, r);
    return void();
}

void dfs(int x) {
    if (size[x] == 0) return insert(rt[x], 1, m, a[x]), void();
    if (ch[x][0]) dfs(ch[x][0]);
    if (ch[x][1]) dfs(ch[x][1]);
    if (size[x] == 1) rt[x] = rt[ch[x][0]];
    if (size[x] == 2) rt[x] = merge(rt[ch[x][0]], rt[ch[x][1]], 1, m, 0, 0, p[x], dec(1, p[x]));
    return void();
}

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("input.in", "r");
    // fout = fopen("output.out", "w+");
    // ferr = fopen("debug.out", "w+");
    int inv10000 = qpow(10000, P - 2);
    n = read();
    for (int i = 1; i <= n; ++i) {
        static int fa;
        fa = read();
        ch[fa][size[fa]++] = i;
    }
    for (int i = 1; i <= n; ++i) {
        int x = read();
        if (size[i]) p[i] = mul(x, inv10000);
        else a[i] = b[++m] = x;
    }
    std::sort(b + 1, b + m + 1);
    m = std::unique(b + 1, b + m + 1) - b - 1;
    for (int i = 1; i <= n; ++i) a[i] = std::lower_bound(b + 1, b + m + 1, a[i]) - b;
    dfs(1);
    solve(rt[1], 1, m);
    int ans = 0;
    for (int i = 1; i <= m; ++i) ans = inc(ans, mul(i, b[i], prob[i], prob[i]));
    return fprintf(fout, "%d\n", ans), 0;
}