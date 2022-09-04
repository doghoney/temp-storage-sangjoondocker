#include<stdio.h>

#define N 64

char arr[N][N];
char stack[2*N*N];
int top;

void group(int row, int col, int size);

int main(){
    int n;
    scanf("%d",&n);

    getchar();
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%c",&arr[i][j]);
        }
        getchar();
    }
    top = 0;
    group(0,0,n);   //left-up : 0,0

    for(int i=0; i<top; i++)
        printf("%c",stack[i]);
    printf("\n");
}

void group(int row, int col, int size){

    if(size<=1){
        stack[top++] = arr[row][col];
        return;
    }
    stack[top++] = '(';
    group(row, col, size/2);
    group(row, col+size/2, size/2);
    group(row+size/2, col, size/2);
    group(row+size/2, col+size/2, size/2);

    for(int i=0; ; i++){
        if(i>=4){
            top = top-4;
            stack[top-1] = '1';
            return;
        }
        if(stack[top-1-i]!='1')
            break;
    }

    for(int i=0; ; i++){
        if(i>=4){
            top = top-4;
            stack[top-1] = '0';
            return;
        }
        if(stack[top-1-i]!='0')
            break;
    }
    
    stack[top++] = ')';
}