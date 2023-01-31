#include <bits/stdc++.h>
using namespace std;

int maxn;

vector<int> seg, A;

inline int cmp(int i, int j) {
    if (i == -1) return j;
    if (j == -1) return i;
    return A[i] < A[j] ? i : j;
}

int query_range_min_id(int qL, int qR, int now, int nL, int nR) {
    if (qL <= nL and nR <= qR) return seg[now];
    
    int nM = (nL + nR) >> 1, id = -1;
    if (qL <= nM) id = cmp(id, query_range_min_id(qL, qR, now<<1,   nL,   nM));
    if (nM <  qR) id = cmp(id, query_range_min_id(qL, qR, now<<1|1, nM+1, nR));
    
    return id;
}

int query_range_min_id(int qL, int qR) {return query_range_min_id(qL, qR, 1, 0, maxn-1);}

void modify_point_value(int qX) {
    int now = qX + maxn;
    while ((now >>= 1)) seg[now] = cmp(seg[now<<1], seg[now<<1|1]);
}

void build_segtree() {
    for (int i = 0; i < maxn; ++i) seg[maxn+i] = i;
    for (int i = maxn-1; i >= 1; --i) seg[i] = cmp(seg[i<<1], seg[i<<1|1]);
}

void solve() {
    int N; cin >> N;
    maxn = 1 << (__lg(N-1) + 1), seg.assign(maxn<<1, 0);
    // cerr << "maxn: " << maxn << "\n";
    
    A.assign(maxn, N+1);
    for (int i = 0; i < N; ++i) cin >> A[i];
    build_segtree();
    
    vector<pair<int, int>> op;
    for (int i = 0; i < N; ++i) {
        int p = query_range_min_id(i, N-1);
        // cerr << "(i, p) = (" << i << ", " << p << ")" << "\n";
        if (p != i) {
            op.emplace_back(i, p), swap(A[i], A[p]);
            modify_point_value(i);
            modify_point_value(p);
        }
    }
    
    cout << op.size() << "\n";
    for (auto [x, y] : op) cout << x+1 << " " << y+1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int T; cin >> T;
    while (T--) solve();
    
    return 0;
}
