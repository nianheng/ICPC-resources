#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
#define N 100000 + 5

int n, m, cnt, T[N], Cnt[N];
LL ans;

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++)
		scanf("%d", T + i);
	for (int l = 1, r = 0; l <= n; l ++)
	{
		while (r <= n && cnt != m)
		{
			if (++ r > n)
				break;
			if (!Cnt[T[r]])
				cnt ++;
			Cnt[T[r]] ++;
		}
		ans += n + 1 - r;
		if (Cnt[T[l]] == 1)
			cnt --;
		Cnt[T[l]] --;
	}
	printf("%lld\n", ans);
	return 0;
}
