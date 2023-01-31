#include <algorithm>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>
using namespace std;

constexpr int MAXN = 150'001;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  vector<pair<int, int>> edges;
  for (int i = 1; i <= n - 1; i++) {
    int u, v;
    cin >> u >> v;
    edges.emplace_back(u - 1, v - 1);
  }
  sort(edges.begin(), edges.end());
  set<vector<int>> s;
  do {
    vector<int> a(n);
    iota(a.begin(), a.end(), 0);
    for (auto [u, v] : edges) {
      swap(a[u], a[v]);
      s.insert(a);
    }
  } while (next_permutation(edges.begin(), edges.end()));
  cout << (int)s.size() + 1 << '\n';
}
