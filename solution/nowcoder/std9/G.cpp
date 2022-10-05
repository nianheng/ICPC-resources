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
typedef unsigned long long ULL;
const int inf = 0x3f3f3f3f;
const ll inf_ll = 0x3f3f3f3f3f3f3f3fLL;
mt19937 wdy(time(0));
/************* header ******************/

const int maxn = 600'000 + 5;
const ULL mod = 1000000007;
const ULL mod2 = 998244353;
const ULL base = 146;
ULL Sum1[maxn], Pow1[maxn];
ULL Sum2[maxn], Pow2[maxn];
char s[maxn];
char ch[maxn];
int N;
int r[maxn];
map<pair<ULL,ULL>, int> P;
int F = 0;
inline pair<ULL,ULL> get_hash(int l, int r){
    ULL hash1 = (Sum1[r] - Sum1[l-1] * Pow1[r - l + 1] % mod + mod) % mod;
    ULL hash2 = (Sum2[r] - Sum2[l-1] * Pow2[r - l + 1] % mod2 + mod2) % mod2;
    return {hash1, hash2};
}

/* s 1 bas */
void init(char *s){
    int n = strlen(s + 1);
    ch[n * 2 + 1] = '#';
    ch[0] = '@';
    ch[n * 2 + 2] = '\0';
    Sum1[0] = Sum2[0] =  0;
    for (int i = 1; i <=n; i++){
        Sum1[i] = (Sum1[i-1] * base % mod + s[i]) % mod;
        Sum2[i] = (Sum2[i-1] * base % mod2 + s[i]) % mod2;
        ch[i * 2] = s[i];
        ch[i * 2 - 1] = '#';
    }
    N = 2 * n + 1;

   // cerr<<ch+1<<endl;
   // cerr<<N<<endl;
}
void manacher(){
    F++;
    r[1] = 1;
    int k = 1;
    for (int i = 2; i <= N; i++){
        int p = k + r[k] - 1;
        if (i <= p){
            r[i] = min(r[2 * k - i], p - i + 1);
        }else{
            r[i] = 1;
        }
        while (ch[i + r[i]] == ch[i - r[i]])r[i]++;
        if (i + r[i] > k + r[k]){
            for (int R = k + r[k] + 1;R <= i + r[i]; R ++){
                int L = 2 * i - R;
                if (ch[R] == '#'){
                    pair<ULL,ULL> hashvalue = get_hash(L/2+1, R/2);
                    if (F > 1 && P.find(hashvalue) == P.end()) continue;
                    if (F > 1 && P[hashvalue] < F - 1){
                        P.erase(hashvalue);
                        continue;
                    }
                    if (P[hashvalue] == F) continue;
                //    cerr<< L/2+1<<" "<<R/2<<endl;
                    P[hashvalue] = F;
                }
            }
            k = i;

        }
    }
}

int main(){
 Pow1[0] = Pow2[0] = 1;
    for (int i = 1; i <= 300000; i ++){
        Pow1[i] = Pow1[i-1] * base % mod;
        Pow2[i] = Pow2[i-1] * base % mod2;
    }
    int K;
    scanf("%d",&K);
    for (int i = 1; i <= K; i++){
        scanf("%s", s + 1);
        init(s);
        manacher();
    }
    int ans = 0;
    for (auto pr : P){
        if (pr.second== F) ans++;
    }
    cout<<ans<<endl;
    return 0;
}