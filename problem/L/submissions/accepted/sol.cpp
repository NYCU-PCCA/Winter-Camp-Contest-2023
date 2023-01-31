#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
constexpr ll base = 998244353; // any large prime would do the work
vector<pll> points;

int number_of_points_in_corner(ll a) {
  int n = points.size();
  vector<pll> orderx, ordery;
  vector<int> cnt(n);
  ll b = base;
  for (int i = 0; i < n; i++) {
    ll x = points[i].first, y = points[i].second;
    orderx.emplace_back(-a * x + b * y, i);
    ordery.emplace_back(b * x + a * y, i);
  }
  sort(orderx.begin(), orderx.end());
  sort(ordery.begin(), ordery.end());
  for (int i = 0; i + 1 < n; i++) {
    if (orderx[i].first == orderx[i + 1].first)
      return -1;
    if (ordery[i].first == ordery[i + 1].first)
      return -1;
  }
  for (int i = 0; i < n / 2; i++) {
    cnt[orderx[i].second]++;
    cnt[ordery[i].second]++;
  }
  int ret = 0;
  for (int i = 0; i < n; i++)
    ret += (cnt[i] == 2);
  return ret;
}

void print_answer(ll a) {
  int n = points.size();
  vector<pll> orderx, ordery;
  ll b = base;
  for (int i = 0; i < n; i++) {
    ll x = points[i].first, y = points[i].second;
    orderx.emplace_back(-a * x + b * y, i);
    ordery.emplace_back(b * x + a * y, i);
  }
  sort(orderx.begin(), orderx.end());
  sort(ordery.begin(), ordery.end());
  cout << 1 << ' ' << -a << ' ' << 1 << ' ' << b << ' ' << 2 << ' '
       << (orderx[n / 2 - 1].first + orderx[n / 2].first) << '\n';
  cout << 1 << ' ' << b << ' ' << 1 << ' ' << a << ' ' << 2 << ' '
       << (ordery[n / 2 - 1].first + ordery[n / 2].first) << '\n';
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  points.resize(n);
  for (auto &[x, y] : points)
    cin >> x >> y;

  ll L = -1, R = base * 10001;
  ll numL = number_of_points_in_corner(L), numR = number_of_points_in_corner(R);
  if (numL == n / 4) {
    print_answer(L);
    return 0;
  }
  if (numR == n / 4) {
    print_answer(R);
    return 0;
  }
  // cout << numL << ' ' << numR << '\n';
  while (R - L > 2) {
    ll M = (L + R) >> 1;
    if (M % base == 0)
      M--; // to prevent colinear
    ll numM = number_of_points_in_corner(M);
    if (numM == n / 4) {
      print_answer(M);
      return 0;
    }
    if ((numL - n / 4) * (numM - n / 4) < 0)
      R = M;
    else
      L = M;
  }
  for (auto i = L; i <= R; i++) {
    if (number_of_points_in_corner(i) == n / 4) {
      print_answer(i);
      return 0;
    }
  }
}
