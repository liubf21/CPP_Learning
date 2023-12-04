#include<algorithm>
#include<string>
using std::max;
using std::min;

const int MaxK = 3;
const int MaxN = 100000;
struct  KDTree_Node
{
    int d[MaxK]; // coordinate
    int s[2]; // left and right son, 0 for empty
    int x[2],y[2],z[2]; // bounding box
}t[MaxN];

int D; // current dimension
struct P
{
    int d[3]; // coordinate
    bool operator<(const P &b) const
    {
        return d[D] < b.d[D];
    }
}a[MaxN]; // all points

#define cmin(a,b) (a<b?a=b:a) // a = min(a,b)
#define cmax(a,b) (a>b?a=b:a)
#define ls t[o].s[0]
#define rs t[o].s[1]

void mt(int f,int x){ // maintain(f = father, x = son)
    cmin(t[f].x[0],t[x].x[0]),cmax(t[f].x[1],t[x].x[1]);
    cmin(t[f].y[0],t[x].y[0]),cmax(t[f].y[1],t[x].y[1]);
    cmin(t[f].z[0],t[x].z[0]),cmax(t[f].z[1],t[x].z[1]);
}

int bt(int l, int r,int d){ // build_tree
    D=d; int o=(l+r)>>1; // o = median
    std::nth_element(a+l,a+o,a+r+1); // sort(a+l,a+r+1) -> a[o]
    t[o].d[0]=t[o].x[0]=t[o].x[1]=a[o].d[0];
    t[o].d[1]=t[o].y[0]=t[o].y[1]=a[o].d[1];
    t[o].d[2]=t[o].z[0]=t[o].z[1]=a[o].d[2];
    if(l<o) ls=bt(l,o-1,(d+1)%3),mt(o,ls); // use recursion
    if(r>o) rs=bt(o+1,r,(d+1)%3),mt(o,rs);
    return o;
}

#define oo 2147483647
#define getdist(p) max(t[p].x[0]-x,0)+max(x-t[p].x[1],0)\
+max(t[p].y[0]-y,0)+max(y-t[p].y[1],0)

int x,y,z;
int ans;
void query(int o){
int tmp=abs(t[o].d[0]-x)+abs(t[o].d[1]-y),d[2]; // tmp = dist(o,x,y)
if(ls)d[0]=getdist(ls);else d[0]=oo; // d[0] = dist(ls,x,y)
if(rs)d[1]=getdist(rs);else d[1]=oo; // d[1] = dist(rs,x,y)
cmin(ans,tmp);tmp=d[0]>=d[1]; // ans = min(ans,tmp), find the nearer son
if(d[tmp]<ans)query(t[o].s[tmp]);tmp^=1; 
if(d[tmp]<ans)query(t[o].s[tmp]);
}

int main(){
    int n; scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d%d%d",&a[i].d[0],&a[i].d[1],&a[i].d[2]);
    int root=bt(1,n,0);

    int x,y,z;
    std::string command;
    if(command=="Insert")// (x,y,z)
    {
        n++;scanf("%d%d%d",&x,&y,&z);
        t[n].d[0]=t[n].x[0]=t[n].x[1]=x;
        t[n].d[1]=t[n].y[0]=t[n].y[1]=y;
        t[n].d[2]=t[n].z[0]=t[n].z[1]=z;
        for(int p=root,D=0;p;D=(D+1)%3){
            mt(p,n);
            int&nxt=t[p].s[t[n].d[D]>=t[p].d[D]];// go to the son
            if(nxt==0){nxt=n;return;}else p=nxt; // find the place to insert
        }
/*
• 也可以在一开始把所有操作读进来，进行预处理
• 给 K-D Tree 上的每个节点打一个标记，表示该点是否被激活
• 插入时只需找到该点并修改标记即可
*/
    }
    else if(command=="Delete")// (x,y,z)
    {

    }
    else if(command=="Search")// (x1,y1,z1) (x2,y2,z2
    {

    } 
    return 0;
}

/*
int n,m,op,x,y,i,dd,rt,ans;
struct T{int d[2],s[2],x[2],y[2];}t[1<<20];
struct P{int d[2];}a[1<<19];
bool operator<(const P&a,const P&b){return a.d[dd]<b.d[dd]||a.d[dd]==b.d[dd]&&a.d[dd^1]<b.d[dd^1];}
#define abs(x) (x>0?x:-(x))
#define max(a,b) (a>b?a:b)
#define cmax(a,b) (a<b?a=b:a)
#define cmin(a,b) (a>b?a=b:a)
#define ls t[now].s[0]
#define rs t[now].s[1]
void mt(int f,int x){
    cmin(t[f].x[0],t[x].x[0]),cmax(t[f].x[1],t[x].x[1]);
    cmin(t[f].y[0],t[x].y[0]),cmax(t[f].y[1],t[x].y[1]);
}
int bt(int l,int r,int d){
    dd=d;int now=l+r>>1;
    std::nth_element(a+l,a+now,a+r+1);
    t[now].d[0]=t[now].x[0]=t[now].x[1]=a[now].d[0];
    t[now].d[1]=t[now].y[0]=t[now].y[1]=a[now].d[1];
    if(l<now)ls=bt(l,now-1,d^1),mt(now,ls);
    if(now<r)rs=bt(now+1,r,d^1),mt(now,rs);
    return now;
}
int getdis(int p){
    return max(t[p].x[0]-x,0)+max(x-t[p].x[1],0)+max(t[p].y[0]-y,0)+max(y-t[p].y[1],0);
}
void ins(int n){
    for(int p=rt,dd=0;p;dd^=1){
        mt(p,n);int&nx=t[p].s[t[n].d[dd]>=t[p].d[dd]];
        if(nx==0){nx=n;return;}else p=nx;
    }
}
void query(int now){
    int d[2]={1<<30,1<<30},d0=abs(t[now].d[0]-x)+abs(t[now].d[1]-y),p;
    if(ls)d[0]=getdis(ls);if(rs)d[1]=getdis(rs);p=d[0]>=d[1];cmin(ans,d0);
    if(d[p]<ans)query(t[now].s[p]);
    if(d[p^1]<ans)query(t[now].s[p^1]);
*/