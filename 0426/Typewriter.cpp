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

bool check(int x) {
    if (x == 0) return false;
    while (x) {
        if (x % 10 == 0 || x % 10 == 1) return false;
        x /= 10;
    }
    return true;
}

static const int N = 105;

int n;
char str[N], s[N], s2[N], t[N];

bool solve2(char *str, int n, int m) {
    char *a = new char[n + 1]();
    char *b = new char[n + 1]();

    auto sub = [&](int i, auto dec) -> void {
        if (i == 0) -- str[i];
        else {
            if (str[i] == 0) str[i] = 9, dec(i - 1, dec);
            else str[i] = str[i] - 1; 
            return void();
        }
    };

    int st = 1;
    for (int i = n; i > m; --i) {
        if (str[i] == 0) a[i] = b[i] = 5, sub(i - 1, sub);
        if (str[i] == 1) a[i] = 5, b[i] = 6, sub(i - 1, sub); 
        if (str[i] == 2) a[i] = 6, b[i] = 6, sub(i - 1, sub);
        if (str[i] == 3) a[i] = 6, b[i] = 7, sub(i - 1, sub);
        if (str[i] == 4) if (i != m + 1 || str[1] == 1) a[i] = 7, b[i] = 7, sub(i - 1, sub); else a[i] = 2, b[i] = 2;
        if (str[i] == 5) if (i != m + 1 || str[1] == 1) a[i] = 7, b[i] = 8, sub(i - 1, sub); else a[i] = 2, b[i] = 3;
        if (str[i] == 6) if (i != m + 1 || str[1] == 1) a[i] = 8, b[i] = 8, sub(i - 1, sub); else a[i] = 3, b[i] = 3;
        if (str[i] == 7) if (i != m + 1 || str[1] == 1) a[i] = 8, b[i] = 9, sub(i - 1, sub); else a[i] = 3, b[i] = 4;
        if (str[i] == 8) if (i != m + 1 || str[1] == 1) a[i] = 9, b[i] = 9, sub(i - 1, sub); else a[i] = 4, b[i] = 4;
        if (str[i] == 9) a[i] = 4, b[i] = 5;
    }
    for (int i = m; i >= 1; --i) {
        a[i] = str[i];
        b[i] = 0;
    }
    while (a[st] == 0) ++ st;
    if (str[0] < 0) return false;
    for (int i = st; i <= n; ++i) if (a[i] == 0 || a[i] == 1) return false;
    for (int i = st; i <= n; ++i) fputc(a[i] + '0', fout);
    fputc(' ', fout);
    for (int i = m + 1; i <= n; ++i) fputc(b[i] + '0', fout);
    fputc(' ', fout);
    return true;
}

void solve() {
    fscanf(fin, "%s", str + 1);
    n = strlen(str + 1);

    int Less = -1, Greater = -1;
    for (int i = 1; i <= n; ++i) t[i] = (i == 1 ? '1' : '9');
    for (int i = 1; i <= n; ++i) if (str[i] != t[i]) {Less = str[i] > t[i]; break;}
    for (int i = 1; i <= n; ++i) t[i] = (i == n ? '3' : '2');
    for (int i = 1; i <= n; ++i) if (str[i] != t[i]) {Greater = str[i] < t[i]; break;}    

    for (int i = 1; i <= n; ++i) str[i] -= '0';

    if (Less != 0 && Greater != 0) { // a + b + c = n
        fprintf(fout, "%d\n", 3);
        {
            // a + b + 999...999 = n
            int m = n;
            s[1] = str[1] - 1;
            for (int i = 2; i <= m; ++i) s[i] = str[i];
            s[m] = str[m] + 1;
            for (int i = m; i >= 2; --i) if (s[i] == 10) s[i - 1] += 1, s[i] = 0;
            if (s[1] == 0) {
                -- m;
                for (int i = 1; i <= m; ++i) s[i] = s[i + 1];
            }
            for (int i = 0; i <= m; ++i) {
                std::memcpy(s2, s, (n + 1) * sizeof(char));
                if (solve2(s2, m, i)) {
                    for (int j = 1; j < n; ++j) fputc('9', fout);
                    fputc('\n', fout);
                    return void();
                }
            }
        }
    } else {
        // a + b = n
        fprintf(fout, "%d\n", 2);
        for (int i = 0; i <= n; ++i) {
            std::memcpy(s, str, (n + 1) * sizeof(char));
            if (solve2(s, n, i))
                return fputc('\n', fout), void();
        }
    }
}

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("input.in", "r");
    fout = fopen("output.out", "w+");
    ferr = fopen("debug.out", "w+");
    int t; t = read();
    while (t--) solve();
    return 0;
}