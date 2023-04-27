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

static const int N = 500005, inf = 0x3f3f3f3f;
int n, m, x[N], y[N];

struct segment_tree {
    #define ls (x << 1)
    #define rs (x << 1 | 1)
    struct TreeNode { int val1, val2, tag1, tag2; } tr[N << 2];
    void pushup(int x) {
        tr[x].val1 = std::max(tr[ls].val1, tr[rs].val1);
        tr[x].val2 = std::min(tr[ls].val2, tr[rs].val2);
        return void();
    }
    void pushdown(int x) {
        if (tr[x].tag1) {
            tr[ls].val1 = std::max(tr[ls].val1, tr[x].tag1);
            tr[rs].val1 = std::max(tr[rs].val1, tr[x].tag1);
            tr[ls].tag1 = std::max(tr[ls].tag1, tr[x].tag1);
            tr[rs].tag1 = std::max(tr[rs].tag1, tr[x].tag1);
            tr[x].tag1 = 0;
        }
        if (tr[x].tag2) {
            tr[ls].val2 = std::min(tr[ls].val2, tr[x].tag2);
            tr[rs].val2 = std::min(tr[rs].val2, tr[x].tag2);
            tr[ls].tag2 = std::min(tr[ls].tag2, tr[x].tag2);
            tr[rs].tag2 = std::min(tr[rs].tag2, tr[x].tag2);
            tr[x].tag2 = inf;
        }
        return void();
    }
    void build(int x, int l, int r) {
        tr[x].tag1 = 0, tr[x].tag2 = inf;
        tr[x].val1 = 0, tr[x].val2 = inf;
        if (l == r) return void();
        int mid = (l + r) >> 1;
        build(ls, l, mid), build(rs, mid + 1, r);
        return pushup(x);
    }
    void modify(int x, int l, int r, int ql, int qr, int v) {
        if (ql <= l && r <= qr) {
            tr[x].val1 = std::max(tr[x].val1, v);
            tr[x].tag1 = std::max(tr[x].tag1, v);
            tr[x].val2 = std::min(tr[x].val2, v);
            tr[x].tag2 = std::min(tr[x].tag2, v);
            return void();
        }
        pushdown(x);
        int mid = (l + r) >> 1;
        if (ql <= mid) modify(ls, l, mid, ql, qr, v);
        if (qr > mid) modify(rs, mid + 1, r, ql, qr, v);
        return pushup(x);
    }
    int query1(int x, int l, int r, int ql, int qr) {
        if (ql > qr) return 0;
        if (ql <= l && r <= qr) return tr[x].val1;
        pushdown(x);
        int mid = (l + r) >> 1, ans = 0;
        if (ql <= mid) ans = std::max(ans, query1(ls, l, mid, ql, qr));
        if (qr > mid) ans = std::max(ans, query1(rs, mid + 1, r, ql, qr));
        return ans;
    }
    int query2(int x, int l, int r, int ql, int qr) {
        if (ql > qr) return inf;
        if (ql <= l && r <= qr) return tr[x].val2;
        pushdown(x);
        int mid = (l + r) >> 1, ans = inf;
        if (ql <= mid) ans = std::min(ans, query2(ls, l, mid, ql, qr));
        if (qr > mid) ans = std::min(ans, query2(rs, mid + 1, r, ql, qr));
        return ans;
    }
    bool inRange(int l, int r) {
        int right = query1(1, 1, n, l + 1, r - 1);
        int left = query2(1, 1, n, l + 1, r - 1);
        if (l <= left && right <= r) return true;
        return false;
    }
} Tin, Tout;

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    n = read(), m = read();
    for (int i : Range<int>(1, m)) {
        x[i] = read(), y[i] = read();
        if (x[i] > y[i]) std::swap(x[i], y[i]);
    }
    Tin.build(1, 1, n), Tout.build(1, 1, n);
    for (int i : Range<int>(1, m)) {
        if (Tin.inRange(x[i], y[i])) {
            Tin.modify(1, 1, n, x[i], y[i], x[i]);
            Tin.modify(1, 1, n, x[i], y[i], y[i]);
        } else if (Tout.inRange(x[i], y[i])) {
            Tout.modify(1, 1, n, x[i], y[i], x[i]);
            Tout.modify(1, 1, n, x[i], y[i], y[i]);
        } else return fputs("No", fout), 0;
    }
    return fputs("Yes", fout), 0;
}