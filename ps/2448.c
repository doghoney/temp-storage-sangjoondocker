#include<stdio.h>
#include<string.h>

#define N 3072

char arr[2*N-1][N];

void star(int x, int y, int k);

int main(){
    int n;
    scanf("%d",&n);

    for(int i=0; i<2*N-1; i++){
        memset(arr[i], ' ', N);
    }

    star(0,0,n);

    for(int j=n-1; j>=0; j--){
        for(int i=0; i<2*n-1; i++){
            printf("%c",arr[i][j]);
        }
        printf("\n");
    }
}

void star(int x, int y, int k){
    if(k==3){
        arr[x+0][y] = '*';
        arr[x+1][y] = '*';
        arr[x+2][y] = '*';
        arr[x+3][y] = '*';
        arr[x+4][y] = '*';
        arr[x+1][y+1] = '*';
        arr[x+3][y+1] = '*';
        arr[x+2][y+2] = '*';
        return;
    }
    star(x, y, k/2);
    star(x+k/2, y+k/2, k/2);
    star(x+k, y, k/2);
}