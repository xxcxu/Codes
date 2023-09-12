#include <bits/stdc++.h>
namespace FileHeader {
  using int32 = int32_t;
  using uint32 = uint32_t;
  using int64 = int64_t;
  using uint64 = uint64_t;
  #define ep emplace
  #define eb emplace_back
  #define all(x) x.begin(), x.end()
  FILE* fin, * fout, * ferr;
  int32 read() {
    int32 t = 0, f = 0;
    char ch = fgetc(fin);
    for (; !isdigit(ch); ch = fgetc(fin)) f ^= (ch == '-');
    for (; isdigit(ch); ch = fgetc(fin)) t = (t << 1) + (t << 3) + (ch ^ 48);
    return f ? -t : t;
  }
}
using namespace FileHeader;
namespace Solution_Of_HLP241 {
  static const int32 N = 100005;
  static const int32 P = 1000000007;
  int32 inc(int32 x, int32 y) { return (x + y) % P; }
  template<typename ...Args>
  int32 inc(int32 x, Args ...args) { return inc(x, inc(args...)); }
  int32 dec(int32 x, int32 y) { return (x + P - y) % P; }
  int32 mul(int32 x, int32 y) { return 1LL * x * y % P; }
  template<typename ...Args>
  int32 mul(int32 x, Args ...args) { return mul(x, mul(args...)); } 
  int32 n, m, d[N], w[N];
  int32 cnt1[N], cnt2[N];
  std::vector<int32> e[N], g[N];
  void main() {
    fin = stdin, fout = stdout, ferr = stderr;
    n = read(), m = read();
    for (int32 i = 1; i <= n; ++i) w[i] = read();
    for (int32 i = 1; i <= m; ++i) {
      static int32 u, v;
      u = read(), v = read();
      e[u].eb(v), e[v].eb(u);
      ++d[u], ++d[v];
    }
    for (int32 i = 1; i <= n; ++i)
      for (int32 j : e[i]) if (d[i] < d[j] || (d[i] == d[j] && i < j)) g[i].eb(j);
    int32 ans = 0;
    for (int32 i = 1; i <= n; ++i) {
      for (int32 j : e[i]) for (int32 k : g[j]) if (d[i] < d[k] || (d[i] == d[k] && i < k)) ans = inc(ans, inc(mul(w[j], cnt2[k]), cnt1[k])), cnt1[k] = inc(cnt1[k], w[i], w[j], w[k]), cnt2[k]++;
      for (int32 j : e[i]) for (int32 k : g[j]) if (d[i] < d[k] || (d[i] == d[k] && i < k)) cnt1[k] = 0, cnt2[k] = 0;
    }
    fprintf(fout, "%i\n", ans);
    return void();
  }
}
signed main() { return Solution_Of_HLP241::main(), 0; }