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
int n, dp[N][5];
std::map<char, int> map;
char s[N];

int inc(int x, int y) { return (x + y) % P; }
template<typename ...Args>
int inc(int x, Args... args) { return inc(x, inc(args...)); }

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("mine.in", "r");
    fout = fopen("mine.out", "w+");
    fscanf(fin, "%s", s + 1);
    n = strlen(s + 1);
    map['*'] = 0, map['0'] = 1, map['2'] = 4;
    for (int i = 1; i <= n; ++i) {
        if (s[i] != '?' && s[i] != '1') dp[i][map[s[i]]] = 1;
        else if (s[i] == '1') dp[i][2] = dp[i][3] = 1;
        else dp[i][0] = dp[i][1] = dp[i][2] = dp[i][3] = dp[i][4] = 1;
    }
    dp[1][4] = 0, dp[1][3] = 0;
    for (int i = 2; i <= n; ++i) {
        dp[i][0] = dp[i][0] * inc(dp[i - 1][0], dp[i - 1][2], dp[i - 1][4]); // * = ** + /1* + *2*
        dp[i][1] = dp[i][1] * inc(dp[i - 1][1], dp[i - 1][3]); // 0 = 00 + *10 + *20
        dp[i][2] = dp[i][2] * inc(dp[i - 1][1], dp[i - 1][3]); // /1* = 01 + *11
        dp[i][3] = dp[i][3] * dp[i - 1][0]; // *1/
        dp[i][4] = dp[i][4] * dp[i - 1][0]; 
    }
    int ans = 0;
    ans = inc(dp[n][0], dp[n][1], dp[n][3]);
    fprintf(fout, "%d\n", ans);
    return 0;
}