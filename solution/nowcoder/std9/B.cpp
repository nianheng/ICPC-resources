#pragma GCC optimize(3)
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
#define per(i,r,l) for (int i = r,_ = l;i> _;i--)
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

const int maxn = 8000 + 5;
const int mod = 998244353;

int dp[maxn];
int n;
int a[maxn];
int b[maxn];

int power(int x, int y){
    int ret = 1;
    while (y){
        if (y & 1){
            ret = 1ll * ret * x % mod;
        }
        y >>= 1;
        x = 1ll * x * x % mod;
    }
    return ret;
}

int main(){
    scanf("%d",&n);
    for (int i = 1; i < n; i ++){
        scanf("%d", a+i);
        b[i] = power(a[i], mod - 2);
        a[i] = min(n, i + a[i]) + 1;
    }

    int tot = 0;
    int ans = 0;

    dp[1] = 1;

    rep(stp, 0, n){
        ans += 1ll * dp[n] * dp[n] % mod;
        if (ans >= mod) ans -= mod;
        tot += dp[n];
        if (tot >= mod) tot -= mod;
        dp[n] = 0;
        per (cur, n-1, 0){
            int delta = 1ll * dp[cur] * b[cur] % mod;
            dp[a[cur]] -= delta;
            if (dp[a[cur]] < 0) dp[a[cur]] += mod;
            dp[cur + 1] += delta;
            if (dp[cur + 1] >= mod) dp[cur + 1] -= mod;
            dp[cur] = 0;
        }
        REP(i, 1, n) {
            dp[i] += dp[i-1];
            if (dp[i] >= mod) dp[i] -= mod;
        }
    }

    cout<< ans << endl;

    return 0;
}