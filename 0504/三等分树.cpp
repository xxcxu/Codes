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

static const int N = 100005;

int n, cnt, sumv; LL ans;
int v[N], sum[N], sum2[N];
std::vector<int> e[N];

void dfs(int x, int fa) {
    sum[x] = v[x];
    for (int y : e[x])
        if (y != fa) {
            dfs(y, x);
            sum[x] += sum[y];
            sum2[x] += sum2[y];
        }
    if (x == e[0][0]) return void();
    if (sum[x] == sumv / 3 * 2) ans += sum2[x];
    if (sum[x] == sumv / 3) ans += (cnt - sum2[x]), ++ sum2[x], ++ cnt;
    return void();
}

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("input.in", "r");
    // fout = fopen("output.out", "w+");
    // ferr = fopen("debug.out", "w+");
    n = read();
    for (int i = 1; i <= n; ++i) {
        static int x;
        v[i] = read(), x = read();
        e[x].eb(i);
        sumv += v[i];
    }
    if (sumv % 3 != 0) return fprintf(fout, "%d\n", 0), 0;
    dfs(e[0][0], 0);
    return fprintf(fout, "%lld\n", ans), 0;
}