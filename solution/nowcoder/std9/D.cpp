#include <cstdio>
#include <algorithm>
using namespace std;
#define N 1000 + 5

int n, m, Ans[N][N];
bool flip;

int main()
{
	scanf("%d%d", &n, &m);
	if (n > m)
		swap(n, m), flip = true;
	if (n == 2)
	{
		Ans[1][1] = 2, Ans[1][2] = 1;
		Ans[2][1] = 3, Ans[2][2] = 4;
		int a = 2, b = 1;
		for (int j = 3; j * 2 <= m; j ++)
		{
			Ans[a][j] = j * 2 - 1;
			Ans[b][j] = j * 2;
			swap(a, b);
		}
		if (m >= 4)
		{
			for (int j = m / 2 + 1; j <= m; j ++)
				Ans[a][j] = m / 2 + j;
			for (int j = m; j > m / 2; j --)
				Ans[b][j] = 2 * m + m / 2 + 1 - j;
		}
	}
	else
	{
		bool flag = false;
		if (n % 4 != 0)
			n -= 2, flag = true;
		int id = 0;
		for (int i = n; i; i --)
			Ans[i][1] = ++ id;
		for (int i = 1; i <= n; i += 4)
		{
			for (int j = 2; j <= m; j ++)
				Ans[i][j] = ++ id;
			for (int j = m; j >= 2; j --)
				Ans[i + 1][j] = ++ id;
			int a = 2, b = 3;
			for (int j = 2; j <= m; j ++)
			{
				Ans[i + a][j] = ++ id;
				Ans[i + b][j] = ++ id;
				swap(a, b);
			}
			if (i % 8 == 5)
			{
				reverse(Ans[i] + 2, Ans[i] + m + 1);
				reverse(Ans[i + 1] + 2, Ans[i + 1] + m + 1);
				reverse(Ans[i + 2] + 2, Ans[i + 2] + m + 1);
				reverse(Ans[i + 3] + 2, Ans[i + 3] + m + 1);
			}
		}
		if (flag)
		{
			n += 2;
			if (n % 8 == 6)
			{
				for (int i = 1; i <= n - 2; i ++)
					for (int j = 1; j <= m; j ++)
						Ans[i][j] += 4;
				Ans[n - 1][1] = 4, Ans[n - 1][2] = 3;
				Ans[n][1] = 1, Ans[n][2] = 2;
				int a = n - 1, b = n, id = (n - 2) * m + 4, j = m;
				for (int ret = m - 3; ret > 2; j --)
				{
					Ans[a][j] = ++ id;
					Ans[b][j] = ++ id;
					swap(a, b);
					ret -= (j == m ? 1 : 2);
				}
				for (int _j = j; _j >= 3; _j --)
					Ans[a][_j] = ++ id;
				for (int _j = 3; _j <= j; _j ++)
					Ans[b][_j] = ++ id;
			}
			else
			{
				for (int i = 1; i <= n - 2; i ++)
					for (int j = 1; j <= m; j ++)
						Ans[i][j] += 3;
				int id = (n - 2) * m + 3;
				Ans[n - 1][1] = 3, Ans[n - 1][2] = ++ id;
				Ans[n][1] = 2, Ans[n][2] = 1;
				int a = n - 1, b = n, j = 3;
				for (int ret = m - 2; ret > 2; j ++)
				{
					Ans[a][j] = ++ id;
					Ans[b][j] = ++ id;
					swap(a, b);
					ret -= 2;
				}
				for (int _j = j; _j <= m; _j ++)
					Ans[a][_j] = ++ id;
				for (int _j = m; _j >= j; _j --)
					Ans[b][_j] = ++ id;
			}
		}
	}
	if (flip)
	{
		for (int i = 1; i <= m; i ++)
			for (int j = 1; j < i; j ++)
				swap(Ans[i][j], Ans[j][i]);
		swap(n, m);
	}
	puts("Yes");
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
			printf("%d%c", Ans[i][j], j == m ? '\n' : ' ');
	return 0;
}