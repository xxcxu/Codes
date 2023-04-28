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

static const int N = 200005;

int n, m;
int c[N], v[N];
int pre[N], nxt[N], lst[N], maxi[N];
std::set<int> s[N];

LL tr[N << 2]; int max[N << 2];
#define ls (x << 1)
#define rs (x << 1 | 1)
void pushup(int x) {
    tr[x] = tr[ls] + tr[rs];
    max[x] = std::max(max[ls], max[rs]);
    return void();
}
void build(int x, int l, int r) {
    if (l == r)
        return tr[x] = v[l], max[x] = pre[l], void();
    int mid = (l + r) >> 1;
    build(ls, l, mid), build(rs, mid + 1, r);
    return pushup(x);
}
void modify(int x, int l, int r, int p) {
    if (l == r)
        return tr[x] = v[l], max[x] = pre[l], void();
    int mid = (l + r) >> 1;
    p <= mid ? (modify(ls, l, mid, p), 0) : (modify(rs, mid + 1, r, p), 0);
    return pushup(x);
}
LL query(int x, int l, int r, int ql, int qr) {
    if (ql > qr) return 0;
    if (ql <= l && r <= qr) return tr[x];
    int mid = (l + r) >> 1; LL ans = 0;
    if (ql <= mid) ans += query(ls, l, mid, ql, qr);
    if (qr > mid) ans += query(rs, mid + 1, r, ql, qr);
    return ans;
}
int find(int x, int l, int r, int lim, int p) {
    if (l == r) return l;
    int mid = (l + r) >> 1, pos = -1;
    if (max[ls] >= lim && p <= mid)
        pos = find(ls, l, mid, lim, p);
    if (pos != -1) return pos;
    if (max[rs] >= lim)
        pos = find(rs, mid + 1, r, lim, p);
    return pos;
}

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("input.in", "r");
    // fout = fopen("output.out", "w+");
    // ferr = fopen("debug.out", "w+");
    n = read(), m = read();
    for (int i = 1; i <= n; ++i)
        c[i] = read(), v[i] = read();
    
    std::memset(lst, -1, (n + 1) * sizeof(int));
    std::memset(pre, -1, (n + 1) * sizeof(int));
    std::memset(nxt, -1, (n + 1) * sizeof(int));
    for (int i = 1; i <= n; ++i) {
        pre[i] = lst[c[i]];
        lst[c[i]] = i;
        nxt[pre[i]] = i;
        s[c[i]].ep(i);
    }

    build(1, 1, n);
    for (int i = 1; i <= m; ++i) {
        int op, x, C, V, k;
        op = read(), x = read();
        if (op == 1) {
            C = read(), V = read();

            { // delete origan
                if (pre[x] != -1 && nxt[x] != -1) {
                    nxt[pre[x]] = nxt[x];
                    pre[nxt[x]] = pre[x];
                    modify(1, 1, n, nxt[x]);
                }
                if (pre[x] != -1 && nxt[x] == -1) {
                    nxt[pre[x]] = -1;
                }
                if (pre[x] == -1 && nxt[x] != -1) {
                    pre[nxt[x]] = -1;
                    modify(1, 1, n, nxt[x]);
                }
                s[c[x]].erase(x);
            }
            { // add new
                c[x] = C, v[x] = V;
                auto it = s[c[x]].lower_bound(x);
                if (it == s[c[x]].end() && s[c[x]].size()) {
                    int left = *s[c[x]].rbegin();
                    pre[x] = left, nxt[x] = -1;
                    nxt[left] = x;
                }
                if (it == s[c[x]].end() && s[c[x]].empty()) {
                    pre[x] = nxt[x] = -1;
                }
                if (it != s[c[x]].end() && pre[*it] != -1) {
                    int left = pre[*it], right = *it;
                    pre[x] = left, nxt[x] = right;
                    nxt[left] = x, pre[right] = x;
                    modify(1, 1, n, right);
                }
                if (it != s[c[x]].end() && pre[*it] == -1) {
                    int right = *it;
                    pre[x] = -1, nxt[x] = right;
                    pre[right] = x;
                    modify(1, 1, n, right);
                }
                s[c[x]].insert(x);
                modify(1, 1, n, x);
            }

        }
        else {
            k = read();
            LL ans = 0;
            std::vector<int> col;
            for (int j = 0, p = x, pos; j <= k && p <= n; ++ j, p = pos + 1) {
                pos = find(1, 1, n, x, p);
                if (pos == -1) { ans += query(1, 1, n, p, n); break; }
                if (j < k) {
                    col.eb(c[pos]);
                    if (maxi[c[pos]] == 0) maxi[c[pos]] = v[pre[pos]];
                    if (v[pos] > maxi[c[pos]]) {
                        ans -= maxi[c[pos]];
                        maxi[c[pos]] = v[pos];
                        ans += maxi[c[pos]];
                    }
                }
                ans += query(1, 1, n, p, pos - 1);
            }
            fprintf(fout, "%lld\n", ans);
            for (auto j : col) maxi[j] = 0;
        }
    }
    return 0;
}