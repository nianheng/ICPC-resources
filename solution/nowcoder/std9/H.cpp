#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point
{
    ll x,y;
    Point() {}
    Point(ll _x,ll _y):x(_x),y(_y) {}
    Point operator - (const Point& t)const
    {
        return Point(x-t.x,y-t.y);
    }
    ll operator * (const Point& t)const
    {
        return x*t.y-y*t.x;
    }
    ll operator ^ (const Point& t)const
    {
        return x*t.x+y*t.y;
    }
    bool operator < (const Point& t)const
    {
        return x==t.x ? y<t.y : x<t.x;
    }
    bool operator == (const Point& t)const
    {
        return x==t.x && y==t.y;
    }
};
bool cmp(const Point& a,const Point &b)
{
    bool up[2]={a.y>0 || (a.y==0 && a.x>0),b.y>0 || (b.y==0 && b.x>0)};
    return up[0]^up[1] ? up[0] : a*b>0;
}
bool cmp_strict(const Point& a,const Point &b)
{
    bool up[2]={a.y>0 || (a.y==0 && a.x>0),b.y>0 || (b.y==0 && b.x>0)};
    return up[0]^up[1] ? up[0] : (a*b==0 ? (a^a)<(b^b) : a*b>0);
}

struct Line
{
    Point s,d;
    Line(){}
    Line(Point _s, Point _d):s(_s),d(_d){}
};

template<typename T>
class vector_view
{
public:
    vector_view(const vector<T>& _v,int _rev=0):rev(_rev),v(_v){}
    const T& operator [] (size_t n)const
    {
        return rev ? v[v.size()-1-n] : v[n];
    }
    size_t size()const
    {
        return v.size();
    }
private:
    int rev;
    const vector<T>& v;
};

pair<size_t,size_t> tangent(vector_view<Point> lef, vector_view<Point> rig, Line split, int sgn)
{
    size_t lef_l=0,lef_r=lef.size()-1,rig_l=0,rig_r=rig.size()-1;
    while(lef_l<lef_r && rig_l<rig_r)
    {
        size_t lef_m=(lef_l+lef_r)/2,rig_m=(rig_l+rig_r)/2;
        Point a=lef[lef_m],b=lef[lef_m+1],c=rig[rig_m],d=rig[rig_m+1];
        if((b-a)*(c-a)*sgn>=0 || (b-a)*(d-a)*sgn>=0)lef_r=lef_m;
        else if((c-a)*(d-a)*sgn>=0 || (c-b)*(d-b)*sgn>=0)rig_l=rig_m+1;
        else
        {
            if((b-a)*split.d<=0)lef_l=lef_m+1;
            else if((d-c)*split.d<=0)rig_r=rig_m;
            else
            {
                __int128 lef_s=(__int128)((b-a)*(b-split.s))*((d-c)*split.d);
                __int128 rig_s=(__int128)((d-c)*(d-split.s))*((b-a)*split.d);
                if((lef_s-rig_s)*sgn>=0)lef_l=lef_m+1;
                else rig_r=rig_m;
            }
        }
    }
    while(lef_l<lef_r)
    {
        size_t lef_m=(lef_l+lef_r)/2;
        Point a=lef[lef_m],b=lef[lef_m+1],c=rig[rig_l];
        if((b-a)*(c-a)*sgn>=0)lef_r=lef_m;
        else lef_l=lef_m+1;
    }
    while(rig_l<rig_r)
    {
        size_t rig_m=(rig_l+rig_r)/2;
        Point b=lef[lef_l],c=rig[rig_m],d=rig[rig_m+1];
        if((c-b)*(d-b)*sgn>=0)rig_l=rig_m+1;
        else rig_r=rig_m;
    }
    return {lef_l,rig_l};
}

