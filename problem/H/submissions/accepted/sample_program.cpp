#include<bits/stdc++.h>


#define eb emplace_back
#define ll long long
#define INF (ll)0x3f3f3f3f3f3f3f3f
#define endl '\n'

using namespace std;

struct Dinic {
	struct Edge {
		ll to, flow;
		Edge(ll a, ll b) : to(a), flow(b) {}
	};

	ll s, t;
	vector<Edge> e;
	vector<ll> dis;
	vector<int> cur;
	vector<vector<ll>> G;

	Dinic(ll sz): dis(sz + 1), G(sz + 1), cur(sz + 1) {}

	void add(ll u, ll v,  ll f) {
		G[u].eb(e.size());
		e.eb(v, f);
		G[v].eb(e.size());
		e.eb(u, 0);
	}

	bool bfs() {
		fill(dis.begin(), dis.end(), -1);
		queue<int> que;
		que.emplace(s);
		dis[s] = 0;
		while(que.size()) {
			int x = que.front(); que.pop();
			for(int id : G[x]) {
				ll y = e[id].to, f = e[id].flow;
				if(dis[y] == -1 && f > 0) {
					dis[y] = dis[x] + 1;
					que.emplace(y);
				}
			}
		}
		return dis[t] != -1;
	}

	ll dfs(ll x, ll f = INF) {
		if(x == t || f == 0) return f;
		ll a, ret = 0;
		for(int &i = cur[x]; i < G[x].size(); i ++) {
			int id = G[x][i];
			ll y = e[id].to;
			if(e[id].flow > 0 && dis[y] == dis[x] + 1) {
				a = dfs(y, min(f, e[id].flow));
				e[id ^ 1].flow += a;
				e[id].flow -= a;
				ret += a;
				f -= a;
			}
			if(f == 0) return ret;
		}
		return ret;
	}

	ll solve(ll _s, ll _t ) {
		s = _s;
		t = _t;
		ll df, flow = 0;
		while(bfs()) {
			fill(cur.begin(), cur.end(), 0);
			while((df = dfs(s))) flow += df;
		}
		return flow;
	}
};

void read_graph(int t, Dinic &D) {
	int cur = 1;
	int _s = 0, _t = t * t + 3;
	for(int i = 0; i < t; i ++) {
		for(int j = 0; j < 2 * i + 1; j ++) {
			if(j & 1) {
				D.add(_s, cur, 1);
			}else {
				D.add(cur, _t, 1);
			}
			cur ++;
		}
	}
	for(int i = 0; i < t; i ++) {
		for(int j = 0; j < (i + 1); j ++) {
			char tmpa, tmpb;
			cin >> tmpa >> tmpb;
			int cur_id = 1 + i * i + j * 2;
			if(tmpa == '.') {
//				cout << cur_id - 1 << ' ' << cur_id << endl;
				D.add(cur_id - 1, cur_id, 1);
			}
			if(tmpb == '.') {
//				cout << cur_id + 1 << ' ' << cur_id << endl;
				D.add(cur_id + 1, cur_id, 1);
			}
		}
		for(int j = 0; j < (i + 1); j ++) {
			char tmpa, tmpb;
			cin >> tmpa >> tmpb;
			int top_id = 1 + i * i + j * 2;
			int bot_id = 2 + (i + 1) * (i + 1) + j * 2;
			if(tmpa == '.') {
//				cout << top_id << ' ' << bot_id << endl;
				D.add(bot_id, top_id, 1);
			}
		}
	}
}

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);
	int t;
	cin >> t;

	Dinic D(t * t + 5);

	read_graph(t, D);
	cout << D.solve(0, t * t + 3) << endl;

//	for(int i = 1; i <= n; i ++) {
//		D.add(0, i, 1);
//	}
//
//	for(int i = 1; i <= m; i ++) {
//		D.add(i + n, n + m + 1, 1);
//	}
//
//	for(int i = 0; i < e; i ++) {
//		int a, b;
//		cin >> a >> b;
//		if(st.find({a, b + n}) != st.end()) continue;
//		D.add(a, b + n, 1);
//	}
//
//	cout << D.solve(0, n + m + 1) << endl;
	
	return 0;
}
