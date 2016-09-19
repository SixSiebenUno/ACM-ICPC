#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

#define ll long long

const int MaxN = 5 * (int)1e4 + 7;

int T,n,miu[MaxN],pri[MaxN];
bool isp[MaxN];
int a,b,c,d,p;
ll ans,summiu[MaxN];

void GetMiu()
{
	int i,j;
	n = 5 * (int)1e4; miu[1] = 1;
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
	for(i=0;i<=n;i++)
		summiu[i] = summiu[i-1]+miu[i];
}

inline ll Calc(int n,int m)
{
	int i,j,k; ll s = 0;
	for(i=1; i<=n && i<=m; i=j+1)
	{
		j = n/(n/i);
		k = m/(m/i);
		//printf("%d %d %d",i,j,k);
		//printf("  ==>  %d %d %d %d\n",n/i,n/j,m/i,m/k);
		j = min(j,k);
		s += (ll) (summiu[j]-summiu[i-1]) * (n/i) * (m/i);
	}
	//cout <<"End:  "<< n<<' '<<m<<' '<<p<<" :  "<<s << endl;
	return s;
}

int main()
{
	GetMiu();
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&p);
		ans = 0;
		ans += Calc(b/p,d/p);
		ans -= Calc((a-1)/p,d/p);
		ans -= Calc(b/p,(c-1)/p);
		ans += Calc((a-1)/p,(c-1)/p);
		printf("%lld\n",ans);
	}
	return 0;
}
