#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
const int MAXN=8005;
const int INF=0x3f3f3f3f;
struct Node
{
    int v,dp,mi;
    Node(){}
    Node(int _v,int _dp,int _mi):v(_v),dp(_dp),mi(_mi){}
}stk[MAXN];
int a[MAXN],dp[2][MAXN],top;
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1; i<=n; i++)
        scanf("%d",&a[i]);
    int now=0,la=1;
    for(int i=0; i<=n; i++)
        dp[now][i]=INF*(i>0);
    for(int k=1; k<=n; k++)
    {
        swap(now,la);
        for(int i=0; i<=n; i++)
            dp[now][i]=INF;
        stk[top=0]=Node(INF,INF,INF);
        for(int i=1; i<=n; i++)
        {
            int mdp=dp[la][i-1];
            while(stk[top].v<=a[i])
                mdp=min(mdp,stk[top].dp),top--;
            stk[top+1]=Node(a[i],mdp,min(stk[top].mi,mdp+a[i])),++top;
            dp[now][i]=stk[top].mi;
        }
        printf("%d\n",dp[now][n]);
    }
    return 0;
}
