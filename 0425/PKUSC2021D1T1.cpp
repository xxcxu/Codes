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

static const int N = 1005;
int n, T, P, a[N], b[N];

int inc(int x, int y) { return (x + y) % P; }
int dec(int x, int y) { return (x + P - y) % P; }
int mul(int x, int y) { return 1LL * x * y % P; }

class Matrix {
    private: int n, m;
    public: std::vector<std::vector<int>> a;
    public: Matrix(int n = 0, int m = 0, int p = 0): n(n), m(m) {
        a.resize(n, std::vector<int>(m, 0));
        if (p) for (int i = 0; i < n; ++i) a[i][i] = 1;
    }
    public: std::vector<int>& operator [] (int x) & { return a[x]; }
    public: const std::vector<int>& operator[](int x) const& { return a[x]; }
    public: friend Matrix operator * (const Matrix &a, const Matrix &b) {
        Matrix ans = Matrix(a.n, b.m);
        for (int i = 0; i < a.n; ++i)
            for (int j = 0; j < b.m; ++j)
                for (int k = 0; k < a.m; ++k)
                    ans.a[i][j] = inc(ans.a[i][j], mul(a.a[i][k], b.a[k][j]));
        return ans;
    }
    public: friend Matrix operator ^ (Matrix a, int k) {
        Matrix ans = a;
        for (k = k - 1; k; k >>= 1, a = a * a)
            if (k & 1) ans = ans * a;
        return ans;
    }
};

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("input.in", "r");
    // fout = fopen("output.out", "w+");
    // ferr = fopen("debug.out", "w+");
    n = read(), T = read(), P = read();
    Matrix A = Matrix(n, n);
    int s = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            A[i][j] = read(), s = inc(s, A[i][j]);
            a[i] = inc(a[i], A[i][j]), b[j] = inc(b[j], A[i][j]);
        }
    if (T == 0) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                fprintf(fout, "%d%c", A[i][j] % P, " \n"[j == n - 1]);
        return 0;
    }
    Matrix F = Matrix(1, 2);
    F[0][0] = 1, F[0][1] = 0;
    Matrix Base = Matrix(2, 2);
    Base[0][0] = n, Base[0][1] = mul(s, 2);
    Base[1][0] = 0, Base[1][1] = mul(n, 2);
    if (T > 1) F = F * (Base ^ (T - 1));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            fprintf(fout, "%d%c", inc(mul(F[0][0], inc(a[i], b[j])), F[0][1]), " \n"[j == n - 1]);
    return 0;
}