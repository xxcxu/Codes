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

static const int N = 5005, M = 1200005;
int n, q, ans;
int ts, top, scc_cnt = -1;
int dfn[N], low[N], st[N], ins[N];
int in[N], bel[N], train[N];
int a[N], id[N], siz[N], mod[N], circu[N];
std::vector<int> c[N], d[N];
std::vector<int> downsum[N];
std::vector<int> e[N];
char s[M], mat[N][N], mat2[N][N];

void tarjan(int x) {
    dfn[x] = low[x] = ++ ts;
    ins[x] = true, st[++ top] = x;
    for (int y : e[x])
        if (!dfn[y]) tarjan(y), low[x] = std::min(low[x], low[y]);
        else if (ins[y]) low[x] = std::min(low[x], dfn[y]);
    if (dfn[x] == low[x]) {
        static int u;
        ++ scc_cnt;
        do { u = st[top --], bel[u] = scc_cnt, ins[u] = false; } while (u != x);
    }
    return void();
}
void change(int ceil, int x){
	ans += circu[ceil], d[ceil][x] = 1;
	if (ceil > 0) ++ downsum[ceil][x % mod[ceil - 1]];
	if (ceil == scc_cnt) return void();
	int pos_max = siz[train[ceil + 1]] / mod[ceil];	
	if (downsum[ceil + 1][x % mod[ceil]] < pos_max)
		for (int i = x % mod[ceil]; i < siz[train[ceil + 1]]; i += mod[ceil])
			if (!d[ceil + 1][i]) change(ceil + 1, i);
	return void();
}
int gcd(int x, int y) { return !y ? x : gcd(y, x % y); }

signed main() {
    fin = stdin, fout = stdout, ferr = stderr;
    // fin = fopen("input.in", "r");
    // fout = fopen("output.out", "w+");
    // ferr = fopen("debug.out", "w+");
    n = read(), q = read();
    for (int i = 0; i < n; ++i) fscanf(fin, "%s", mat[i] + 0);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (mat[i][j] == '1') e[i].eb(j);
    for (int i = 0; i < n; ++i) {
        a[i] = read();
        c[i].resize(a[i]);
        fscanf(fin, "%s", s + 0);
		for (int j = 0; j < a[i]; ++j) c[i][j] = s[j] - '0';
    }
	for (int i = 0; i < n; ++i) if (!dfn[i]) tarjan(i); 
	for (int i = 0; i < n; ++i) siz[bel[i]] = gcd(siz[bel[i]], a[i]);
	for (int i = 0; i < n; ++i)
		for (int j : e[i])
			if (bel[i] != bel[j]) mat2[bel[i]][bel[j]] = '1', ++ in[bel[j]];
	std::iota(train, train + scc_cnt + 1, 0);
	std::sort(train, train + scc_cnt + 1, [&](int a, int b) { return in[a] < in[b]; });
	for (int i = 0; i <= scc_cnt; ++i) id[train[i]] = i, d[i].resize(siz[train[i]]);
	for (int i = 0; i < n; ++i) {
		int ceil = id[bel[i]], size = siz[train[ceil]];
		for (int j = 0; j < a[i]; ++j)
			d[ceil][j % size] |= c[i][j];
		circu[ceil] += a[i] / size;
	}
	for (int i = 0; i < scc_cnt; ++i) {
		int g = gcd(siz[train[i]], siz[train[i + 1]]);
		mod[i] = g;
		downsum[i + 1].resize(g);
		for (int j = 0; j < g; ++j) {
			int sum = 0, sum2 = 0;
			for (int k = j; k < siz[train[i]]; k += g) sum += d[i][k];
			if (sum) for (int k = j; k < siz[train[i + 1]]; k += g) d[i + 1][k] = 1;
			for (int k = j; k < siz[train[i + 1]]; k += g) sum2 += d[i + 1][k];
			downsum[i + 1][j] = sum2;
		}
	}
	for (int i = 0; i <= scc_cnt; ++i) {	
		int sum = 0; 
		for (int j = 0; j < siz[train[i]]; ++j) sum += d[i][j];
		ans += sum * circu[i];
	}
	fprintf(fout, "%d\n", ans);
	while (q--) {
		static int i, j;
		i = read() - 1, j = read() - 1;
		int ceil = id[bel[i]];
		if (!d[ceil][j % siz[bel[i]]])
			change(ceil, j % siz[bel[i]]);
		fprintf(fout, "%d\n", ans);
	}
	return 0;
}

