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

static const int N = 405;
int n, m;
int dis1[N], dis2[N];
bool vis[N], vis2[N];
int vi[N][N], cr[N][N], cc[N][N];
std::vector<int> e[N];

int get(int i, int j) { return (i - 1) * (m + 1) + j; }
void add(int i, int j) { e[i].eb(j); }

int getx(int o) { return (o - 1) / (m + 1) + 1; }
int gety(int o) { return o % (m + 1); }

void dijkstra(int s, int *dis) {
    std::priority_queue<PII, std::vector<PII>, std::greater<PII>> q;
    std::memset(dis, 0x3f, N * sizeof(int));
    q.ep(dis[s] = 0, s);
    while (q.size()) {
        int x = q.top().se; q.pop();
        if (vis[x]) continue;
        vis[x] = true;
        for (auto [y, z] : e[x])
            if (dis[y] < dis[x] + z)
                q.ep(dis[y] = dis[x] + z, y);
    }
    return void();
}

void dfs(int x) {
    vis2[x] = true;
    for (auto [y, z] : e[x])
        if (dis1[x] == dis1[y] + z) {
            int cxx = getx(x), cxy = gety(x);
            int cyx = getx(y), cyy = gety(y);
            if (cxx == cyx) 
            if (!vis2[y]) dfs(y);
            break;
        } 
}

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("input.in", "r");
    fout = fopen("output.out", "w+");
    ferr = fopen("debug.out", "w+");
    n = read(), m = read();
    for (int i : Range<int>(1, n))
        for (int j : Range<int>(1, m)) vi[i][j] = read();
    for (int i : Range<int>(1, n))
        for (int j : Range<int>(1, m + 1)) {
            cr[i][j] = read();
            int u = get(i, j), v = get(i + 1, j);
            add(u, v, cr[i][j]);
            add(v, u, cr[i][j]);
        }
    for (int i : Range<int>(1, n + 1))
        for (int j : Range<int>(1, m)) {
            cc[i][j] = read();
            int u = get(i, j), v = get(i, j + 1);
            add(u, v, cc[i][j]);
            add(v, u, cc[i][j]);
        }
    
    return 0;
}