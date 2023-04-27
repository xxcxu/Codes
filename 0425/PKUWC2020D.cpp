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

static const int N = 400'005;
int n, q;
int sum[N], pai[N];
char s[N];


signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    n = read(), q = read();
    fscanf(fin, "%s", s + 1);
    for (int i = 1; i <= n; ++i) {
        static int cnt = 0;
        sum[i] = sum[i - 1] + (s[i] == '1');
        pai[i] = pai[i - 1];
        if (s[i] == '1')
            if (cnt) ++ pai[i], -- cnt;
        if (s[i] == '0')
            ++ cnt;
    }
    while (q--) {
        static int x, k;
        x = read(), k = read();
        if (sum[k] < x) fprintf(fout, "%d\n", -1);
        else if (sum[k] - x < pai[k]) fprintf(fout, "%d\n", sum[k] - x);
        else fprintf(fout, "%d\n", pai[k] + (sum[k] - x - pai[k]) / 2);
    }
    return 0;
}