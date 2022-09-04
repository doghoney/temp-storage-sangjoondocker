#include<cstdio>
#include<vector>
#include<utility>
#include<queue>
#include<map>

#define SIZE 50
#define N 100
#define INF 987654321

using namespace std;
typedef pair<int,int> P;
typedef pair<P, int> NODE;


char field[SIZE][SIZE];
bool visted[SIZE][SIZE];
vector<P> cars;
vector<P> parks;
map<P,int> parkdic;
int path[N][N];
int A[N];
int B[N];
bool used[N];

bool dfs(int a, int limit){
    used[a] = true;
    for(int b=0; b<parks.size(); b++){
        if(path[a][b]>limit)
            continue;
        if(B[b] == -1 || !used[B[b]] && dfs(B[b], limit)){
            A[a] = b;
            B[b] = a;
            //printf("%d,%d : %d\n", a, b, path[a][b]);
            return true;
        }
    }
    return false;
}

int main(){
    int r, c;
    char buf[SIZE+1];
    
    //input
    scanf("%d %d", &r, &c);
    for(int i=0; i<r; i++){
        scanf("%s", buf);
        for(int j=0; j<c; j++){
            field[i][j] = buf[j];
            if(buf[j]=='C'){
                cars.push_back(P(i, j));
            }
            else if(buf[j]=='P'){
                parks.push_back(P(i, j));
                parkdic.insert({P(i,j), parks.size()-1});
            }
        }
    }

    
    //BFS : get path
    queue<NODE> Q; 
    int x;
    int y;
    int dist;
    int cnt;

    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            path[i][j] = INF;

    for(int i=0; i<cars.size(); i++){
        Q.push(NODE(cars[i],0));
        for(int j=0; j<r; j++)
            for(int k=0; k<c; k++)
                visted[j][k] = false;
        cnt = 0;
        while(!Q.empty()){
            x = Q.front().first.first;
            y = Q.front().first.second;
            dist = Q.front().second;
            Q.pop();
            if(field[x][y]=='P'){
                path[i][parkdic.find(P(x,y))->second] = dist;
            }

            if(x-1>=0 && field[x-1][y]!='X' && !visted[x-1][y]){
                visted[x-1][y] = true;
                Q.push(NODE(P(x-1,y),dist+1));
            }
            if(x+1<r && field[x+1][y]!='X' && !visted[x+1][y]){
                visted[x+1][y] = true;
                Q.push(NODE(P(x+1,y),dist+1));
            }
            if(y-1>=0 && field[x][y-1]!='X' && !visted[x][y-1]){
                visted[x][y-1] = true;
                Q.push(NODE(P(x,y-1),dist+1));
            }
            if(y+1<c && field[x][y+1]!='X' && !visted[x][y+1]){
                visted[x][y+1] = true;
                Q.push(NODE(P(x,y+1),dist+1));
            }
        }
    }

    // for(int i=0; i<cars.size(); i++){
    //     for(int j=0; j<parks.size(); j++)
    //         printf("[%d][%d] : %d\n", i,j,path[i][j]);
    // }

    //network flow + binary search 
    int low = 0;
    int high = 0;
    int limit;
    bool success = true;
    for(int i=0; i<cars.size(); i++){
        for(int j=0; j<parks.size(); j++){
            high += path[i][j];
        }
    }
    while(low<high){
        //flow algoritm : find minimum time
        limit = (low+high)/2;
        success = true;

        for(int i=0; i<N; i++){
            A[i] = -1;
            B[i] = -1;
        }

        // /printf("-----low, limit, high : %d %d %d\n", low, limit, high);
        for(int i=0; i<cars.size(); i++){
            if(A[i]==-1){
                for(int i=0; i<N; i++){
                    used[i] = false;
                }
                if(!dfs(i, limit)){
                    success = false;
                }
            }
        }   

        //binary search
        if(success) high = limit;
        else low = limit+1;
    }

    //check if possible
    limit = (low+high)/2;
    success = true;
    
    for(int i=0; i<N; i++){
        A[i] = -1;
        B[i] = -1;
    }

    for(int i=0; i<cars.size(); i++){
        if(A[i]==-1){
            for(int i=0; i<N; i++){
                used[i] = false;
            }
            if(!dfs(i, limit))
                success = false;
        }
    }
    
    if(success && low!=INF)
        printf("%d\n", low);
    else
        printf("-1\n");
}