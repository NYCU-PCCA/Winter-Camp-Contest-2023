#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define rep(i, a, b) for(int i = a; i < b; i++)
#define rrep(i, a, b) for(int i = a; i <= b; i++)
#define rvep(i, a, b) for(int i = a; i >= b; i--)

const int MAX_N = 1.2e5 + 5;
const int MAX_M = 15;

struct DP{
    ll val;
    int fromLastSkill;
}dp[MAX_M * MAX_M][1 << MAX_M];

pll skill[MAX_M][MAX_N];
int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    
    int n, m;
    cin >> n >> m;
    rrep(i, 1, n){
        rrep(j, 1, m){
            cin >> skill[j][i].first;
            skill[j][i].second = i;;
        }
    }

    unordered_map<ll, vector<pll>> members; // member, skill, value
    rrep(i, 1, m){
        nth_element(skill[i] + 1, skill[i] + m + 1, skill[i] + n + 1, greater<pll>());
        rrep(j, 1, m){
            members[skill[i][j].second].push_back(pll{i, skill[i][j].first});
        }
    }

    int dpSize = 1 << m, dpidx = 0;
    vector<int> memberId;
    for(auto member : members){
        dpidx++;
        memberId.push_back(member.first);
        for(int i = 0; i < dpSize; i++){
            if(dp[dpidx][i].val <= dp[dpidx - 1][i].val){
                dp[dpidx][i].val = dp[dpidx - 1][i].val;
                dp[dpidx][i].fromLastSkill = -1;
            }
            for(auto ski : member.second){
                if(i & (1 << ski.first - 1)) continue;
                int ii = i | (1 << ski.first - 1);
                if(dp[dpidx][ii].val < dp[dpidx - 1][i].val + ski.second){
                    dp[dpidx][ii].val = dp[dpidx - 1][i].val + ski.second;
                    dp[dpidx][ii].fromLastSkill = ski.first;
                }
            }
        }
    }

    // for(int i = 1; i <= dpidx; i++){
    //     for(int j = 0; j < dpSize; j++){
    //         cout << dp[i][j].val << ',' << dp[i][j].fromLastSkill << ' ';
    //     }cout << endl;
    // }
    
    cout << dp[dpidx][dpSize - 1].val << endl;

    for(int i = dpidx, mask = dpSize - 1; i > 0; i--){
        if(dp[i][mask].fromLastSkill != -1){
            cout << memberId[i - 1] << ' ' << dp[i][mask].fromLastSkill << endl;
            mask ^= 1 << dp[i][mask].fromLastSkill - 1;
        }
    }
    return 0;
}
