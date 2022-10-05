 #include<bits/stdc++.h>
using namespace std;
#define int long long
int read(){
	int a=0,fh=1;char c=getchar();
	while(c>'9'||c<'0'){if(c=='-')fh=-1;c=getchar();}
	while('0'<=c&&c<='9'){
		a=a*10+c-48;
		c=getchar();
	}
	return a*fh;
}
#define MN 500005
#define pii pair<int,int>
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define vc vector
int n,m;
int fa[MN],dep[MN],anc[MN][21],eid[MN],tag[MN][2];
bool vis[MN];
struct vec{
	int x,y,z;
	vec(){}
	
	vec(int X,int Y,int Z){
		x=X,y=Y,z=Z;
	}
}loc[MN],w[MN];
vec operator +(vec a,vec b){
	return vec(a.x+b.x,a.y+b.y,a.z+b.z);
}
bool operator ==(vec a,vec b){
	return a.x==b.x&&a.y==b.y&&a.z==b.z;
}
vc<pair<int,vec > >e[MN];
void dfs(int x){
//	cerr<<"dfs: "<<x<<" "<<fa[x]<<endl;
	vis[x]=1;
	dep[x]=dep[fa[x]]+1;
	anc[x][0]=fa[x];
	for(int i=1;i<=19;++i)anc[x][i]=anc[anc[x][i-1]][i-1];
	for(auto i:e[x]){
		int v=i.x;
		if(vis[v])continue;
		fa[v]=x;
		loc[v]=loc[x]+i.y;
		dfs(v); 
	}
}
int LCA(int x,int y){
	if(dep[x]<dep[y])swap(x,y);
	for(int i=19;i>=0;--i)
		if(dep[anc[x][i]]>=dep[y])x=anc[x][i];
	if(x==y)return x;
	for(int i=19;i>=0;--i)
		if(anc[x][i]!=anc[y][i])x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}
int u[MN],v[MN];
vc<int>ans,err;
void DFS(int x){
	for(auto i:e[x]){
		int v=i.x;
		if(fa[v]!=x)continue;
		DFS(v);
		for(int i=0;i<2;++i)tag[x][i]+=tag[v][i];
	}
	if(tag[x][0]==err.size()&&!tag[x][1]&&x != 1)ans.pb(eid[x]);
}
signed main(){
//	freopen("4.in","r",stdin);
//	freopen("4.out","w",stdout);
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		u[i]=read(),v[i]=read(); 
		int x=read(),y=read(),z=read();
		w[i]=vec(x,y,z);
		e[u[i]].pb(mp(v[i],vec(x,y,z)));
		e[v[i]].pb(mp(u[i],vec(-x,-y,-z)));
	}
	dfs(1);
	for(int i=1;i<=m;++i){
		int x=u[i],y=v[i];
		if(fa[x]==y||fa[y]==x){
			assert((loc[x]+w[i])==loc[y]);
			if(fa[y]==x)swap(x,y);
			eid[x]=i;
			continue;
		}
		int g=LCA(x,y);
		bool op=((loc[x]+w[i])==loc[y]);
	//	else cerr<<"! "<<x<<" "<<y<<" "<<g<<endl; 
		tag[x][op]++;
		tag[y][op]++;
		tag[g][op]-=2;
		if(!op)err.pb(i);
	}
	//for(auto i:err)cerr<<"err: "<<i<<endl;
	DFS(1);
	if(err.size()==1)ans.pb(err.back());
	sort(ans.begin(),ans.end());
	if (!ans.empty() && ans.front() == 0)
	    ans = vector<int>(ans.begin() + 1, ans.end());
	printf("%lld\n",(int)ans.size());
	for(auto i:ans)printf("%lld ",i);
	return 0;
}
