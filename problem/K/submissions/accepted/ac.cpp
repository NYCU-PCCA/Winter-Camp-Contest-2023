#include<bits/stdc++.h>
#define int long long
#define matsuri pair<int,int>
//const int iris = 1e9+7;
const int iris = 998244353;
using namespace std;

struct dsu{
	vector<int> arr;
	vector<matsuri> op;
	int n;
	
	void init(int _n)
	{
		n=_n;
		arr.resize(n+1,1);
	}
	int fnd(int a)
	{
		return arr[a]>0 ? a : fnd(-arr[a]);
	}
	void unn(int a,int b)
	{
		a=fnd(a);
		b=fnd(b);
		if(arr[a]<arr[b])
			swap(a,b);
		op.emplace_back(a,arr[a]);
		op.emplace_back(b,arr[b]);
		op.emplace_back(0,arr[0]);
		if(a==b)
			return;
		arr[a]+=arr[b];
		arr[b]=-a;
		arr[0]=max(arr[0], arr[a]);
	}
	void rev()
	{
		for(int i=0;i<3;i++)
		{
			auto [a,x]=op.back();
			arr[a]=x;
			op.pop_back();
		}
	}
	int kaltist()
	{
		return arr[0];
	}
}ds;

vector<int> sagiri[400001];
int ans;
bool ex[100001];
vector<int> G[100001];

void add(int l,int r,int i,int L,int R,int a)
{
	int m=(l+r)/2;
	if(L<=l && r<=R)
		sagiri[i].emplace_back(a);
	else if(l<=R && L<=r)
		add(l,m,i*2,L,R,a), add(m+1,r,i*2+1,L,R,a);
}
void sana(int l,int r,int i)
{
	int m=(l+r)/2;
	for(int a:sagiri[i])
	{
		ex[a]=1;
		for(int b:G[a])
			if(ex[b])
				ds.unn(a,b);
	}
	if(l<r)
		sana(l,m,i*2), sana(m+1,r,i*2+1);
	else
		ans=max(ans, ds.kaltist());
	for(int a:sagiri[i])
	{
		ex[a]=0;
		for(int b:G[a])
			if(ex[b])
				ds.rev();
	}
}

int mx=1e5;

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n,m,k,i,a,b;
	
	cin>>n>>m>>k;
	ds.init(n);
	for(i=1;i<=n;i++)
	{
		cin>>a;
		add(1,mx,1,max(a-k,1LL),a,i);
	}
	while(m--)
	{
		cin>>a>>b;
		G[a].emplace_back(b);
		G[b].emplace_back(a);
	}
	sana(1,mx,1);
	cout<<ans<<'\n';
	
	return 0;
}
