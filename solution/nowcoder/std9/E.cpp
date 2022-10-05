#include<bits/stdc++.h>
using namespace std;
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int m;
		scanf("%d",&m);
		int len=32-__builtin_clz(m);
		vector<int> cnt(len);
		for(int i=0,la=-1;i<len;i++)
		{
			if(m>>i&1)cnt[la=i]++;
			else if(la>=0)cnt[la]++;
		}
		vector<int> res;
		int low=0,high=2*len-2;
		for(int i=0;i<len;i++)
		{
			if(i>0)res.push_back(low+2),res.push_back(low+1),low+=2;
			for(int j=0;j<cnt[i];j++)res.push_back(++high);
		}
		printf("%zu\n",res.size());
		for(size_t i=0;i<res.size();i++)
			printf("%d%c",res[i]," \n"[i+1==res.size()]);
	}
	return 0;
}