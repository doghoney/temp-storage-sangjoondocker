#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define N 10004

int depth;
struct{
        int lchild;
        int rchild;
}tree[N+1]; //idx usg : [1,n]
int leftmost[N+1];    //leftmost[i] : level i's leftmost node, idx usg :[1,n]
int rightmost[N+1];   //same

int sst(int node, int level, int limit);

int main(){
    int n;

    //input
    scanf("%d",&n);
    int cur;
    for(int i=0; i<n; i++){
        scanf("%d", &cur);
        scanf("%d", &tree[cur].lchild);
        scanf("%d", &tree[cur].rchild);
    }

    //find root
    bool checklist[N+1];    //idx usg : [1,n]
    int root;

    memset(checklist, 1, n+1);
    for(int i=1; i<=n; i++){
        if(tree[i].lchild!=-1)
            checklist[tree[i].lchild] = 0;
        if(tree[i].rchild!=-1)    
            checklist[tree[i].rchild] = 0;
    }
    for(int i=1; i<=n; i++){
        if(checklist[i]==1){
            root = i;
            break;
        }
    }
    
    //bfs search
    
    memset(leftmost, -1, N);
    memset(rightmost, -1, N);
    sst(root, 1, 0);   

    int width;
    int maxwidth = -1;
    int maxlevel = -1;
    for(int i=1; i<=depth; i++){
        width = rightmost[i]-leftmost[i]+1;
        if(maxwidth < width){
            maxwidth = width;
            maxlevel = i;
        }
    }

    printf("%d %d\n", maxlevel, maxwidth);
}

int sst(int node, int level, int limit){
    int leftsub, rightsub, loc;
    if(node == -1)
        return 0;
    if(depth < level)
        depth = level;
    
    leftsub = sst(tree[node].lchild, level+1, limit);
    rightsub = sst(tree[node].rchild, level+1, limit+leftsub+1);

    loc = limit+leftsub;

    //renew
    if(leftmost[level]== -1 || loc<leftmost[level])
        leftmost[level] = loc;
    if(rightmost[level]== -1 || rightmost[level]<loc)
        rightmost[level] = loc;

    return leftsub+rightsub+1;
}