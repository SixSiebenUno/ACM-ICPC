#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int MaxN = 100007;

struct SegType
{
	int l,r,f,id,siz,d,a[21];
};

int T,n,m,a[MaxN];
SegType seg[MaxN<<2];

void MakeSeg(int x,int l,int r)
{
	seg[x].l = l; seg[x].r = r;
	seg[x].f = 0; seg[x].id = 1; seg[x].siz = 1;

	if(l==r)
	{
		int i,j,d; i = 1; d = a[l];

		for(j=2;j*j<=d;j++)
			if(d%j==0)
				while(d%j==0) seg[x].a[i++] = j, d/=j;
		if(d!=1) seg[x].a[i++] = d;
		while(i<=20) seg[x].a[i++] = 1;
		seg[x].d = seg[x].a[1];
		/*
		printf("%d :  ",a[l]);
		for(i=1;i<20;i++) printf("%d ",seg[x].a[i]);
		printf("\n");
		*/
		return;
	}

	int i, lc = x<<1, mi = (l+r)>>1;
	MakeSeg(lc,l,mi);
	MakeSeg(lc+1,mi+1,r);

	for(i=1;i<=20;i++)
		seg[x].a[i] = max(seg[lc].a[i], seg[lc+1].a[i]);
	seg[x].d = max(seg[lc].d, seg[lc+1].d);
}

void Download(int x)
{
	int lc = x<<1, f = seg[x].f; seg[x].f = 0;
	seg[lc].f += f; seg[lc+1].f += f;
	seg[lc].id += f; seg[lc+1].id += f;
	if(seg[lc].id > 20) seg[lc].id = 20;
	if(seg[lc+1].id > 20) seg[lc+1].id = 20;
	if(seg[lc].siz) seg[lc].d = seg[lc].a[seg[lc].id];
	if(seg[lc+1].siz) seg[lc+1].d = seg[lc+1].a[seg[lc+1].id];
}

int Calc(int x,int l,int r)
{
	//printf("Calc: %d %d %d %d\n",x,seg[x].l,seg[x].r,seg[x].d);
	if(l<=seg[x].l && seg[x].r<=r && seg[x].siz)
		return seg[x].d;
	int lc = x<<1, ans = 1;
	if(seg[x].f) Download(x);
	if(l <= seg[lc].r) ans = max(ans, Calc(lc,l,r));
	if(seg[lc].r < r) ans = max(ans, Calc(lc+1,l,r));
	seg[x].d = max(seg[lc].d, seg[lc+1].d);
	if(seg[lc].siz && seg[lc+1].siz && seg[lc].id==seg[lc+1].id)
		seg[x].siz = 1, seg[x].id = seg[lc].id;
	else seg[x].siz = 0;
	return ans;
}

void Update(int x,int l,int r)
{
	//printf("Update: %d %d %d  %d %d\n",x,l,r,seg[x].f,seg[x].id);
	if(l<=seg[x].l && seg[x].r<=r && seg[x].siz)
	{
		seg[x].f ++; seg[x].id ++;
		if(seg[x].id>20) seg[x].id = 20;
		seg[x].d = seg[x].a[seg[x].id];
		return;
	}
	int lc = x<<1;
	if(seg[x].f) Download(x);
	if(l <= seg[lc].r) Update(lc,l,r);
	if(seg[lc].r < r) Update(lc+1,l,r);
	seg[x].d = max(seg[lc].d, seg[lc+1].d);
	if(seg[lc].siz && seg[lc+1].siz && seg[lc].id==seg[lc+1].id)
		seg[x].siz = 1, seg[x].id = seg[lc].id;
	else seg[x].siz = 0;
}

int main()
{
	freopen("E.in","r",stdin);
	freopen("E.out","w",stdout);

	int i,typ,l,r;

	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(i=1;i<=n;i++)
			scanf("%d",a+i);
		MakeSeg(1,1,n);
		for(i=1;i<=m;i++)
		{
			scanf("%d%d%d",&typ,&l,&r);
			if(typ==1) printf("%d ",Calc(1,l,r));
			else Update(1,l,r);
		}
		printf("\n");
	}

	return 0;
}