class ConvexHull
{
public:
    ConvexHull(int _sgn):sgn(_sgn){}
    void push(const Point& p)
    {
        all[1].push_back(p);
        while(hull[1].size()>1u && (p-hull[1].back())*(p-hull[1][hull[1].size()-2])*sgn>=0)
            hull[1].pop_back(),sum[1].pop_back();
        sum[1].push_back(sum[1].empty() ? 0 : sum[1].back()+hull[1].back()*p);
        hull[1].push_back(p);
    }
    void pop()
    {
        if(all[0].empty())
        {
            hull[1].clear();
            sum[1].clear();
            while(!all[1].empty())
            {
                Point p=all[1].back();
                all[1].pop_back();
                all[0].push_back(p);
                r_hull.emplace_back();
                r_sum.emplace_back();
                while(hull[0].size()>1u && (p-hull[0].back())*(p-hull[0][hull[0].size()-2])*sgn<=0)
                {
                    r_hull.back().push_back(hull[0].back()),hull[0].pop_back();
                    r_sum.back().push_back(sum[0].back()),sum[0].pop_back();
                }
                reverse(r_hull.back().begin(),r_hull.back().end());
                reverse(r_sum.back().begin(),r_sum.back().end());
                sum[0].push_back(sum[0].empty() ? 0 : sum[0].back()+p*hull[0].back());
                hull[0].push_back(p);
            }
        }
        all[0].pop_back();
        hull[0].pop_back();
        hull[0].insert(hull[0].end(),r_hull.back().begin(),r_hull.back().end());
        r_hull.pop_back();
        sum[0].pop_back();
        sum[0].insert(sum[0].end(),r_sum.back().begin(),r_sum.back().end());
        r_sum.pop_back();
    }
    ll query()
    {
        if(hull[0].empty() && hull[1].empty())return 0;
        if(hull[0].empty())return sum[1].back();
        if(hull[1].empty())return sum[0].back();
        pair<size_t,size_t> ct=tangent(vector_view<Point>(hull[1],1),hull[0],Line(Point(0,0),hull[1].front()),sgn);
        size_t c[2]={ct.second,hull[1].size()-1-ct.first};
        return (sum[0].back()-sum[0][c[0]])+(sum[1].back()-sum[1][c[1]])+hull[0][c[0]]*hull[1][c[1]];
    }
private:
    int sgn;
    vector<Point> hull[2],all[2];
    vector<vector<Point>> r_hull;
    vector<ll> sum[2];
    vector<vector<ll>> r_sum;
};
void solve(const vector<Point>& target,const vector<pair<int,int>>& radar)
{
    vector<int> idx(radar.size());
    iota(idx.begin(),idx.end(),0);
    sort(idx.begin(),idx.end(),[&](int i,int j){
        return radar[i]<radar[j];
    });
    vector<ll> res(radar.size());
    ConvexHull up(1),dw(-1);
    int l=0,r=0;
    for(auto i : idx)
    {
        while(r<radar[i].second)
            up.push(target[r]),dw.push(target[r]),r++;
        while(l<radar[i].first)
            up.pop(),dw.pop(),l++;
        res[i]=up.query()-dw.query();
    }
    for(auto r : res)
        printf("%lld\n",r);
}

int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    vector<Point> target;
    for(int i=0;i<n;i++)
    {
        ll x,y;
        scanf("%lld%lld",&x,&y);
        if(x||y)target.emplace_back(x,y);
    }
    sort(target.begin(),target.end(),cmp_strict);
    target.erase(unique(target.begin(),target.end()),target.end());
    vector<pair<int,int>> radar;
    for(int i=0;i<q;i++)
    {
        ll a,b;
        scanf("%lld%lld",&a,&b);
        int l=upper_bound(target.begin(),target.end(),Point(b,-a),cmp)-target.begin();
        int r=lower_bound(target.begin(),target.end(),Point(-b,a),cmp)-target.begin();
        while(l>r || (l==r && (target[l%target.size()]^Point(a,b))>0))r+=target.size();
        radar.emplace_back(l,r);
    }
    target.insert(target.end(),target.begin(),target.end());
    solve(target,radar);
    return 0;
}
