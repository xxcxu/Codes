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

static const int N = 1000005, M = 2 * N;
int n, m, q, dp[N], ans[M];

struct Edge {
    int fro, ver, lik;
    Edge(int fro = 0, int ver = 0, int lik = 0):
        fro(fro), ver(ver), lik(lik) {}
} e[M];

struct Query {
    int x, l, r, id;
    Query(int x = 0, int l = 0, int r = 0, int id = 0):
        x(x), l(l), r(r), id(id) {}
} qu[M];

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("input.in", "r");
    // fout = fopen("output.out", "w+");
    // ferr = fopen("debug.out", "w+");
    n = read(), m = read(), q = read();
    for (int i = 1; i <= m; ++i) {
        static int u, v, w;
        u = read(), v = read(), w = read(); 
        e[i] = Edge(v, u, w);
    }
    for (int i = 1; i <= q; ++i) {
        static int x, l, r;
        x = read(), l = read(), r = read();
        qu[i] = Query(x, l, r, i);
    }
    std::sort(e + 1, e + m + 1, [=](const Edge &a, const Edge &b) { return a.lik < b.lik; });
    std::sort(qu + 1, qu + q + 1, [=](const Query &a, const Query &b) { return a.r < b.r; });
    int j = 1;
    for (int i = 1, k; i <= m; i = k) {
        while (j <= q && qu[j].r < e[i].lik)
            ans[qu[j].id] = dp[qu[j].x] >= qu[j].l, ++ j;
        dp[1] = e[k = i].lik;
        while (k <= m && e[i].lik == e[k].lik) ++ k;
        std::vector<PII> vec;
        for (int p = i; p < k; ++p) vec.eb(e[p].ver, dp[e[p].fro]);
        for (auto [fi, se] : vec) dp[fi] = std::max(dp[fi], se);
    }
    while (j <= q) ans[qu[j].id] = dp[qu[j].x] >= qu[j].l, ++ j;
    for (int i = 1; i <= q; ++i) fputs(ans[i] ? "Yes\n" : "No\n", fout);
    return 0;
}