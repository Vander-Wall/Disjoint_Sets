/*
并查集 = 初始化 + 查找根节点+ 合并集合
用途： 1.维护无向图的连通性，支持判断两个点是否连在同一连通块内，和判断增加一条边后，是否会产生环
       2. 用在求最小生成树Kruskal算法里
*/



#include <stdio.h>
#include <set>

using namespace std;
#define maxn 10009

int pre[maxn]; // 比如pre[x]表示x的父亲节点
int Rank[maxn];//集合的层次
int data[maxn];

//初始化集合
void init(int n){  //对n个节点初始化,节点序号从0..n-1
    for(int i = 1;i <= n; i++){
        pre[i] = i; //  自己跟自己一个集合，因为它前面一个是它自己嘛
        Rank[i] = 1; // 每个节点构成的
    }
}


// 无路径压缩
int find_pre(int x){
    //如果x的爸爸是自己，那说明什么，自己就是自己的爸爸，自己是属于一个集合的
    if(pre[x] ==x)
        return x;
    //否则x的上头肯定有人了不，那就找pre(x)就好，pre就是上头的意思，前一个的意思，明白？
    return find_pre(pre[x]);
}
// 带路径压缩 adv means advanced
int find_pre_adv(int x){
    if(pre[x] == x){
        return x;
    }
    return pre[x] = find_pre_adv(pre[x]);
}

// 合并
void join(int x,int y){
    int rootx = find_pre_adv(x);
    int rooty = find_pre_adv(y);
    if(rootx == rooty)return;
    if(Rank[rootx] > Rank[rooty]){
        pre[rooty] = rootx;
    }
    if(Rank[rootx] == Rank[rooty]){
        Rank[y]++;
        pre[rootx] = rooty;
    }
    if(Rank[rootx] < Rank[rooty]){
        pre[rootx] = rooty;
    }

}

int main()
{
    int n,m;  // N : 1-N
    set<int> s;
    while(~scanf("%d",&n)){
        if(n==0)return 0;
    scanf("%d",&m);
        init(n);
        for(int i = 0;i < m; i++){
            int x,y;
            scanf("%d%d",&x,&y);
            join(x,y);
        }
        for(int i = 1;i <= n; i++){
            int tmp = find_pre_adv(pre[i]);
            s.insert(tmp);
        }
        printf("%d\n", s.size()-1);
        set<int>::iterator it;
        s.clear();
    }
    return 0;
}
