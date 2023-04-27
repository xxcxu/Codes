#include <stdio.h>
#include <ctype.h>

inline char getc() {
	static char *p1, *p2, buf[1<<20];
	return p1 == p2 ? (p2 = (p1 = buf) + fread(buf, 1, 1<<20, stdin), p1 == p2 ? 10 : *p1++) : *p1++;
}

inline int read() {
	int f = 1, r = 0; char c = getc();
	while (!isdigit(c)) f ^= c == '-', c = getc();
	while (isdigit(c)) r = r * 10 + c - 48, c = getc();
	return f ? r : -r;
}

typedef unsigned int u32;
typedef unsigned long long u64;
const int N=2049;
u32 n,i,j,a[N][N];
u32 u[N][N],v[N][N];//left,bottom
u32 c[N][N],d[N][N];//right,top
u32 pa[N][N],pb[N][N],p[N],s;//stack
u64 ans;
void swap(u32 &a,u32 &b){
	u32 c=a;a=b;b=c;
}
struct node{
	node *l,*r;
	u32 s,sa,sb,la,ra,lb,rb;
	//minsum,asum,bsum,amin,amax,bmin,bmax
	bool fa,fb;//flaga,flagb
}*h;
node *build(u32 l,u32 r){
	node *g=new node;
	if(l==r)return g;
	u32 m=(l+r)>>1;
	g->l=build(l,m);
	g->r=build(m+1,r);
	return g;
}
void clear(node *g,u32 l,u32 r){
	g->s=g->sa=g->sb=0;
	g->la=g->ra=g->lb=g->rb=0;
	g->fa=g->fb=0;
	if(l==r)return;
	u32 m=(l+r)>>1;
	clear(g->l,l,m);
	clear(g->r,m+1,r);
}inline u32 min(u32 a,u32 b){
	return a<b?a:b;
}inline u32 max(u32 a,u32 b){
	return b<a?a:b;
}
inline void setmin(node *g){
	if(g->ra<=g->lb)g->s=g->sa;
	else g->s=g->sb;
}inline void update(node *g,u32 l,u32 r){
	if(l==r)return;
	u32 m=(l+r)>>1;
	bool B=g->fa||g->fb;
	if(g->fa){
		g->l->fa=g->r->fa=1;
		g->fa=0;
		g->l->la=g->r->la=g->l->ra=g->r->ra=g->la;
		g->l->sa=g->la*(m-l+1);
		g->r->sa=g->la*(r-m);
	}if(g->fb){
		g->l->fb=g->r->fb=1;
		g->fb=0;
		g->l->lb=g->r->lb=g->l->rb=g->r->rb=g->lb;
		g->l->sb=g->lb*(m-l+1);
		g->r->sb=g->lb*(r-m);
	}if(B){
		setmin(g->l);
		setmin(g->r);
	}
}void modia(u32 x,u32 y,u32 a,node *g=h,u32 l=0,u32 r=n-1){
	update(g,l,r);
	if(x<=l&&y>=r&&(g->lb>=a||g->rb<=a)){
		g->la=g->ra=a;
		g->sa=a*(r-l+1);
		g->fa=1;
		setmin(g);
		return;
	}u32 m=(l+r)>>1;
	if(x<=m)modia(x,y,a,g->l,l,m);
	if(y>m)modia(x,y,a,g->r,m+1,r);
	g->la=min(g->l->la,g->r->la);
	g->ra=max(g->l->ra,g->r->ra);
	g->lb=min(g->l->lb,g->r->lb);
	g->rb=max(g->l->rb,g->r->rb);
	g->sa=g->l->sa+g->r->sa;
	g->sb=g->l->sb+g->r->sb;
	g->s=g->l->s+g->r->s;
}void modib(u32 x,u32 y,u32 b,node *g=h,u32 l=0,u32 r=n-1){
	update(g,l,r);
	if(x<=l&&y>=r&&(g->la>=b||g->ra<=b)){
		g->lb=g->rb=b;
		g->sb=b*(r-l+1);
		g->fb=1;
		setmin(g);
		return;
	}u32 m=(l+r)>>1;
	if(x<=m)modib(x,y,b,g->l,l,m);
	if(y>m)modib(x,y,b,g->r,m+1,r);
	g->la=min(g->l->la,g->r->la);
	g->ra=max(g->l->ra,g->r->ra);
	g->lb=min(g->l->lb,g->r->lb);
	g->rb=max(g->l->rb,g->r->rb);
	g->sa=g->l->sa+g->r->sa;
	g->sb=g->l->sb+g->r->sb;
	g->s=g->l->s+g->r->s;
}u32 gsum(u32 y,node *g=h,u32 l=0,u32 r=n-1){
	update(g,l,r);
	if(y>=r)return g->s;
	u32 m=(l+r)>>1;
	if(y<=m)return gsum(y,g->l,l,m);
	return g->l->s+gsum(y,g->r,m+1,r);
}

