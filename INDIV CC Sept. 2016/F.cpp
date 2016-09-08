#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define ll long long

const int MaxN = 100007;

int n,m,q;
int fir[MaxN],nxt[MaxN],len[MaxN],cst[MaxN];
vector<int> iv[MaxN];
ll f[MaxN],seg[MaxN<<2];
int tot,l[MaxN<<2],r[MaxN<<2]; 

void Insert(int x,int id,ll d)
{
	if(l[x]==r[x])
	{
		seg[x] = d;
		return;
	}
	int lc = x<<1;
	if(id<=r[lc]) Insert(lc,id,d);
	else Insert(lc+1,id,d);
	seg[x] = min(seg[lc],seg[lc+1]);
}

void Delete(int x,int id)
{
	if(l[x]==r[x])
	{
		seg[x] = 1LL<<60;
		return;
	}
	int lc = x<<1;
	if(id<=r[lc]) Delete(lc,id);
	else Delete(lc+1,id);
	seg[x] = min(seg[lc],seg[lc+1]);
}

inline ll GetMin(int x,int le,int ri)
{
	if(le<=l[x] && r[x]<=ri) return seg[x];
	int lc = x<<1; ll ans = 1LL<<60;
	if(le<=r[lc]) ans = min(ans, GetMin(lc,le,ri));
	if(r[lc]<ri) ans = min(ans, GetMin(lc+1,le,ri));
	return ans;
}

inline ll Calc(int l,int r)
{
	if(l<1) l = 1;
	return GetMin(1,l,r);
}

void DFS(int x)
{
	int i;
	if(x==1) f[x] = 0;
	else
	{
		f[x] = 1LL<<60;
		for(i=fir[x]; i; i = nxt[i])
			f[x] = min(f[x], cst[i] + Calc(tot-len[i]+1,tot));
	}
	tot++; Insert(1,tot,f[x]);
	for(i=0;i<iv[x].size();i++)
		DFS(iv[x][i]);
	Delete(1,tot); tot--;
	//printf("%d %lld\n",x,f[x]);
}

void MakeSeg(int x,int le,int ri)
{
	l[x] = le; r[x] = ri; seg[x] = 1LL<<60;
	if(le==ri) return;
	int lc = x<<1, mi = (le+ri)>>1;
	MakeSeg(lc,le,mi);
	MakeSeg(lc+1,mi+1,ri);
}

int main()
{
	freopen("F.in","r",stdin);
	//freopen("F.out","w",stdout);

	int i,a,b,v,k,w;

	scanf("%d%d",&n,&m);
	for(i=1;i<n;i++)
		scanf("%d%d",&a,&b),
		iv[b].push_back(a);
	for(i=1;i<=m;i++)
	{
		scanf("%d%d%d",&v,&k,&w);
		nxt[i] = fir[v];
		fir[v] = i;
		len[i] = k; cst[i] = w;
	}
	MakeSeg(1,1,n);

	tot = 0; DFS(1);

	scanf("%d",&q);
	for(i=1;i<=q;i++)
		scanf("%d",&a), printf("%lld\n",f[a]);

	return 0;
}
