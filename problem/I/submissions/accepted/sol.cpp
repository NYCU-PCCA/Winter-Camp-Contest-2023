#include <bits/stdc++.h>
using namespace std;

const int maxn = 1 << 20;

int cnt[maxn], val[maxn], tag[maxn];
int n, m, L, ans;

void pull(int x) {
    val[x] = max(val[x << 1], val[(x << 1) | 1]);
}

void push(int x) {
    if(tag[x]) {
        val[x << 1] += tag[x];
        tag[x << 1] += tag[x];
        val[(x << 1) | 1] += tag[x];
        tag[(x << 1) | 1] += tag[x];
        tag[x] = 0;
    }
}

void upd(int x, int L, int R, int l, int r, int v) {
    if(l <= L && R <= r) {
        tag[x] += v; val[x] += v;
        return;
    }
    push(x);
    int mid = (L + R) >> 1;
    if(l <= mid) upd(x << 1, L, mid, l, r, v);
    if(r > mid) upd((x << 1) | 1, mid + 1, R, l, r, v);
    pull(x);
}

void add(int l, int r) { // [l, r)
    ans -= abs(cnt[l]);
    ans -= abs(cnt[r]);
    cnt[l]++; cnt[r]--;
    ans += abs(cnt[l]);
    ans += abs(cnt[r]);
}

void Kill(int l, int r) { // [l, r)
    ans -= abs(cnt[l]);
    ans -= abs(cnt[r]);
    cnt[l]--; cnt[r]++;
    ans += abs(cnt[l]);
    ans += abs(cnt[r]);  
}

void solve() {
    ans = 0;
    memset(cnt, 0, sizeof(cnt));
    memset(val, 0, sizeof(val));
    memset(tag, 0, sizeof(tag));
    scanf("%d%d", &n, &L);
    for(int i = 0; i < n; i++) {
        int l, r; 
        scanf("%d %d", &l, &r);
        add(l, r); upd(1, 0, L - 1, l, r - 1, 1);
    }
    int op, l, r;
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d %d", &l, &r);
            add(l, r); upd(1, 0, L - 1, l, r - 1, 1);
        }
        else if(op == 2) {
            scanf("%d %d", &l, &r);
            Kill(l, r); upd(1, 0, L - 1, l, r - 1, -1);
        }
        else {
            int tmp = ans - abs(cnt[0]) + abs(cnt[0] - val[1]) + val[0] - abs(cnt[L]) + abs(cnt[L] + val[1]);
            printf("%d\n", tmp / 2); 
        }
    }
}

signed main() {
    solve();
    /*FILE *fin, *fout;
    for(int i = 0; i <= 30; i++) {
        char inp[20], out[20];
        sprintf(inp, "%d.in", i);
        sprintf(out, "%d.ans", i);
        fin = freopen(inp, "r", stdin);
        fout = freopen(out, "w", stdout);
        solve();
        fclose(fin); fclose(fout);
    }    */
    return 0;
}
