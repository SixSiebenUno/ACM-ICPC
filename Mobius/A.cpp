//http://www.spoj.com/problems/VLATTICE/

#include <iostream>
#include <cstdio>
using namespace std;

#define ll long long

const int MaxN = (int) 1e6 + 7;

int T,n,miu[MaxN],pri[MaxN];
bool isp[MaxN];
ll ans,ans1,ans2;

void GetMiu()
{
	int i,j;
	n = (int) 1e6; miu[1] = 1;
	for(i=2;i<=n;i++)
	{
		if(!isp[i])
			pri[++pri[0]] = i, miu[i] = -1;
		for(j=1;j<=pri[0]&&i*pri[j]<=n;j++)
		{
			isp[i*pri[j]] = true;
			if(i%pri[j]==0) miu[i*pri[j]] = 0;
			else miu[i*pri[j]] = -miu[i];
		}
	}
}

int main()
{
	int i,d;
	GetMiu();
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		ans = 3LL; ans1 = ans2 = 0;
		for(d=1;d<=n;d++)
		{
			i = n/d;
			ans1 += (ll) miu[d] * i * i;
			ans2 += (ll) miu[d] * i * i * i;
		}
		ans += ans1 * 3 + ans2;
		printf("%lld\n",ans);
	}
	return 0;
}
