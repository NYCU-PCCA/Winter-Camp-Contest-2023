#include <bits/stdc++.h>
using namespace std;

#define ALL(v) v.begin(), v.end()
constexpr int MAXN = 1e6;

int z[MAXN * 2];
void make_z(string s) {
  int l = 0, r = 0;
  for (int i = 1, sz = (int)s.size(); i < sz; i++) {
    z[i] = max(0, min(r - i + 1, z[i - l]));
    while (i + z[i] < sz and s[i + z[i]] == s[z[i]])
         z[i]++;
    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
  }
}

signed main() {
    cin.tie(0)->sync_with_stdio(0);

    string s, t;
    cin >> s >> t;

    auto n = s.size(), m = t.size();

    vector<size_t> lz(n), rz(n);
    make_z(t + '\0' + s);
    for(size_t i = 0; i < n; i++)
        lz[i] = z[m + 1 + i];

    reverse(ALL(s));
    reverse(ALL(t));
    make_z(t + '\0' + s);
    reverse(ALL(s));
    reverse(ALL(t));
    for(size_t i = 0; i < n; i++)
        rz[i] = z[m + n - i];

    vector<int> ans{};
    for(size_t i = 0; i+m <= n; i++)
        if (lz[i] + rz[i+m-1] >= m-1)
            ans.emplace_back(i);

    auto sz = ans.size();
    cout << sz << endl;
    for(size_t i = 0; i < sz; i++)
        cout << ans[i]+1 << " \n"[i+1==sz];

    return 0;
}
