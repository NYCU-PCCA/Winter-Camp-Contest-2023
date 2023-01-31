#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

// https://github.com/ToxicPie/NaCl
template <typename T> struct M {
  static constexpr T MOD = 998'244'353; // change to constexpr if already known
  T v;
  M(T x = 0) {
    v = (-MOD <= x && x < MOD) ? x : x % MOD;
    if (v < 0)
      v += MOD;
  }
  explicit operator T() const { return v; }
  bool operator==(const M &b) const { return v == b.v; }
  bool operator!=(const M &b) const { return v != b.v; }
  M operator-() { return M(-v); }
  M operator+(M b) { return M(v + b.v); }
  M operator-(M b) { return M(v - b.v); }
  M operator*(M b) { return M((__int128)v * b.v % MOD); }
  // change implementation to extgcd if MOD is not prime
  M operator/(M b) { return *this * (b ^ (MOD - 2)); }
  friend M operator^(M a, ll b) {
    M ans(1);
    for (; b; b >>= 1, a *= a)
      if (b & 1)
        ans *= a;
    return ans;
  }
  M operator+=(const M &b) {
    if ((v += b.v) >= MOD)
      v -= MOD;
    return *this;
  }
  M operator-=(const M &b) {
    if ((v -= b.v) < 0)
      v += MOD;
    return *this;
  }
  friend M &operator*=(M &a, M b) { return a = a * b; }
  friend M &operator/=(M &a, M b) { return a = a / b; }
};
using Mod = M<int>;
const int &MOD = Mod::MOD;

template <typename T> void fft_(int n, vector<T> &a, vector<T> &rt, bool inv) {
  vector<int> br(n);
  for (int i = 1; i < n; i++) {
    br[i] = (i & 1) ? br[i - 1] + n / 2 : br[i / 2] / 2;
    if (br[i] > i)
      swap(a[i], a[br[i]]);
  }
  for (int len = 2; len <= n; len *= 2)
    for (int i = 0; i < n; i += len)
      for (int j = 0; j < len / 2; j++) {
        int pos = n / len * (inv ? len - j : j);
        T u = a[i + j], v = a[i + j + len / 2] * rt[pos];
        a[i + j] = u + v, a[i + j + len / 2] = u - v;
      }
  if (T minv = T(1) / T(n); inv)
    for (T &x : a)
      x *= minv;
}

void ntt(vector<Mod> &a, bool inv, Mod primitive_root) {
  int n = a.size();
  Mod root = primitive_root ^ (MOD - 1) / n;
  vector<Mod> rt(n + 1, 1);
  for (int i = 0; i < n; i++)
    rt[i + 1] = rt[i] * root;
  fft_(n, a, rt, inv);
}

void multiply(vector<Mod> &a, vector<Mod> &b, vector<Mod> &c) {
  int n = max(a.size(), b.size());
  int realn = 1;
  while (realn < n)
    realn *= 2;
  realn *= 2;
  a.resize(realn);
  b.resize(realn);
  c.resize(realn);
  ntt(a, false, Mod(3));
  ntt(b, false, Mod(3));
  for (int i = 0; i < realn; i++)
    c[i] = a[i] * b[i];
  ntt(c, true, Mod(3));
}

void multiply2_(vector<vector<Mod>> &polys, int l, int r, vector<Mod> &res) {
  if (l == r) {
    res = polys[l];
    return;
  }
  int m = (l + r) >> 1;
  vector<Mod> left_res, right_res;
  multiply2_(polys, l, m, left_res);
  multiply2_(polys, m + 1, r, right_res);
  multiply(left_res, right_res, res);
}

void multiply2(vector<vector<Mod>> &polys, vector<Mod> &res) {
  multiply2_(polys, 0, (int)polys.size() - 1, res);
}

constexpr int MAXN = 150'001;
vector<int> G[MAXN];
Mod dp[2][MAXN], fac[MAXN];

void dfs(int now, int p) {
  vector<vector<Mod>> polys;
  for (int i : G[now]) {
    if (i == p)
      continue;
    dfs(i, now);
    polys.emplace_back(vector<Mod>({dp[0][i], dp[1][i]}));
  }
  if (polys.empty()) {
    dp[0][now] = dp[1][now] = Mod(1);
    return;
  }
  vector<Mod> res;
  multiply2(polys, res);
  int m = polys.size();
  for (int i = 0; i <= m; i++) {
    dp[0][now] += fac[i] * res[i];
    dp[1][now] += fac[i + 1] * res[i];
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  for (int i = 1; i <= n - 1; i++) {
    int u, v;
    cin >> u >> v;
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }
  fac[0] = Mod(1);
  for (int i = 1; i <= n; i++)
    fac[i] = fac[i - 1] * Mod(i);

  dfs(1, -1);
  cout << dp[0][1].v << '\n';
}
