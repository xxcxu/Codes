#include <bits/stdc++.h>

using PII = std::pair<int, int>;
using LL = long long;
using DB = double;
using LD = long double;
using t3i = std::tuple<int, int, int>;

#define fi first
#define se second
#define ep emplace
#define eb emplace_back
#define all(x) x.begin(), x.end()

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

static const int N = 205;
int n, ans, suma, sumb;
int a[N], b[N], c[N];
int dp[2][N][N * N];

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("input.in", "r");
    // fout = fopen("output.out", "w+");
    // ferr = fopen("debug.out", "w+");
    n = read();
    for (int i = 1; i <= n; ++i) a[i] = read(), suma += a[i];
    for (int i = 1; i <= n; ++i) b[i] = read(), sumb += b[i];
    for (int i = 1; i <= n; ++i) c[i] = std::min(a[i], b[i]);
    for (int i = 1; i <= n; ++i) ans += std::max(a[i] - b[i], 0);

    std::memset(dp, 0x3f, sizeof dp);
    for (int i = suma; i <= sumb; ++i) dp[0][0][i] = 0; 
    for (int i = 1; i <= n; ++i) {
        std::memcpy(dp[i & 1][0] + suma, dp[i + 1 & 1][0] + suma, (sumb - suma + 1) * sizeof(int));
        for (int j = 1; j < n; ++j)
            for (int k = suma; k <= sumb; ++k)
                dp[i & 1][j][k] = std::min(dp[i + 1 & 1][j][k], dp[i + 1 & 1][j - 1][k + b[i]] + c[i]);
    }
    
    for (int i = 0; i < n; ++i)
        fprintf(fout, "%d%c", dp[n & 1][i][suma] < 0x3f3f3f3f ? 2 * (dp[n & 1][i][suma] + ans) : -1, " \n"[i == n - 1]);
    return 0;
}
