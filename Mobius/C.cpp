#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define ll long long

const int MaxN = (int)1e5 + 7;

int T,n,m,phi[MaxN],pri[MaxN];
bool isp[MaxN];
ll ans,sumphi[MaxN];

void GetPhi()
{
	int i,j;
	n = (int)1e5; phi[1] = 1;
	for(i=2;i<=n;i++)
	{
		if(!isp[i])
			pri[++pri[0]] = i, phi[i] = i-1;
		for(j=1;j<=pri[0]&&i*pri[j]<=n;j++)
		{
			isp[i*pri[j]] = true;
			if(i%pri[j]==0)
				phi[i*pri[j]] = phi[i] * pri[j];
			else phi[i*pri[j]] = phi[i] * (pri[j]-1);
		}
	}
	for(i=1;i<=n;i++)
		sumphi[i] = sumphi[i-1]+phi[i];
}

inline ll Calc(int n,int m)
{
	int i,j,k; ll s = 0;
	for(i=1; i<=n && i<=m; i=j+1)
	{
		j = n/(n/i); k = m/(m/i); j = min(j,k);
		s += (ll) (sumphi[j]-sumphi[i-1]) * (n/i) * (m/i);
	}
	return (s<<1) - (ll) n*m;
}

int main()
{
	GetPhi();
	scanf("%d%d",&n,&m);
	printf("%lld\n",Calc(n,m));
	return 0;
}
