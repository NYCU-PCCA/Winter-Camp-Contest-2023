#include<bits/stdc++.h>
#include "testlib.h"
//#define int long long
#define matsuri pair<int,int>
const int iris = 1e9+7;
using namespace std;

int dir[][2]={{-1,0}, {0,1}, {1,0}, {0,-1}};
char arr[102][102], aoi[102][102];
bool vis[102][102], ouo[102][102][4];

int sana(int a,int b)
{
	if(vis[a][b])
		return 0;
	vis[a][b]=1;
	int res=(arr[a][b]=='#'), i,c,d,cnt=0;
	for(i=0;i<4;i++)
	{
		c=a+dir[i][0];
		d=b+dir[i][1];
		
		if((arr[a][b]=='#' || ouo[a][b][i]) && (ouo[c][d][(i+2)%4] || arr[c][d]=='#'))
			res+=sana(c,d), cnt++;
	}
	if(arr[a][b]=='#' && cnt>1)
		res=-99999;
	return res;
}

int main(int argc, char* argv[])
{
	registerTestlibCmd(argc, argv);
	
	int T=inf.readInt(1,10);
	inf.readEoln();
	
	while(T--)
	{
		int n,m,i,j,k,cnt=0,sagiri=100;
		char c;
		
		n=inf.readInt(1,sagiri);
		inf.readSpace();
		m=inf.readInt(1,sagiri);
		inf.readEoln();
		
		for(i=0;i<=n+1;i++)
		{
			for(j=0;j<=m+1;j++)
			{
				arr[i][j]='.';
				vis[i][j]=0;
				for(k=0;k<4;k++)
					ouo[i][j][k]=0;
			}
		}
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=m;j++)
			{
				arr[i][j]=inf.readChar();
				cnt+=(arr[i][j]=='#');
			}
			inf.readEoln();
		}
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=m;j++)
			{
				c=aoi[i][j]=ouf.readChar();
				if((arr[i][j]=='#')^(c=='#') || ((c<'A' || c>'F') && c!='#' && c!='.'))
					quitf(_wa, "invalid %d", T);
				
				if('A'<=c && c<='D')
				{
					ouo[i][j][c-'A']=ouo[i][j][(c-'A'+1)%4]=1;
				}
				else if(c=='E')
				{
					ouo[i][j][0]=ouo[i][j][2]=1;
				}
				else if(c=='F')
				{
					ouo[i][j][1]=ouo[i][j][3]=1;
				}
			}
			ouf.readEoln();
		}
		
		cnt/=2;
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=m;j++)
			{
				if(arr[i][j]=='#' && !vis[i][j])
				{
					int a=sana(i,j);
					if(a==2)
						cnt--;
					else if(a<0)
						quitf(_wa, "invalidouo %d %d %d", T, i, j);
				}
			}
		}
		if(cnt)
			quitf(_wa, "ohno %d %d", T, cnt);
	}

	inf.readEof();
	ouf.readEof();
	
	quitf(_ok, "oniichandaisuki");

	return 0;
}
