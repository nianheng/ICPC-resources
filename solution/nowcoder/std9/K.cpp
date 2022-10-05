#include <bits/stdc++.h>
using namespace std;
#ifdef __LOCAL_DEBUG__
# define _debug(fmt, ...) fprintf(stderr, "\033[91m[%s %3d]: " fmt "\n\033[0m", \
  __func__,__LINE__, ##__VA_ARGS__)
#else
# define _debug(...) (void(0))
#endif
#define PB(x) push_back(x)
#define rep(i,l,r) for (int i = l,_ = r;i< _;i++)
#define REP(i,l,r) for (int i=l,_=r;i<=_;i++)
#define leave(x) do {cout<<#x<<endl;fflush(stdout);return 0;}while (0);
#define untie do{ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);}while (0)
#define range(x) x.begin(),x.end()
typedef long long LL;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef long double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int inf = 0x3f3f3f3f;
const ll inf_ll = 0x3f3f3f3f3f3f3f3fLL;
mt19937 wdy(time(0));
/************* header ******************/

const int maxn = (1 << 20) + 5;

int ans[maxn];
int f[maxn],g[maxn];
void FMT(int *f, int n, int op) // op=1为正变换，op=-1为逆变换
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < (1 << n); ++j)
            if (j & (1 << i))
                f[j] += f[j ^ (1 << i)] * op;
}

int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    for (int i = 1; i <= n; i ++){
        int m;
        scanf("%d",&m);
        int mask = 0;
        while (m--){
            int c;
            scanf("%d",&c);
            c--;
            mask |= (1 << c);
        }
        ans[mask] = f[mask] = g[mask] = 1;
    }
    FMT(g, k, 1);

    for (int i = 2; i <= k; i ++){
        FMT(f, k, 1);
        for (int j = 0; j < (1 << k); j ++){
            f[j] *= g[j];
        }
        FMT(f, k, -1);
        int cnt = 0;
        for (int j = 0; j < (1 << k); j ++){
            if (f[j]){
                f[j] = 1;
                if (ans[j] == 0){
                    ans[j] = i;
                }
                cnt ++;
            }
        }
        if (!cnt)break;
    }

    vector<int> count(k + 1);
    for (int mask = (1 << k) - 1; mask > 0; mask--){
        count[ans[mask]]++;
        if (ans[mask] == 0)continue;
        for (int i = 0; i < k; i++){
            if ((mask >> i) & 1){
                int mask2 = mask ^ (1 << i);
                ans[mask2] = min(ans[mask2], ans[mask]);
                if (ans[mask2] == 0)
                    ans[mask2] = ans[mask];
            }
        }
    }

    for (int i = 1; i <= k; i++){
        cout << count[i];
        if (i != k) cout << " ";
        else cout << endl;
    }
    return 0;
}