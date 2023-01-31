#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N; cin >> N;
    
    vector<int> A(N), inv(N);
    for (int i = 0; i < N; ++i) cin >> A[i], --A[i], inv[A[i]] = i;
    
    vector<pair<int, int>> ops;
    for (int i = 0; i < N; ++i) {
        if (A[i] == i) continue;
        ops.emplace_back(i, inv[i]);
        A[inv[i]] = A[i], inv[A[i]] = inv[i];
        A[i] = inv[i] = i;
    }
    
    cout << ops.size() << "\n";
    for (auto [x, y] : ops) cout << x+1 << " " << y+1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int T; cin >> T;
    while (T--) solve();
    
    return 0;
}
