#include<cstdio>
#include<utility>
#include<algorithm>
#include<cmath>

#define C 100005
#define N 1000

using namespace std;
typedef pair<int ,int> P;

P arrows[C];
P candidate[C];
P stack[C];
int top;

int pita(P a, P b){
    return (a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second);
}

int signedarea(P a, P b, P c){
    return a.first*b.second+b.first*c.second+c.first*a.second
        -a.second*b.first-b.second*c.first-c.second*a.first;
}

bool compare(P a, P b){
    int result = signedarea(arrows[0],a,b);
    if(a.first==arrows[0].first && a.second==arrows[0].second)
        return true;
    if(b.first==arrows[0].first && b.second==arrows[0].second)
        return false;

    if(result>0)
        return true;
    else if(result<0)
        return false;
    else{
        if(pita(a, arrows[0])>pita(b, arrows[0]))
            return true;
        else 
            return false;
    }
}



int main(){
    int c, x, y;
    int depth = N+1;    //lowest y coordinate
    int start;   //idx of lowest arrow

    //input
    scanf("%d", &c);
    for(int i=0; i<c; i++){
        scanf("%d %d", &x, &y);
        arrows[i] = P(x,y);
        if(y < depth){
            start = i;
            depth = y;
        }
        else if(y == depth && x < arrows[start].first){
            start = i;
        }
    }

    //sorting
    P tmp;
    int cnt = 0;
    int pre;

    tmp = arrows[0];
    arrows[0] = arrows[start];
    arrows[start] = tmp;
    sort(arrows+1, arrows+c, compare);

    //if there's many start
    for(int i=0; i<c; i++){
        if(arrows[0].first==arrows[i].first&&arrows[0].second==arrows[i].second)
            start = i;
    }

    candidate[cnt++] = arrows[start];
    candidate[cnt++] = arrows[start+1];
    for(int i=start+2; i<c; i++){
        if(signedarea(candidate[0], candidate[cnt-1], arrows[i])!=0)
            candidate[cnt++] = arrows[i];
        // else
        //     printf("[%d,%d][%d,%d] -> [%d][%d] out\n",arrows[0].first, arrows[0].second, candidate[cnt-1].first, candidate[cnt-1].second, arrows[i].first, arrows[i].second);
    }

    //stack : make convex hull
    top = 0;    //top is always empty (can add here)
    stack[top++] = candidate[0];
    stack[top++] = candidate[1];

    for(int i=2; i<cnt; i++){
        while(1){
            if(signedarea(stack[top-2], stack[top-1], candidate[i])>0){
                stack[top++] = candidate[i];
                break;
            }
            else{
                top--;
            }
        }
        // printf("[%d] : ", i);
        // for(int i=0; i<top; i++){
        //     printf("(%d,%d) ",stack[i].first, stack[i].second);
        // }
        // printf("\n");
    }

    //get the longest distance
    double longest = -1;
    for(int i=0; i<top; i++){
        for(int j=i+1; j<top; j++){
            if(longest < sqrt(pita(stack[i],stack[j])))
                longest = sqrt(pita(stack[i],stack[j]));
        }
    }
    printf("%.7lf\n",longest);
}