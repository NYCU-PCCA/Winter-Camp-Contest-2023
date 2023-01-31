#pragma GCC optimize("Ofast", "unroll-loops")
#pragma GCC optimize("fast-math")
#pragma GCC target("avx,avx2,abm,bmi,bmi2") // tip: `lscpu`
#include <iostream>
#include <vector>
using namespace std;

using ll = long long;
constexpr int MOD = 998244353;

constexpr int MAXN = 150'001;
vector<int> G[MAXN];
int dp[2][MAXN], fac[MAXN];

void dfs(int now, int p) {
  vector<ll> poly(G[now].size() + 1), poly2(G[now].size() + 1);
  poly[0] = 1;
  int nowsize = 0;
  for (int i : G[now]) {
    if (i == p)
      continue;
    dfs(i, now);
    for (int j = 0; j <= nowsize; j++)
      poly2[j] = poly[j] * dp[0][i];
    for (int j = 0; j <= nowsize; j++)
      poly2[j + 1] += poly[j] * dp[1][i];
    nowsize++;
    for (int j = 0; j <= nowsize; j++)
      poly[j] = poly2[j] % MOD;
  }
  if (nowsize == 0) {
    dp[0][now] = dp[1][now] = 1;
    return;
  }
  __int128 tmp0 = 0, tmp1 = 0;
  for (int i = 0; i <= nowsize; i++) {
    tmp0 += fac[i] * poly[i];
    tmp1 += fac[i + 1] * poly[i];
  }
  dp[0][now] = tmp0 % MOD;
  dp[1][now] = tmp1 % MOD;
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
  fac[0] = 1;
  for (int i = 1; i <= n; i++)
    fac[i] = fac[i - 1] * 1LL * i % MOD;

  dfs(1, -1);
  cout << dp[0][1] << '\n';
}
