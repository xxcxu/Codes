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

static const int N = 1000005, P = 1000000007;

int inc(int x, int y) { return (x + y) % P; }
int dec(int x, int y) { return (x + P - y) % P; }
int mul(int x, int y) { return 1LL * x * y % P; }
int qpow(int x, int y) {
    int ans = 1;
    for (; y; y >>= 1, x = mul(x, x))
        if (y & 1) ans = mul(ans, x);
    return ans;
}

int n, dp[N], siz[N], fac[N], inv[N];
std::vector<int> e[N];

void init(int n) {
    fac[0] = 1;
    for (int i : Range<int>(1, n)) fac[i] = mul(fac[i - 1], i);
    inv[n] = qpow(fac[n], P - 2);
    for (int i = n - 1; i >= 0; --i) inv[i] = mul(inv[i + 1], i + 1);
    return void();
}

int binom(int n, int m) {
    if (n < m || m < 0) return 0;
    return mul(fac[n], mul(inv[m], inv[n - m]));
}

void dfs(int x, int fa) {
    siz[x] = 1;
    for (int y : e[x])
        if (y != fa)
            dfs(y, x), siz[x] += siz[y];
    return void();
}

void dfs2(int x, int fa) {
    dp[x] = fac[siz[x] - 1];
    for (int y : e[x])
        if (y != fa)
            dfs2(y, x), dp[x] = mul(dp[x], mul(dp[y], inv[siz[y]]));
    return void();
}

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("input.in", "r");
    // fout = fopen("output.out", "w+");
    // ferr = fopen("debug.out", "w+");
    n = read(), init(n);
    for (int i : Range<int>(1, n - 1)) {
        static int u, v;
        u = read(), v = read();
        e[u].eb(v), e[v].eb(u);
    }
    dfs(1, 0);
    dfs2(1, 0);
    return fprintf(fout, "%d\n", dp[1]), 0;
}