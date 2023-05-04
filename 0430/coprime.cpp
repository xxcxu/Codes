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

static const int N = 500005;
int n, q, tot; LL ans;
int a[N], mu[N], vis[N], cnt[N], statue[N], prime[N];

void init(int n) {
    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) prime[++tot] = i, mu[i] = -1;
        for (int j = 1; i * prime[j] <= n; ++j) {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) { mu[i * prime[j]] = 0; break; }
            mu[i * prime[j]] = -mu[i];
        }
    }
}

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("coprime.in", "r");
    fout = fopen("coprime.out", "w+");
	init(N - 1);
    n = read(), q = read();
    for (int i = 1; i <= n; ++i) a[i] = read();
    while (q--) {
        static int x;
        x = read();
        statue[x] ^= 1;
        if (statue[x] == 0) {
            for (int i = 1; i * i <= a[x]; ++i)
                if (a[x] % i == 0) {
                    -- cnt[i];
                    ans -= mu[i] * cnt[i];
                    if (a[x] / i != i) {
                        -- cnt[a[x] / i];
                        ans -= mu[a[x] / i] * cnt[a[x] / i];
                    }
                }
        }
        if (statue[x] == 1) {
            for (int i = 1; i * i <= a[x]; ++i)
                if (a[x] % i == 0) {
                    ans += mu[i] * cnt[i];
                    ++ cnt[i];
                    if (a[x] / i != i) {
                        ans += mu[a[x] / i] * cnt[a[x] / i];
                        ++ cnt[a[x] / i];
                    }
                }
        }
        fprintf(fout, "%lld\n", ans);
    }
    return 0;
}