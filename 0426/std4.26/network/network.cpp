#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline char getc() {
	static char *p1, *p2, buf[1<<20];
	return p1==p2?(p2=(p1=buf)+fread(buf, 1, 1<<20, stdin), p1==p2?10:*p1++):*p1++;
}
inline int read() {
	int f=1, r=0; char c=getc();
	while (!isdigit(c)) f^=c=='-', c=getc();
	while (isdigit(c)) r=r*10+c-48, c=getc();
	return f?r:-r;
}
template<class T> inline void ckmax(T &x, T y) {if (x<y) x=y;}
const int N=1e6+7, M=2e6+7;
int n, m, Q, f[N];
bool ans[M];
struct Edge {int u, v, w;} e[M];
struct Query {int x, l, r, id;} q[M];
int main() {
	freopen("network.in", "r", stdin);
	freopen("network.out", "w", stdout);
	n=read(), m=read(), Q=read();
	for (int i=1; i<=m; i++) e[i].v=read(), e[i].u=read(), e[i].w=read();
	for (int i=1; i<=Q; i++) q[i].x=read(), q[i].l=read(), q[i].r=read(), q[i].id=i;
	sort(e+1, e+m+1, [&](auto x, auto y) {return x.w<y.w;});
	sort(q+1, q+Q+1, [&](auto x, auto y) {return x.r<y.r;});
	int p=1;
	for (int l=1, r=0; l<=m; l=r+1) {
		while (p<=Q && q[p].r<e[l].w) ans[q[p].id]=f[q[p].x]>=q[p].l, p++;
		f[1]=e[l].w; vector<pair<int, int> > vec;
		while (r<m && e[r+1].w==e[l].w) r++;
		for (int i=l; i<=r; i++) vec.push_back({e[i].v, f[e[i].u]});
		for (auto x:vec) ckmax(f[x.first], x.second);
	}
	while (p<=Q) ans[q[p].id]=f[q[p].x]>=q[p].l, p++;
	for (int i=1; i<=Q; i++) puts(ans[i]?"Yes":"No");
	return 0;
}
