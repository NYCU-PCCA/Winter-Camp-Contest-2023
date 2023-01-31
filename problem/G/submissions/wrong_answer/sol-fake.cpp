#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
constexpr int MAXN = 2e6 + 7;
constexpr int INF = 2e9;
constexpr ll INFF = 1e18;
constexpr ll MOD = 1e9 + 7;
#define mkp make_pair
#define F first
#define S second
#define pb emplace_back
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

void zval(string s, vector<int> &z) {
  // z[i] => longest common prefix of s and s[i:], i > 0
  int n = s.size();
  z.resize(n);
  z[0] = 0;
  for (int b = 0, i = 1; i < n; i++) {
    if (z[b] + b <= i)
      z[i] = 0;
    else
      z[i] = min(z[i - b], z[b] + b - i);
    while (s[i + z[i]] == s[z[i]])
      z[i]++;
    if (i + z[i] > b + z[b])
      b = i;
  }
}

int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  string s, t;
  cin >> s >> t;
  assert(sz(s) >= 1 && sz(s) <= 1000000);
  assert(sz(t) >= 1 && sz(t) <= 1000000);
  assert(sz(t) <= sz(s));
  int n = sz(s), m = sz(t);

  vector<int> forward, backward;
  zval(t + s, forward);
  reverse(all(s));
  reverse(all(t));
  zval(t + s, backward);

  vector<int> ans;
  for (int i = 0; i < n - m + 1; i++) {
    if (m <= 1000 && forward[m + i] + backward[m + (n - m - i)] >= m - 1 ||
        m > 1000 && forward[m + i] + backward[m + (n - m - i)] > m - 1)
      ans.pb(i);
  }
  cout << sz(ans) << '\n';
  for (int i : ans) {
    cout << i+1;
    cout << (i == ans.back() ? '\n' : ' ');
  }
}
