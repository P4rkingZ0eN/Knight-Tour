#include <bits/stdc++.h>
using namespace std;
const int dx[8]={-2,-2,2,2,1,-1,1,-1},dy[8]={1,-1,1,-1,-2,-2,2,2};
vector<vector<int> >G,H;
vector<int>vis,ans;
int N,K=0;
pair<int,int>PP[1000003];
int idx(int x,int y,int m){
    return(x-1)*m+y;
}
int last;
int deg(int x){
    int ret=0;
    for(int y:G[x])ret+=vis[y]<=0;
    return ret;
}
int cnt=0,ne,me;
void dfs(int x){
    if(vis[x]==ne*me){
        last=x;
        return;
    }
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
    if(nxt==0){
        cout<<"fail\n";
        return;
    }
    vis[nxt]=vis[x]+1;
    H[x+K].push_back(nxt+K);
    H[nxt+K].push_back(x+K);
    dfs(nxt);
}
pair<int,int>A,B,C,D;
int g(int x,int y){
    if(x==A.first&&y==A.second)return B.first;
    if(x==B.first&&y==B.second)return D.first;
    if(x==C.first&&y==C.second)return D.second;
    if(x==D.first&&y==D.second)return C.second;
    if(y==A.first&&x==A.second)return C.first;
    if(y==B.first&&x==B.second)return A.second;
    if(y==C.first&&x==C.second)return A.first;
    if(y==D.first&&x==D.second)return B.second;
    return y;
}
void _DFS(int x){
    cout<<PP[x].first<<" "<<PP[x].second<<"\n";
    for(int y:H[x]){
        y=g(x,y);
        if(vis[y])continue;
        vis[y]=vis[x]+1;
        _DFS(y);
    }
}
void subP(int n,int m,int nn,int mm){
    ne=n,me=m;
    G.clear();G.resize(n*m+3);
    vis=vector<int>(n*m+1,0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int v=idx(i,j,m);
            PP[v+K]={i+nn,j+mm};
            for(int k=0;k<8;k++){
                int x=dx[k]+i,y=dy[k]+j;
                if(x>0&&x<=n&&y>0&&y<=m){
                    int u=idx(x,y,m);
                    G[v].push_back(u);
                }
            }
        }
    }
    dfs(1);
    H[last+K].push_back(1+K);
    H[1+K].push_back(last+K);
    K+=n*m;
}

int main(){
    freopen("input.txt","r",stdin);
    //ios_base::sync_with_stdio(false);cin.tie(NULL);
    cin>>N;
    H.resize(N*N+1);
    int x0,y0;cin>>x0>>y0;
    if(N<5&&N&1){
        cout<<"No closed tours.";
        return 0;
    }
    srand(time(NULL));
    if(N<100){
        subP(N,N,0,0);
        vis=vector<int>(N*N+1,0);vis[idx(x0,y0,N)]=1;
        _DFS(idx(x0,y0,N));
        return 0;
    }else{
        subP(N/2-2,N/2+2,0,0);A={(N/2-2)*(N/2+2),(N/2-4)*(N/2+2)-1};B={K,K};
        subP(N/2-2,N/2-2,0,N/2+2);B={B.first+(N/2-4)*(N/2-2)+1,B.second+(N/2-3)*(N/2-2)+3};C={K,K};
        subP(N/2+2,N/2+2,N/2-2,0);C={C.first+N/2,C.second+N+4};D={K,K};
        subP(N/2+2,N/2-2,N/2-2,N/2+2);D={D.first+1,D.second+(N/2-2)*2+2};
        vis=vector<int>(N*N+1,0);vis[idx(x0,y0,N)]=1;
        _DFS(idx(x0,y0,N));
    }
    return 0;
}
/*
  input__
  N
  x0 y0
  ________
  
  N is length of chessboard.
  (x0, y0) is the starting point.
*/
