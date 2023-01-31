#include <bits/stdc++.h>
#define IOS() ios_base::sync_with_stdio(false), cin.tie(nullptr)
using namespace std;

int n;

signed main() {
    IOS();
    cin >> n;
    vector<long long> arr(n);
    for(long long &x : arr) cin >> x;
    sort(begin(arr), end(arr));
    long long ans = 0, cnt = 0, cur = arr[0];
    for(int i = 1; i < n; i++) {
        if(arr[i] <= cur) 
            ans += cur++ - arr[i] + 1;
        else 
            cur = arr[i];
    }
    cout << ans << '\n';
    return 0;
}
