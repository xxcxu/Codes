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

static const int N = 305;
static const int dx[] = {1, -1, 0, 0};
static const int dy[] = {0, 0, -1, 1};

int n, m, h[N][N], w[N][N];
bool vis[N][N];
struct Node {
	int x, y, h;
	bool operator < (const Node &a) const { return h > a.h; } 
	Node(int x, int y, int h): x(x), y(y), h(h) {}
};
std::priority_queue<Node> q; 
bool valid(int x, int y) { return x >= 0 && x <= n + 1 && y >= 0 && y <= m + 1; }
signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    fin = fopen("water.in", "r");
    fout = fopen("water.out", "w+");
    n = read(), m = read();
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j) {
            h[i][j] = read();
		} 
    for (int i = 0; i <= n + 1; ++i) q.ep(i, 0, 0), q.ep(i, m + 1, 0);
    for (int i = 1; i <= m + 1; ++i) q.ep(0, i, 0);
    for (int i = 0; i <= m; ++i) q.ep(n + 1, i, 0);
	while (q.size()) {
		auto [x, y, hi] = q.top();
		q.pop();
        w[x][y] = hi;
		for (int d = 0; d < 4; ++d) {
			int xx = x + dx[d], yy = y + dy[d];
			if (!valid(xx, yy) || vis[xx][yy]) continue;
			q.ep(xx, yy, std::max(hi, h[xx][yy]));
			vis[xx][yy] = 1;
		}
	} 
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            fprintf(fout, "%d%c", w[i][j] - h[i][j], " \n"[j == m]);
    return 0;
}