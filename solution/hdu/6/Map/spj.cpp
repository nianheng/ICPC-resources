#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<ctype.h>
#include<math.h>
#include<set>
#include<map>
#include<vector>
#include<queue>
#include<bitset>
#include<algorithm>
#include<time.h>
using namespace std;
double ans[200000] =
{
};
int tt;
void WA()
{
  printf("%d\n", tt);
	puts("WA");
	exit(0);
}
void AC()
{
	char trash[1000];
	if (scanf("%s", trash) != -1) {
		WA();
	}
	else {
		puts("AC");
		exit(0);
	}
}
const double eps = 1e-6;
bool ok1(double x, double y) {
	return fabs(x - y) < eps;
}
int main() {
  #ifdef Sakuyalove
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
  #endif
  int T = 200000;
  for (tt = 0; tt < T; tt++) {
    double Ans;
    if (scanf("%lf", &Ans) != 1) WA();
    if (!ok1(ans[tt], Ans)) WA();
  }
  AC();
	return 0;
}