u64 square(u32 x,u32 y,u32 l){
	clear(h,0,n-1);
	u64 ret=0;
	modia(0,n-1,l);
	modib(0,n-1,l);
	for(u32 i=l-1;i;--i){
		if(u[i+x][i+y]-y<l)modia(0,u[i+x][i+y]-y,i);
		if(v[i+x][i+y]-x<l)modib(0,v[i+x][i+y]-x,i);
		if(i<l-1){
			u32 g=i+y-1,g0;
			while((g-y<l)&&g!=pa[i+x][i+y]){
				g0=pa[i+x][g];
				if(g0+1-y<l)modia(g0+1-y,g-y,d[i+x][g]+i);
				else modia(0,g-y,d[i+x][g]+i);
				g=g0;
			}g=i+x-1;
			while((g-x<l)&&g!=pb[i+x][i+y]){
				g0=pb[g][i+y];
				if(g0+1-x<l)modib(g0+1-x,g-x,c[g][i+y]+i);
				else modib(0,g-x,c[g][i+y]+i);
				g=g0;
			}
		}ret+=gsum(i-1)-i*i;
	}return ret;
}

u64 gans(){
	//u:left 0 v:bottom 0
	for(i=0;i<n;++i)u[i][0]=v[0][i]=~0u;
	for(i=0;i<n;++i)
	for(j=0;j<n;++j){
		if(a[i][j]){
			u[i][j+1]=u[i][j];
			v[i+1][j]=v[i][j];
		}else{
			u[i][j+1]=j;
			v[i+1][j]=i;
		}
	}//c:right max 1 d:top max 1
	for(i=n-1;~i;--i)
	for(j=n-1;~j;--j){
		if(a[i][j]){
			c[i][j]=c[i][j+1]+1;
			d[i][j]=d[i+1][j]+1;
		}else c[i][j]=d[i][j]=0;
	}//pa:stack left pb:stack bottom
	for(i=0;i<n;++i)
	for(j=0,s=0;j<n;++j){
		while(s&&d[i][j]<=d[i][p[s-1]])--s;
		if(s)pa[i][j]=p[s-1];
		else pa[i][j]=~0u;
		p[s++]=j;
	}
	for(j=0;j<n;++j)
	for(i=0,s=0;i<n;++i){
		while(s&&c[i][j]<=c[p[s-1]][j])--s;
		if(s)pb[i][j]=p[s-1];
		else pb[i][j]=~0u;
		p[s++]=i;
	}
	u64 ret=0;
	for(i=0;i<n;++i)ret+=square(0,i,n-i);
	for(i=1;i<n;++i)ret+=square(i,0,n-i);
	return ret;
}int main(){
	freopen("jntm.in","r",stdin);
	freopen("jntm.out","w",stdout);
	
	n=read();
	for(i=0;i<n;++i)
	for(j=0;j<n;++j)a[i][j]=read();
	h=build(0,n-1);
	ans=gans();
	for(i=0;i<n;++i)
	for(j=0;j<n-j-1;++j)swap(a[i][j],a[i][n-j-1]);
	ans+=gans();
	printf("%llu",ans);
	return 0;
}
