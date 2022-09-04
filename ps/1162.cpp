#include<cstdio>
#include<vector>
#include<queue>
#include<utility>

#define N 10004
#define M 50004
#define K 20
#define INF 10000000000     //10^10
using namespace std;
typedef pair<int,int> P;
typedef pair<long long,int> NODE;

vector<P> adj[N+1];
long long length[N+1][K+1];
bool visited[N+1];

int main(){
    int n, m, k;
    scanf("%d %d %d",&n, &m, &k);
    
    int u, v, w;
    for(int i=0; i<m; i++){
        scanf("%d %d %d", &u, &v, &w);
        adj[u].push_back(P(v,w));
        adj[v].push_back(P(u,w));
    }

    //dijsktra
    priority_queue<NODE, vector<NODE>, greater<NODE>> PQ;
    int cur;
    int newlength;
    bool renewed;
    for(int cnt=0; cnt<k+1; cnt++){
        for(int i=1; i<n+1; i++){
            length[i][cnt] = INF;
            visited[i] = false;
        }
        length[1][cnt] = 0;
        PQ.push(NODE(0, 1));

        while(!PQ.empty()){
            do{
                cur = PQ.top().second;
                PQ.pop();
            }while(!PQ.empty()&&visited[cur]);
            if(visited[cur])
                break;

            visited[cur] = true;
            for(P i: adj[cur]){
                renewed = false;
                if(length[cur][cnt] + i.second < length[i.first][cnt]){
                    length[i.first][cnt] = length[cur][cnt] + i.second;
                    renewed = true;
                }
                if((cnt > 0) && (length[cur][cnt-1] < length[i.first][cnt])){
                    length[i.first][cnt] = length[cur][cnt-1];
                    renewed = true;
                }
                if(renewed)
                    PQ.push(NODE(length[i.first][cnt], i.first));
            }
        }
    }

    printf("%lld\n",length[n][k]);
}