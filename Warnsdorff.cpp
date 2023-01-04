#include <bits/stdc++.h>
using namespace std;
const int dx[8]={-2,-2,2,2,1,-1,1,-1},dy[8]={1,-1,1,-1,-2,-2,2,2};
vector<vector<int> >G;
vector<int>vis,ans;
int N;
pair<int,int>PP[1000003];
int idx(int x,int y){
    return(x-1)*N+y;
}
int deg(int x){
    int ret=0;
    for(int y:G[x])ret+=vis[y]<=0;
    return ret;
}
void dfs(int x){
    if(vis[x]==N*N)return;
    int mn=2e9,mx=0,nxt=0;
    for(int y:G[x]){
        if(vis[y])continue;
        int DEG=deg(y),rrr=rand()%((int)1e9+7);;
        if(DEG<mn){
            mn=DEG;
            mx=rrr;
            nxt=y;
        }else if(DEG==mn&&mx<rrr){
            mx=rrr;
            nxt=y;
        }
    }
    vis[nxt]=vis[x]+1;
    ans.push_back(nxt);
    dfs(nxt);
}
int main(){
    cin>>N;
    int x0,y0;cin>>x0>>y0;
    if(N<5){
        cout<<"-1 -1";
        return 0;
    }
    G.resize(N*N+1);
    vis=vector<int>(N*N+1,0);
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            int v=idx(i,j);
            PP[v]={i,j};
            for(int k=0;k<8;k++){
                int x=dx[k]+i,y=dy[k]+j;
                if(x>0&&x<=N&&y>0&&y<=N){
                    int u=idx(x,y);
                    G[v].push_back(u);
                }
            }
        }
    }
    srand(time(NULL));
    int start=idx(x0,y0);
    cout<<x0<<" "<<y0<<"\n";
    vis[start]=1;
    dfs(start);
    for(int i:ans)cout<<PP[i].first<<" "<<PP[i].second<<"\n";
    return 0;
}
