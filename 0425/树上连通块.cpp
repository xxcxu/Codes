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
#define debug(i, a, n) for (int i : Range<int>(1, n)) fprintf(fout, "%d%c", a[i], " \n"[i == n]);

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
int inv(int x) { return qpow(x, P - 2); }

int n, g[N], dp[N];
std::vector<int> e[N];

void dfs(int x, int fa) {
    dp[x] = 1;
    for (int y : e[x])
        if (y != fa) dfs(y, x), dp[x] = mul(dp[x], inc(dp[y], 1));
    return void();
} 

void dfs2(int x, int fa) {
    std::vector<int> pre, suf;
    pre.clear(), suf.clear();
    g[x] = dp[x];
    for (int y : e[x]) {
        pre.emplace_back(inc(dp[y], 1));
        suf.emplace_back(inc(dp[y], 1));
    }
    int son = (int)pre.size();
    for (int i = 1; i < son; ++i) pre[i] = mul(pre[i - 1], pre[i]);
    for (int i = son - 2; i >= 0; --i) suf[i] = mul(suf[i + 1], suf[i]);
    if (x == 1) fprintf(ferr, "%d %d\n", pre[0], pre[1]);
    for (int i = 0; i < (int)e[x].size(); ++i)
        if (int y = e[x][i]; y != fa) {
            dp[x] = mul(i > 0 ? pre[i - 1] : 1, i < son - 1 ? suf[i + 1] : 1);
            if (y == 3) fprintf(ferr, "%d %d\n", i > 0 ? pre[i - 1] : 1, i                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  < son - 1 ? suf[i + 1] : 1);
            if (y == 3) fprintf(ferr, "%d\n", inc(dp[x], 1));
            dp[y] = mul(dp[y], inc(dp[x], 1));
            dfs2(y, x);
        }
}

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("input.in", "r");
    // fout = fopen("output.out", "w+");
    // ferr = fopen("debug.out", "w+");
    n = read();
    for (int i = 1; i < n; ++i) {
        static int u, v;
        u = read(), v = read();
        e[u].eb(v), e[v].eb(u);
    }
    dfs(1, 0);
    dfs2(1, 0);
    for (int i = 1; i <= n; ++i) fprintf(fout, "%d\n", g[i]);
    return 0;
}