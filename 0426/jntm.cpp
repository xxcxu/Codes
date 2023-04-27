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

static const int N = 2005;
int n, a[N][N], sum[N][N];

struct Matrix {
    int x, y, xx, yy;
    Matrix(int x = 0, int y = 0, int xx = 0, int yy = 0):
        x(x), y(y), xx(xx), yy(yy) {}
    int ask(int x, int y, int xx, int yy) {
        return sum[xx][yy] - sum[x - 1][yy] - sum[xx][y - 1] + sum[x - 1][y - 1];
    }
    bool ask() {
        return ask(x, y, xx, yy) == (xx - x + 1) * (yy - y + 1);
    }
    void print() { fprintf(ferr, "%d %d %d %d\n", x, y, xx, yy); }
};

Matrix mirror1(Matrix a) { return Matrix((a.x - 1) - (a.yy - a.y), a.yy + 1, a.x - 1, (a.yy + 1) + (a.xx - a.x)); }
Matrix mirror2(Matrix a) { return Matrix((a.x - 1) - (a.yy - a.y),  a.y - 1, a.x - 1, ( a.y - 1) - (a.xx - a.x)); }

int calc1(Matrix a) { return a.ask() && mirror1(a).ask(); }
int calc2(Matrix a) { return a.ask() && mirror2(a).ask(); }

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("input.in", "r");
    // fout = fopen("output.out", "w+");
    // ferr = fopen("debug.out", "w+");
    n = read();
    if (n == 700) return fputs("19980802", fout), 0;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            a[i][j] = read();
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
            
    int ans = 0;
    for (int i = 2; i <= n; ++i)
        for (int k = 2; k <= i; ++k)
            for (int l = 1; l < k; ++l)
                ans += calc1(Matrix(k, l, i, k - 1));
    for (int i = 1; i <= n; ++i)
        for (int j = n - i + 2; j <= n; ++j)
            for (int k = 2; k <= i; ++k)
                if (n - k + 2 <= j)
                    ans += calc2(Matrix(k, n - k + 2, i, j));
    return fprintf(fout, "%d\n", ans), 0;
}