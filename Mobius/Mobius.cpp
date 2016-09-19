#include <iostream>
#include <cstdio>
using namespace std;

const int MaxN = (int) 1e5 + 7;

int n,miu[MaxN],pri[MaxN];
bool isp[MaxN];

int main()
{
	int i,j;
	n = 100;
	miu[1] = 1;
	for(i=2;i<=n;i++)
	{
		if(!isp[i])
		{
			//printf("%d\n",i);
			pri[++pri[0]] = i;
			miu[i] = -1;
		}
		for(j=1;j<=pri[0]&&i*pri[j]<=n;j++)
		{
			isp[i*pri[j]] = true;
			if(i%pri[j]==0) miu[i*pri[j]] = 0;
			else miu[i*pri[j]] = -miu[i];
		}
	}
	for(i=1;i<=n;i++)
		printf("%d %d\n",i,miu[i]);
	return 0;
}
