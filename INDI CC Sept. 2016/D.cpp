#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

const int MaxN = 1007;

int T,n,m,col[MaxN];
bool lnk[MaxN][MaxN];
vector<int> iv[MaxN];

bool Color(int x,int c)
{
	int i,u;
	col[x] = c;
	for(i=0;i<iv[x].size();i++)
	{
		u = iv[x][i];
		if(col[u]==c) return false;
		if(col[u]==0 && !Color(u,3-c)) return false;
	}
	return true;
}

int main()
{
	freopen("D.in","r",stdin);

	int i,j,a,b;
	bool flg;

	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++) lnk[i][j] = false;
		for(i=1;i<=n;i++)
			lnk[i][i] = true, col[i] = 0, iv[i].clear();
		for(i=1;i<=m;i++)
		{
			scanf("%d%d",&a,&b);
			lnk[a][b] = lnk[b][a] = true;
		}
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				if(!lnk[i][j])
					iv[i].push_back(j), iv[j].push_back(i);

		flg = true;
		for(i=1;i<=n;i++)
			if(!col[i]) flg &= Color(i,1);
		if(flg) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
