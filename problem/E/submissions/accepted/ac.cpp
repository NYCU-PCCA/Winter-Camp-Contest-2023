#include<bits/stdc++.h>
#define int long long
#define matsuri pair<int,int>
//const int iris = 1e9+7;
const int iris = 998244353;
using namespace std;

int arr[100001];
int dis[2][100001];
vector<matsuri> G[100001];

void dijk(int a, int *ddd, int n)
{
	priority_queue<matsuri, vector<matsuri>, greater<matsuri> > pq;
	int i;
	for(i=1;i<=n;i++)
		ddd[i]=1e18;
	ddd[a]=0;
	pq.push({0,a});
	while(!pq.empty())
	{
		auto [d,a]=pq.top();
		pq.pop();
		if(ddd[a]!=d)
			continue;
		for(auto [b,c]:G[a])
		{
			if(ddd[a]+c < ddd[b])
			{
				ddd[b]=ddd[a]+c;
				pq.push({ddd[b], b});
			}
		}
	}
}

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n,m,a,b,c,x,y,i;
	
	cin>>n>>m;
	for(i=1;i<=n;i++)
		cin>>arr[i];
	while(m--)
	{
		cin>>a>>b>>c;
		G[a].emplace_back(b,c);
		G[b].emplace_back(a,c);
	}
	dijk(1,dis[0],n);
	dijk(n,dis[1],n);
	x=y=1e18;
	for(i=1;i<=n;i++)
	{
		x=min(x, dis[0][i]+arr[i]);
		y=min(y, dis[1][i]+arr[i]);
	}
	cout<<min(x+y, dis[0][n])<<'\n';
	
	return 0;
}
