#include<cstdio>
#include<vector>

#define N 1000
#define M 1000

using namespace std;

vector<int> adj[M];
int par[N];
bool visited[M];

bool dfs(int a){
    visited[a] = true;
    for(int b : adj[a]){
        if(par[b] == -1 || !visited[par[b]]&&dfs(par[b])){
            par[b] = a;
            return true;
        }
    }
    return false;
}

int main(){
    int t;
    int n,m;
    int st, end;
    scanf("%d", &t);

    for(int test=0; test<t; test++){
        //init
        for(int i=0; i<M; i++)
            adj[i].clear();

        //input
        scanf("%d %d", &n, &m);
        for(int i=0; i<m; i++){
            scanf("%d %d", &st, &end);

            for(int j=st; j<=end; j++){
                adj[i].push_back(j-1);
            }
        }
        
        
        //binary matching
        int matched = 0; 
        for(int i=0; i<N; i++) 
            par[i] = -1;
        
        for(int i=0; i<m; i++){
            for(int j=0; j<M; j++) 
                visited[j] = false;
            if(dfs(i))
                matched++;
        }

        printf("%d\n", matched);
    }
}