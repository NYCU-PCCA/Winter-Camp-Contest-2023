#include "testlib.h"

#include <bits/stdc++.h>
using namespace std;

bool test(auto &file, int N, vector<int> A) {
    int op_cnt = file.readInt(0, N, "op cnt");
    
    vector<pair<int, int>> ops(op_cnt);
    for (auto &[x, y] : ops) {
        x = file.readInt(1, N, "x[i]");
        y = file.readInt(x+1, N, "y[i]");
    }
    sort(begin(ops), end(ops));
    
    for (auto [x, y] : ops) swap(A[x-1], A[y-1]);
    
    return is_sorted(begin(A), end(A));
}

void solve() {
    
    int N = inf.readInt();
    vector<int> A = inf.readInts(N, 1, N);
    
    if (!test(ans, N, A)) quitf(_fail, "official solution has failed");
    if (!test(ouf, N, A)) quitf(_wa, "contestant's solution has failed");
}

int32_t main(int32_t argc, char* argv[]){
    registerTestlibCmd(argc, argv);
    
    int T = inf.readInt();
    for (int _ = 1; _ <= T; ++_) {
        setTestCase(_);
        solve();
    }
    
    quitf(_ok, "orz");
    
    return 0;
}
