#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>

#define ALPHA 26
#define N 700
#define INF 987654321

using namespace std;

int capacity[ALPHA*2][ALPHA*2];
int flow[ALPHA*2][ALPHA*2];
vector<int> adj[ALPHA*2];

int main(){
    int n;
    char src, dest;
    int cap;

    //init
    for(int i=0; i<ALPHA*2; i++){
        for(int j=0; j<ALPHA*2; j++){
            capacity[i][j] = 0;
            flow[i][j] = 0;
        }
    }

    //get input
    scanf("%d",&n);

    for(int i=0; i<n; i++){
        scanf(" %c %c %d", &src, &dest, &cap);
        
        if('a'<=src&&src<='z')
            src = src - 'a' + ALPHA;
        else if('A'<=src&&src<='Z')
            src = src - 'A';
        
        if('a'<=dest&&dest<='z')
            dest = dest - 'a'+ ALPHA;
        else if('A'<=dest&&dest<='Z')
            dest = dest - 'A';
        
        //put in adj list
        capacity[src][dest] += cap;
        capacity[dest][src] += cap;
        adj[src].push_back(dest);
        adj[dest].push_back(src);
    }

    //adj list simplify : erase dup
    for(int i=0; i<ALPHA*2; i++){
        if(!adj[i].empty()){
            sort(adj[i].begin(), adj[i].end());
            adj[i].erase(unique(adj[i].begin(), adj[i].end()),adj[i].end());
        }
    }

    queue<int> que;
    queue<int> empty;
    int cur, start, fin;
    int min, parent, child;
    int prev[ALPHA*2];

    //just for ease
    start = 0;          //start at 'A'
    fin = ALPHA-1;      //end at 'Z'

    while(1){
        for(int i=0; i<ALPHA*2; i++){
            prev[i] = -1;
        }
        cur = start;
        swap(que, empty);
        que.push(cur);
        
        //find increasing path
        while(!que.empty()){
            cur = que.front();
            que.pop();

            //continue finding by bfs
            for(int next : adj[cur]){
                if(capacity[cur][next]-flow[cur][next]>0 && prev[next]==-1){
                    prev[next] = cur;
                    que.push(next);
                    if(next == fin)
                        break;
                }
            }
        }
        
        if(prev[fin]==-1)
            break;
        
        //find significant limit : min(capacity[src][dest]-flow[src][dest])
        min = INF;
        child = fin;
        parent = prev[child];
        while(child != start){
            if(min > capacity[parent][child]-flow[parent][child])
                min = capacity[parent][child]-flow[parent][child];
            child = parent;
            parent = prev[child];
        }

        //fill with the limitation
        child = fin;
        parent = prev[child];
        while(child != start){
            flow[parent][child] += min;
            flow[child][parent] += -min;
            //printf("[%2d][%2d] = %d..%d\n",parent, child, capacity[parent][child], flow[parent][child]);
            child = parent;
            parent = prev[child];
        }
        //printf("\n");
    }

    //print result
    int result = 0;
    for(int i : adj[fin])
        result += flow[i][fin];
    printf("%d\n",result);
}