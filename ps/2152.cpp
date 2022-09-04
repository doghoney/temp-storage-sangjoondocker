#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

#define N 10004
#define M 100005

using namespace std;

typedef struct{
    int u;
    int v;
}Edge;

Edge edge[M];
vector<int> edgefrom[N+1]; 
int color[N+1];
int finish[N+1];
int fsort[N+1];
int tm;
int grp;
int componentsize[N+1];
int component[N+1];
int componentfin[N+1];
int acumulatedweight[N+1];

bool compare(int x, int y){
    return finish[x]>finish[y];
}

void label(int x){
    color[x] = 1;
    if(edgefrom[x].size()!=0)
        for(int v : edgefrom[x])
            if(color[v]==0)
                label(v);
    tm++;
    finish[x] = tm;
}

void group(int x){
    color[x] = 1;
    component[x] = grp;
    componentsize[grp]++;
    if(componentfin[grp]<finish[x])
        componentfin[grp] = finish[x];

    if(edgefrom[x].size()!=0)
        for(int v : edgefrom[x])
            if(color[v]==0&&finish[v]!=-1)
                group(v);
}

int main(){
    int n,m;
    int s,t;    
    scanf("%d %d %d %d",&n, &m, &s, &t);

    int u,v;
    for(int i=0; i<m; i++){
        scanf("%d %d",&u,&v);
        edge[i].u = u;
        edge[i].v = v;
        edgefrom[u].push_back(v);
    }

    //init color - 0:not traveled, 1:traveled
    for(int i=1; i<n+1; i++){
        color[i] = 0;
        finish[i] = -1;
    }

    //label G with f[]  + if t's color is 0 : print("0\n");
    tm = 0;
    label(s);
    if(finish[t]==-1){
        printf("0\n");  //no path exist
        return 0;
    }

    //inverse edge
    for(int i=1; i<n+1; i++)
        edgefrom[i].clear();
    for(int i=0; i<m; i++){
        u = edge[i].v;
        v = edge[i].u;
        edgefrom[u].push_back(v);
    }

    //init color&component
    for(int i=0; i<n+1; i++){
        color[i] = 0;
        componentsize[i] = 0;
        componentfin[i] = -1;
    }

    //sort by finish[]
    for(int i=1; i<n+1; i++){
        fsort[i] = i;
    }
    sort(fsort+1, fsort+n+1, compare);

    //check scc
    grp = 0;
    for(int i=1; i<n+1; i++){
        if(color[fsort[i]]==0&&finish[fsort[i]]!=-1){
            group(fsort[i]);
            grp++;
        }
    }

    //init for bfs + make scc dag
    for(int i=0; i<grp; i++){   //scc componenet uses idx [0,grp-1]
        edgefrom[i].clear();
        acumulatedweight[v] = -1;
    }
    for(int i=0; i<m; i++){
        if(component[edge[i].u]!=component[edge[i].v])
            edgefrom[component[edge[i].u]].push_back(component[edge[i].v]);
    }
    for(int i=0; i<grp; i++){
        sort(edgefrom[i].begin(), edgefrom[i].end());
        edgefrom[i].erase(unique(edgefrom[i].begin(), edgefrom[i].end()),edgefrom[i].end());
    }

    //bfs scc
    int result = 0;
    queue<int> q;
    int cur;
    cur = component[s];
    acumulatedweight[cur] = componentsize[cur];
    q.push(cur);

    while(!q.empty()){
        cur = q.front();
        q.pop();
        for(int v : edgefrom[cur]){
            if(acumulatedweight[v] < acumulatedweight[cur]+componentsize[v]){
                acumulatedweight[v] = acumulatedweight[cur]+componentsize[v];
                q.push(v);
            }
        }
    }


    printf("%d\n", acumulatedweight[component[t]]);
}