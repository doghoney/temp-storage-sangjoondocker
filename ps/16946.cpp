#include<iostream>

#define N 1000

int field[N][N];
int n, m;
int groupsize[N*N];
int group[N][N];
int groupcnt;
int membercnt;

//find 0 group then fill -1 & check surround
void dfs(int x, int y) {
    field[x][y] = -1;
    group[x][y] = groupcnt;
    membercnt++;

    if(x-1>=0&&field[x-1][y]==0)
        dfs(x-1,y);        
    if(x+1<n&&field[x+1][y]==0)
        dfs(x+1,y);
    if(y-1>=0&&field[x][y-1]==0)
        dfs(x,y-1);
    if(y+1<m&&field[x][y+1]==0)
        dfs(x,y+1);
}

int main(){
    scanf("%d %d",&n, &m);

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf("%1d",&field[i][j]);
            group[i][j] = 0;
        }
    }

    //grouping
    groupcnt = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            //find 0 group
            if(field[i][j]!=0)
                continue;
            //renewal with groupcnt
            groupcnt++;
            membercnt = 0;
            dfs(i,j);
            groupsize[groupcnt] = membercnt;
        }
    }

    //labeling
    int adjacent[4];
    int list[4];
    int cnt, exist, sum;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(field[i][j]==-1)
                field[i][j] = 0;
            else if(field[i][j]==1){
                for(int k=0; k<4; k++)
                    adjacent[k] = 0;
                if(i-1>=0&&group[i-1][j]!=0)
                    adjacent[0] = group[i-1][j];        
                if(i+1<n&&group[i+1][j]!=0)
                    adjacent[1] = group[i+1][j];
                if(j-1>=0&&group[i][j-1]!=0)
                    adjacent[2] = group[i][j-1];
                if(j+1<m&&group[i][j+1]!=0)
                    adjacent[3] = group[i][j+1];

                cnt = 0;
                for(int k=0; k<4; k++){
                    exist = 0;
                    for(int l=0; l<cnt; l++){
                        if(list[l]==adjacent[k])
                            exist = 1;
                    }
                    if(!exist)
                        list[cnt++] = adjacent[k];
                }

                sum = 0;
                for(int k=0; k<cnt; k++)
                    sum += groupsize[list[k]];
                field[i][j] = sum+1;
            }
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            printf("%d",field[i][j]%10);
        }
        printf("\n");
    }
}