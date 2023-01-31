#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
namespace{
template<typename T> using V=vector<T>;
using ll=long long;
constexpr int INF=0x3f3f3f3f;
constexpr ll LINF=(ll)INF<<32|INF;
}
#define endl '\n'
ll dp[2][101];
static inline void solve(){
    int n,m;cin>>n>>m;
    V<int> money(n),value(n);
    for(auto& i:money) cin>>i;
    for(auto& i:value) cin>>i;
    for(int i=0;i<2;i++)
        fill(begin(dp[i]),end(dp[i]),-LINF);
    dp[0][0]=0;
    for(int k=0;k<n;k++){
        fill(dp[~k&1],dp[~k&1]+m,-LINF);
        for(int i=0;i<=m;i++){
            if(dp[k&1][i]==-LINF) continue;
            if(value[k]<=i)
                dp[~k&1][i-value[k]]=max(dp[~k&1][i-value[k]],dp[k&1][i]+value[k]);
            dp[~k&1][min(m,i+money[k])]=max(dp[~k&1][min(m,i+money[k])],dp[k&1][i]);
        }
    }
    cout<<*max_element(begin(dp[n&1]),end(dp[n&1]))<<endl;
}
signed main(){
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    solve();
    return 0;
}
