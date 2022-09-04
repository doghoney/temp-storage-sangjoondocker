#include<stdio.h>
#include<string.h>
#define N 6561

char arr[N][N];  //왼쪽 아래 :0,0

void box(int x, int y, int size);

int main(){
    int n;
    for(int i=0; i<N; i++)
        memset(arr[i],' ',N);
    scanf("%d",&n);
    
    box(0,0,n);

    for(int j=n-1; j>=0; j--){
        for(int i=0; i<n; i++)
            printf("%c",arr[i][j]);
        printf("\n");
    }
}

void box(int x, int y, int size){
    if(size <= 3){
        arr[x][y] = '*';
        arr[x+1][y] = '*';
        arr[x+2][y] = '*';
        arr[x][y+1] = '*';
        arr[x+2][y+1] = '*';
        arr[x][y+2] = '*';
        arr[x+1][y+2] = '*';
        arr[x+2][y+2] = '*';
        return;
    }
    box(x,y,size/3);
    box(x+size/3,y,size/3);
    box(x+2*size/3,y,size/3);
    box(x,y+size/3,size/3);
    box(x+2*size/3,y+size/3,size/3);
    box(x,y+2*size/3,size/3);
    box(x+size/3,y+2*size/3,size/3);
    box(x+2*size/3,y+2*size/3,size/3);
}