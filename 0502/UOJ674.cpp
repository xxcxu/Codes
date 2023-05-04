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

static const int N = 205, M = N * N, P = 998244353;
int n, sum[N], edg[N];
int dp[N][M], mat[N][N];
std::vector<int> e[M];

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

int guass(int n) {
	int ans = 1;
	for (int i = 1; i <= n; ++i) {
        int pos = i;
        for (int j = i + 1; j <= n; ++j)
            if (mat[j][i] != 0) pos = j;
        if (!mat[pos][i]) return 0;
        if (pos != i) {
            for (int j = 1; j <= n; ++j) std::swap(mat[i][j], mat[pos][j]);
            ans = P - ans;
        }
        int div = inv(mat[i][i]);
        ans = mul(ans, mat[i][i]);
        for (int j = 1; j <= n; ++j) mat[i][j] = mul(mat[i][j], div);
        for (int k = 1; k <= n; ++k)
            if (k != i) {
                div = mat[k][i];
                for (int j = 1; j <= n; ++j)
                    mat[k][j] = dec(mat[k][j], mul(mat[i][j], div));
            }
	}
	return ans;
}

void solve() {
    n = read();
    for (int i = 1; i <= n; ++i) sum[i] = read(), sum[i] += sum[i - 1];
    for (int i = 1; i <= sum[n]; ++i) e[i].clear();
    for (int i = 1; i < n; ++i) edg[i] = read();
    for (int i = 1; i < n; ++i)
        for (int j = 1; j <= edg[i]; ++j) {
            static int u, v;
            u = read(), v = read();
            e[sum[i - 1] + u].eb(sum[i] + v);
        }
    std::memset(dp, 0, sizeof dp);
    for (int i = 1; i <= sum[1]; ++i) dp[i][i] = 1;
    for (int i = 2; i <= n; ++i) {
        for (int j = sum[i - 2] + 1; j <= sum[i - 1]; ++j)
            for (int k : e[j])
                for (int from = 1; from <= sum[1]; ++from)
                    dp[from][k] = inc(dp[from][k], dp[from][j]);
    }
    for (int i = 1; i <= sum[1]; ++i)
        for (int j = sum[n - 1] + 1; j <= sum[n]; ++j)
            mat[i][j - sum[n - 1]] = dp[i][j];
    return fprintf(fout, "%d\n", guass(sum[1])), void();
}

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("input.in", "r");
    // fout = fopen("output.out", "w+");
    // ferr = fopen("debug.out", "w+");
    int t = read();
    while (t--) solve();    
    return 0;
}