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

static const int N = 100005, inf = 0x3f3f3f3f;
int n, a[N];

template<int N, int size>
class St_Table {
    private: int f[N][size], g[N][size], p[N][size];
    public: void init(int n, int *a) {
        for (int i = 1; i <= n; ++i) f[i][0] = a[i], g[i][0] = a[i], p[i][0] = i;
        for (int j = 1; j <= size; ++j)
            for (int i = 1; i <= n - (1ll << j) + 1; ++i) {
                if (f[i][j - 1] >= f[i + (1 << (j - 1))][j - 1]) {
                    f[i][j] = f[i][j - 1];
                    p[i][j] = p[i][j - 1];
                } else {
                    f[i][j] = f[i + (1 << (j - 1))][j - 1];
                    p[i][j] = p[i + (1 << (j - 1))][j - 1];
                }
                g[i][j] = std::min(g[i][j - 1], g[i + (1 << (j - 1))][j - 1]);
            }
        return void();
    }
    public: int ask1(int l, int r) {
        int k = std::log2(r - l + 1);
        return std::min(g[l][k], g[r - (1 << k) + 1][k]);
    }
    public: int ask2(int l, int r) {
        int k = std::log2(r - l + 1);
        return f[l][k] >= f[r - (1 << k) + 1][k] ? p[l][k] : p[r - (1 << k) + 1][k];
    }
};
St_Table<N, 25> table;

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("one.in", "r");
    fout = fopen("one.out", "w+");
    n = read();
    for (int i = 1; i <= n; ++i) a[i] = read();
    table.init(n, a);
    int last = 0, max = inf, now_max = 0;
    while (last < n) {
        int pos = table.ask2(last + 1, n);
        if (a[pos] <= now_max) return fprintf(fout, "%d\n", now_max), 0;
        int delete_max = std::min(max, table.ask1(last + 1, pos));
        max = delete_max;
        now_max = std::max(now_max, a[pos] - delete_max);
        last = pos;
    }
    return fprintf(fout, "%d\n", now_max), 0;
}