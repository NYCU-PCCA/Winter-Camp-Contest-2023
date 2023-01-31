#include<bits/stdc++.h>
#define int long long
#define matsuri pair<int,int>
//const int iris = 1e9+7;
const int iris = 998244353;
using namespace std;

char arr[102][102];

signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int T;
	cin>>T;
	while(T--)
	{
		int n,m,i,j,cnt,nene;
		cnt=nene=0;
		
		cin>>n>>m;
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				cin>>arr[i][j], cnt+=(arr[i][j]=='#');
		for(i=1;i<=n;i++)
		{
			if(i&1)
			{
				for(j=1;j<=m;j++)
				{
					if(arr[i][j]=='#')
						nene++;
					else if(nene%2 && nene<cnt)
					{
						if(j==1)
							arr[i][j]='A';
						else if(j==m)
							arr[i][j]='C';
						else
							arr[i][j]='F';
					}
				}
			}
			else
			{
				for(j=m;j>=0;j--)
				{
					if(arr[i][j]=='#')
						nene++;
					else if(nene%2 && nene<cnt)
					{
						if(j==1)
							arr[i][j]='B';
						else if(j==m)
							arr[i][j]='D';
						else
							arr[i][j]='F';
					}
				}
			}
		}
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=m;j++)
				cout<<arr[i][j];
			cout<<'\n';
		}
	}
	
	return 0;
}
