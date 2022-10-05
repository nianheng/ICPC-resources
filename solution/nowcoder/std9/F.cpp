#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
#define N 1000 + 5
#define M (N) * (N)

int n, m, prod, sz, Pos[M], P[M], A[N][N], Id[N][N], Up[N][N], Stack[N][2];
LL ans, Cnt[M];

inline LL Get(int k)
{
	int cnt = 0;
	LL ret = 0;
	if (k <= 20)
	{
		cnt = prod;
		for (int i = k, x, y; i <= prod; i += k)
		{
			x = (Pos[i] - 1) / m + 1, y = Pos[i] - (x - 1) * m;
			Id[x][y] = k;
		}
	}
	else
	{
		for (int i = k; i <= prod; i += k)
			P[cnt ++] = Pos[i];
		sort(P, P + cnt);
	}
	for (int i = 0, x = 1, y = 0; i <= cnt; i ++)
	{
		if (i < cnt)
		{
			if (k <= 20)
			{
				x = y == m ? x + 1 : x;
				y = y == m ? 1 : y + 1;
				if (i < cnt && Id[x][y] != k)
					continue ;
			}
			else
			{
				x = (P[i] - 1) / m + 1, y = P[i] - (x - 1) * m;
				Id[x][y] = k;
			}
			Up[x][y] = Id[x - 1][y] == k ? Up[x - 1][y] + 1 : 1;
		}
		if (i == cnt || Id[x][y - 1] != k)
		{
			for (int mx = Stack[sz][0]; sz; sz --)
			{
				int l = mx - Stack[sz - 1][0];
				int h = Stack[sz][1] - Stack[sz - 1][1];
				ret += (LL) (l * (l + 1) / 2) * h;
			}
			sz = 1;
			Stack[sz][0] = y - 1, Stack[sz][1] = 0;
		}
		if (i == cnt)
			break ;
		for (int mx = Stack[sz][0]; sz && Stack[sz][1] >= Up[x][y]; sz --)
		{
			int l = mx - Stack[sz - 1][0];
			int h = Stack[sz][1] - max(Stack[sz - 1][1], Up[x][y]);
			ret += (LL) (l * (l + 1) / 2) * h;
			if (Stack[sz - 1][1] >= Up[x][y])
				Stack[sz - 1][0] = Stack[sz][0];
		}
		sz ++;
		Stack[sz][0] = y, Stack[sz][1] = Up[x][y];
	}
	return ret;
}

int main()
{
	scanf("%d%d", &n, &m);
	prod = n * m;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
		{
			scanf("%d", A[i] + j);
			Pos[A[i][j]] = (i - 1) * m + j;
		}
	for (int i = 1; i <= prod; i ++)
		Cnt[i] = Get(i);
	for (int i = prod; i; i --)
		for (int j = i * 2; j <= prod; j += i)
			Cnt[i] -= Cnt[j];
	for (int i = 1; i <= prod; i ++)
		ans += Cnt[i] * i;
	printf("%lld\n", ans);
	return 0;
}