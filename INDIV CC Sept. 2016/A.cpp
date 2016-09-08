#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const int MaxL = 100007;

int T; char str[MaxL];

int main()
{
	int i,l,a,b;

	scanf("%d",&T);
	
	while(T--)
	{
		scanf("%s",str+1);
		l = strlen(str+1);
		a = b = 0;
		for(i=1;i<=l;i++)
			if(str[i]=='1') a++;
			else b++;
		if(a==1 || b==1) printf("Yes\n");
		else printf("No\n");
	}

	return 0;
}
