#include<cstdio>
#include<utility>

#define N 10
#define x first 
#define y second

using namespace std;
typedef pair<int, int> P;

int map[N][N];
int colorpaper[6];
int total;
int min;
bool paper(P cur, int size){
    if(colorpaper[size]<=0)
        return false;
    if(cur.x+size>N||cur.y+size>N)
        return false;
    if(total>min)
        return false;

    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
            if(map[cur.x+i][cur.y+j]!=1)
                return false;
        
    return true;
}

void fill(P cur, int size, int content){
    for(int i=0; i<size; i++)
        for(int j=0; j<size; j++)
            map[cur.x+i][cur.y+j] = content;
}

void backtrace(P cur){
    P next;
    bool find;
    for(int size=1; size<=5; size++){
        if(paper(cur,size)){
            fill(cur, size, -1);
            colorpaper[size]--;
            total++;
            
            find = false;
            for(int i=0; i<N; i++)
                for(int j=0; j<N; j++)
                    if(!find&&map[i][j]==1){
                        next = P(i,j);
                        find = true;
                    }

            if(find)
                backtrace(next);
            else{
                if(min > total)
                    min = total;
            }
            fill(cur, size, 1);
            colorpaper[size]++;
            total--;
        }
    }
        
}

int main(){
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            scanf("%d", &map[i][j]);

    P start;
    bool find = false;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            if(!find&&map[i][j]==1){
                start = P(i,j);
                find = true;
            }

    if(!find){
        printf("0\n");
        return 0;
    }
    
    for(int i=1; i<=5; i++)
        colorpaper[i] = 5;
    total = 0;
    min = 100;
    backtrace(start);
    
    if(min!=100)
        printf("%d\n", min);
    else
        printf("-1\n");
}