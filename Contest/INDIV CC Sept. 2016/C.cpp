#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

int T,n,c,s,t,typ[10];
int maxs,maxid,tie;

int main()
{
	freopen("C.in","r",stdin);

	int i,j,k;

	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		maxs = maxid = tie = 0;
		for(i=1;i<=n;i++)
		{
			scanf("%d",&c);
			for(j=1;j<=6;j++) typ[j] = 0;
			for(j=1;j<=c;j++)
				scanf("%d",&k), typ[k]++;
			sort(typ+1,typ+7);
			
			s = c;
			s += 4 * typ[1];
			s += 2 * (typ[2]-typ[1]);
			s += typ[3]-typ[2];

			if(s > maxs) maxs = s, maxid = i, tie = 0;
			else if(s == maxs) tie = 1;
		}
		if(tie) printf("tie\n");
		else if(maxid==1) printf("chef\n");
		else printf("%d\n",maxid);
	}
	return 0;
}
