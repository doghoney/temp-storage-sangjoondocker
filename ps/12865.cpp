#include<cstdio>
#include<utility>
#include<algorithm>

using namespace std;
#define N 100
#define W 10000007
#define we first
#define va second

typedef pair<int,int> P;
P item[N];
int n, k;
int maxprofit;

bool compare(P a, P b){
    return a.second*b.first>b.second*a.first;
}

void dfs(int lev, int weight, int value){
    int totalweight = weight;
    int bound = value;
    int i;

    //printf("[%d] : %d %d\n",lev, weight, value);
    if(value > maxprofit)
        maxprofit = value;
    
    if(lev>=n)
        return;

    for(i=lev; i<n; i++){
        if(totalweight + item[lev].first <= k){
            totalweight += item[lev].we;
            bound += item[lev].va;
        }
        else
            break;
    }
    
    if(i<n)
        bound += (k-totalweight)*item[i].va/item[i].we;
    if(bound<maxprofit)
        return;
    
    if(weight+item[lev].we <= k)
        dfs(lev+1, weight+item[lev].we, value+item[lev].va);
    dfs(lev+1, weight, value);
        
}

int main(){
    int w, v;
    scanf("%d %d",&n, &k);
    for(int i=0; i<n; i++){
        scanf("%d %d",&w, &v);
        item[i] = P(w,v);
    }

    sort(item, item+n, compare);

    maxprofit = 0;

    dfs(0,0,0);

    printf("%d\n",maxprofit);
    
}