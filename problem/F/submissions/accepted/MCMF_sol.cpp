#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define rep(i, a, b) for(int i = a; i < b; i++)
#define rrep(i, a, b) for(int i = a; i <= b; i++)
#define rvep(i, a, b) for(int i = a; i >= b; i--)

#define pb push_back
const int MAX_N = 1.2e5 + 5 + 60;
const int MAX_M = 60 + 5;
const ll INF = 1LL << 50;
const ll C = 1LL << 35;

int n, m, mm;
// from code book
struct MCMF { // 0-base
    struct edge {
        ll from, to, cap, flow, cost, rev;
    } *past[MAX_N];
    vector<edge> G[MAX_N];
    bitset<MAX_N> inq;
    ll dis[MAX_N], up[MAX_N], s, t, mx, n;
    bool BellmanFord(ll &flow, ll &cost) {
        fill(dis, dis + n, INF);
        queue<ll> q;
        q.push(s), inq.reset(), inq[s] = 1;
        up[s] = mx - flow, past[s] = 0, dis[s] = 0;
        while (!q.empty()) {
            ll u = q.front();
            q.pop(), inq[u] = 0;
            if (!up[u]) continue;
            for (auto &e : G[u]){
                if (e.flow != e.cap && dis[e.to] > dis[u] + e.cost) {
                    dis[e.to] = dis[u] + e.cost, past[e.to] = &e;
                    up[e.to] = min(up[u], e.cap - e.flow);
                    if (!inq[e.to]) inq[e.to] = 1, q.push(e.to);
                }
            }
        }
        if (dis[t] == INF) return 0;
        flow += up[t], cost += up[t] * dis[t];
        for (ll i = t; past[i]; i = past[i]->from) {
            auto &e = *past[i];
            e.flow += up[t], G[e.to][e.rev].flow -= up[t];
        }
        return 1;
    }
    ll MinCostMaxFlow(ll _s, ll _t, ll &cost) {
        s = _s, t = _t, cost = 0;
        ll flow = 0;
        while (BellmanFord(flow, cost));
        return flow;
    }
    void init(ll _n, ll _mx) {
        n = _n, mx = _mx;
        for (int i = 0; i < n; ++i) G[i].clear();
    }
    void add_edge(ll a, ll b, ll cap, ll cost) {
        G[a].pb(edge{a, b, cap, 0, cost, G[b].size()});
        G[b].pb(edge{b, a, 0, 0, -cost, G[a].size() - 1});
        // cout << a << ' ' << b << ' ' << cap << ' ' << cost << endl;
    }
    void getmember(int n){
        for(auto e : G[s]){
            if(e.cap == e.flow){
                cout << e.to << ' ';
                for(auto f : G[e.to]){
                    if(f.cap == f.flow){
                        cout << f.to - n << "\n";
                        break;
                    }
                }
            }
        }
    }
}mcmf;

// ll dp[MAX_M * MAX_M][1 << MAX_M];
pll skill[MAX_M][MAX_N];
int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    
    cin >> n >> m;
    mm = m * m;
    int s = 0, t = n + m + 1;
    mcmf.init(t + 1, m);
    
    rrep(i, 1, n){
        rrep(j, 1, m){
            cin >> skill[j][i].first;
            skill[j][i].second = i;
        }
    }

    set<ll> members;
    rrep(i, 1, m){
        nth_element(skill[i] + 1, skill[i] + m + 1, skill[i] + n + 1, greater<pll>());
        rrep(j, 1, m){
            // cout << cout <<  << endl;
            members.insert(skill[i][j].second);
            mcmf.add_edge(skill[i][j].second, n + i, 1, C - skill[i][j].first);
        }
        mcmf.add_edge(n + i, t, 1, 0);
    }
    // cout << members.size() << endl;
    for(auto member : members){
        // cout << member << endl;
        mcmf.add_edge(s, member, 1, 0);
    }
    ll ans = 0;
    mcmf.MinCostMaxFlow(s, t, ans);
    
    cout << C * m - ans << endl;
    mcmf.getmember(n);
    return 0;
}
