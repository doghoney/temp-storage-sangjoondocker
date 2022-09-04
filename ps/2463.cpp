#include<iostream>
#include<algorithm>
#include<set>

#define SIZE 100005
#define PADDING 1000000000
using namespace std;

typedef struct{
    int u;
    int v;
    int weight;
}Edge;

Edge edge[SIZE+1];
int parent[SIZE+1];
long long sizebyparent[SIZE+1];
long long sum[SIZE];

bool compare(Edge e1, Edge e2){
    return e1.weight>e2.weight;
}

int find(int x){
    if(parent[x] == x) return x;
    parent[x] = find(parent[x]);
    return parent[x];
}

void merge(int x, int y) {
    int a = find(x);
    int b = find(y);
    if(a == b) return;
    parent[b] = a;
    sizebyparent[a] += sizebyparent[b];
}

int main(){
    int n,m;
    scanf("%d %d",&n, &m);

    for(int i=0; i<m; i++){
        scanf("%d %d %d",&edge[i].u, &edge[i].v, &edge[i].weight);
    }

    //sort by weight
    sort(edge, edge+SIZE, compare);

    //init
    for(int i=0; i<n+1; i++){
        parent[i] = i;
        sizebyparent[i] = 1;
    }
    sum[0] = edge[m-1].weight;
    for(int i=1; i<m; i++){
        sum[i]=(sum[i-1]+edge[m-1-i].weight)%PADDING;
    }

    //restruct graph from the maximum
    long long result = 0;
    int pu, pv;
    Edge e;
    for(int i=0; i<m; i++){
        e = edge[i];
        pu = find(e.u);
        pv = find(e.v);
        if(pu==pv)
            continue;

        result += (sizebyparent[pu]%PADDING)*(sizebyparent[pv]%PADDING)*sum[m-1-i]%PADDING;
        merge(pu, pv);
    }
    
    printf("%d\n",(int)(result%PADDING));
}