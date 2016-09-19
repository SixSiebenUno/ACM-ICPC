#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int MaxL = 20000;

int T,l; char str[MaxL];

int main()
{
	int i,j;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",str+1);
		l = strlen(str+1);
		for(i=1,j=l;i<=j;i++,j--)
			if(str[i]=='.' && str[j]=='.') str[i] = str[j] = 'a';
			else if(str[i]=='.') str[i] = str[j];
			else if(str[j]=='.') str[j] = str[i];
			else if(str[i]!=str[j]) break;
		if(i<=j) printf("-1\n");
		else printf("%s\n",str+1);
	}
	return 0;
}
