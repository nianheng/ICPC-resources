#include<bits/stdc++.h>
using namespace std;

const int MAXN=200005;
const int MAXM=500005;
const int INF=0x3f3f3f3f;

struct DSU
{
    int fa[MAXN];
    void init(int n)
    {
        iota(fa+1,fa+n+1,1);
    }
    int find(int x)
    {
        return fa[x]==x ? x : fa[x]=find(fa[x]);
    }
    int merge(int x,int y)
    {
        x=find(x),y=find(y);
        if(x==y)return 0;
        return fa[x]=y,1;
    }
}dsu;

int col[MAXN][2];
vector<pair<int,int>> e[MAXN];
vector<tuple<int,int,int>> extra;

pair<int,int> fa[MAXN];
int dep[MAXN],sz[MAXN],son[MAXN];
int top[MAXN],dfn[MAXN],loc[MAXN],ts;
void dfs1(int u,int f)
{
    sz[u]=1,dep[u]=dep[f]+1;
    for(auto& [v,id] : e[u])
    {
        if(v==f)continue;
        fa[v]={u,id};
        dfs1(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[son[u]])son[u]=v;
    }
}
void dfs2(int u,int t)
{
    top[u]=t,loc[dfn[u]=++ts]=u;
    if(son[u])dfs2(son[u],t);
    for(auto& [v,id] : e[u])
    {
        if(v==fa[u].first || v==son[u])continue;
        dfs2(v,v);
    }
}
int lca(int u,int v)
{
    while(top[u]!=top[v])
        (dep[top[u]]>dep[top[v]] ? u=fa[top[u]].first : v=fa[top[v]].first);
    return (dep[u]<dep[v] ? u : v);
}
bool check(int u,int v,int a,int b)
{
    int w[4]={lca(u,a),lca(u,b),lca(v,a),lca(v,b)};
    sort(w,w+4,[&](int i,int j){ return dep[i]>dep[j]; });
    return w[0]!=w[1] || (dep[w[0]]>=dep[lca(u,v)] && dep[w[1]]>=dep[lca(a,b)]);
}

struct Path
{
    int a[2][2],c[2][2];
    Path()
    {
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
                a[i][j]=-INF,c[i][j]=0;
    }
    Path(int col[2])
    {
        a[0][0]=a[1][1]=0;
        a[0][1]=a[1][0]=-INF;
        c[0][0]=c[1][0]=col[0];
        c[0][1]=c[1][1]=col[1];
    }
    Path operator + (const Path& rhs)const
    {
        if(!c[0][0])return rhs;
        if(!rhs.c[0][0])return (*this);
        Path res;
        memcpy(res.c[0],c[0],sizeof(c[0]));
        memcpy(res.c[1],rhs.c[1],sizeof(rhs.c[1]));
        for(int i=0;i<2;i++)for(int j=0;j<2;j++)for(int k=0;k<2;k++)for(int l=0;l<2;l++)
            res.a[i][l]=max(res.a[i][l],a[i][j]+rhs.a[k][l]+(c[1][j]!=rhs.c[0][k]));
        return res;
    }
    Path rev()const
    {
        Path res=(*this);
        swap(res.a[0][1],res.a[1][0]);
        swap(res.c[0],res.c[1]);
        return res;
    }
    int res()const
    {
        return max({a[0][0],a[0][1],a[1][0],a[1][1]});
    }
};

Path pre[MAXN],seg[MAXN<<2];
void build(int l,int r,int n)
{
    if(l==r)
    {
        int u=loc[l],id=fa[u].second;
        seg[n]=Path(col[id]);
        return;
    }
    int m=(l+r)/2;
    build(l,m,n<<1);
    build(m+1,r,n<<1|1);
    seg[n]=seg[n<<1]+seg[n<<1|1];
}
Path query(int ql,int qr,int l,int r,int n)
{
    if(ql==l && qr==r)return seg[n];
    int m=(l+r)/2;
    if(qr<=m)return query(ql,qr,l,m,n<<1);
    if(ql>m)return query(ql,qr,m+1,r,n<<1|1);
    return query(ql,m,l,m,n<<1)+query(m+1,qr,m+1,r,n<<1|1);
}
Path query(int u,int v,int n)
{
    Path pu,pv;
    while(top[u]!=top[v])
    {
        if(dep[top[u]]>dep[top[v]])
        {
            pu=pre[dfn[u]]+pu;
            u=fa[top[u]].first;
        }
        else
        {
            pv=pre[dfn[v]]+pv;
            v=fa[top[v]].first;
        }
    }
    if(dep[u]<dep[v])
        pv=query(dfn[u]+1,dfn[v],1,n,1)+pv;
    else if(dep[u]>dep[v])
        pu=query(dfn[v]+1,dfn[u],1,n,1)+pu;
    return pu.rev()+pv;
}

int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    dsu.init(n);
    for(int i=1,ex=MAXM;i<=n;i++)
    {
        int u,v,k;
        scanf("%d%d%d",&u,&v,&k);
        if(dsu.merge(u,v))
        {
            e[u].emplace_back(v,i);
            e[v].emplace_back(u,i);
        }
        else extra.emplace_back(u,v,i);
        vector<int> c(k);
        for(int j=0;j<k;j++)
            scanf("%d",&c[j]);
        if(k==1)col[i][0]=col[i][1]=c[0];
        else if(k==2)col[i][0]=c[0],col[i][1]=c[1];
        else col[i][0]=col[i][1]=++ex;
    }
    assert(extra.size()==1u);
    dfs1(1,0);
    dfs2(1,1);
    for(int i=1;i<=n;i++)
    {
        int u=loc[i],id=fa[u].second;
        if(top[u]==u)pre[i]=Path(col[id]);
        else pre[i]=pre[i-1]+Path(col[id]);
    }
    build(1,n,1);
    for(int i=1;i<=q;i++)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        int res=query(a,b,n).res(),u,v,id;
        tie(u,v,id)=extra[0];
        if(!check(a,u,v,b))
            res=max(res,(query(a,u,n)+Path(col[id])+query(v,b,n)).res());
        if(!check(a,v,u,b))
            res=max(res,(query(a,v,n)+Path(col[id])+query(u,b,n)).res());
        printf("%d\n",res+1);
    }
    return 0;
}
