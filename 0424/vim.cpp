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

static const int N = 70005, S = 11, inf = 0x3f3f3f3f;
int n, m, cnt, tag, need[N];
int sum[N];
int dp[N][S], f[N][S][S];
char s[N];
int t[N];

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("input.in", "r");
    // fout = fopen("output.out", "w+");
    // ferr = fopen("debug.out", "w+");
    n = read();
    fscanf(fin, "%s", s + 1);
    for (int i = 1; i <= n; ++i) {
        if (s[i] == 'e') ++ cnt, tag = 1;
        else t[++m] = s[i] - 'a', need[m] = tag, tag = 0;
    }
    std::memset(dp, 0x3f, sizeof dp);
    std::memset(f, 0x3f, sizeof f);
    dp[0][t[1]] = 0;
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < S; ++j) {

            if (j != t[i] && !need[i]) dp[i][j] = std::min(dp[i][j], dp[i - 1][j]);
            dp[i][j] = std::min(dp[i][j], dp[i - 1][t[i]] + 2);
            if (j != t[i]) dp[i][j] = std::min(dp[i][j], f[i - 1][t[i]][j]);
            dp[i][j] = std::min(dp[i][j], f[i - 1][t[i]][t[i]] + 2);
            
            for (int k = 0; k < S; ++k) {
                if (j != t[i]) f[i][j][k] = std::min(f[i][j][k], dp[i - 1][j] + 3);
                f[i][j][k] = std::min(f[i][j][k], dp[i - 1][t[i]] + 5);
                if (j != t[i] && k != t[i]) f[i][j][k] = std::min(f[i][j][k], f[i - 1][j][k] + 1);
                if (j != t[i]) f[i][j][k] = std::min(f[i][j][k], f[i - 1][j][t[i]] + 3);
                if (k != t[i]) f[i][j][k] = std::min(f[i][j][k], f[i - 1][t[i]][k] + 3);
                f[i][j][k] = std::min(f[i][j][k], f[i - 1][t[i]][t[i]] + 5);
            }
        }
    }
    return fprintf(fout, "%d\n", dp[m][10] + 2 * (cnt - 1)), 0;
}