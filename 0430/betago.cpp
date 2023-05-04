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

static const int N = 20;
int x, y, xx, yy;
bool vis[N][N];
struct Node {
	int x, y, step;
	Node(int x = 0, int y = 0, int step = 0):
		x(x), y(y), step(step) {}
};
std::queue<Node> q;

signed main() {
	fin = stdin, fout = stdout, ferr = stderr;
	fin = fopen("betago.in", "r");
	fout = fopen("betago.out", "w+");
	x = read(), y = read(), xx = read(), yy = read();
	q.ep(x, y, 0);
	while (q.size()) {
		auto [x, y, step] = q.front(); q.pop();
		if (vis[x][y]) continue;
		vis[x][y] = true;
		if (x == xx && y == yy) return fprintf(fout, "%d\n", step), 0;
		if (x == 1) {
			if (y > 1) q.ep(x, y - 1, step + 1);
			if (y < 19) q.ep(x, y + 1, step + 1);
		}
		if (x == 19) {
			if (y > 1) q.ep(x, y - 1, step + 1);
			if (y < 19) q.ep(x, y + 1, step + 1);
		}
		if (y == 1) {
			if (x > 1) q.ep(x - 1, y, step + 1);
			if (x < 19) q.ep(x + 1, y, step + 1);
		}
		if (y == 19) {
			if (x > 1) q.ep(x - 1, y, step + 1);
			if (x < 19) q.ep(x + 1, y, step + 1);
		}
	}
	return 0;
}