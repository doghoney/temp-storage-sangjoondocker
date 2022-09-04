#include <cstdio>

#define N 102
#define M 20004
#define INF 200005      //if start at -100005 : none starting path can get renewed

typedef struct{
    int u;
    int v;
    int weight;
}Edge;

Edge edge[M];
int dist[N+1];
int pre[N+1];
bool cycle[N+1];

int main(){
    int n, m;
    Edge e;

    scanf("%d %d",&n, &m);
    
    for(int i=0; i<m; i++){
        scanf("%d %d %d",&edge[i].u, &edge[i].v, &edge[i].weight);
    }

    //init
    for(int i=1; i<n+1; i++){   
        dist[i] = -INF;
        pre[i] = 0;         //vertex's idx start from 1
        cycle[i] = 0;
    }
    dist[1] = 0;
    pre[1] = -1;
    
    //bellman-ford
    for(int i=0; i<n-1; i++){
        for(int j=0; j<m; j++){
           e = edge[j];
           if(dist[e.u]+e.weight>dist[e.v]){
            //    printf("[%d][%d][%d,%d] : %d+%d>%d\n",i,j,e.u,e.v,dist[e.u],e.weight, dist[e.v]);
               dist[e.v] = dist[e.u]+e.weight;
               pre[e.v] = e.u;
           }
        }
    }

    //check cycle
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            e = edge[j];
            if(dist[e.u]+e.weight>dist[e.v]){
                dist[e.v] = INF;
                cycle[e.v] = 1;
            }
        }
    }

    // for(int i=1; i<n+1; i++){
    //     printf("[%d] : pre=%d, dist=%d\n",i,pre[i],dist[i]);
    // }

    if(dist[n]>=INF){
        printf("-1\n");
        return 0;
    }

    int stk[N];
    int top = 0;
    int cur = n;
    while(cur!=-1){
        stk[top++] = cur;
        cur = pre[cur];
    }
    for(int i=top-1;; i--){
        if(i<=0){
            printf("%d\n",stk[i]);
            break;
        }
        printf("%d ", stk[i]);
    }
}