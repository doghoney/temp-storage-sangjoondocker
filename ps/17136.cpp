#include<iostream>

#define N 10

int arr[N][N];
int min;
int count;
int colorpaper[6];

bool paper(int x, int y, int size){
    bool result = 1;
    if(x+size>N||y+size>N)
        return 0;
    if(colorpaper[size]<=0)
        return 0;
    if(count>min)
        return 0;

    for(int i=0; i<size; i++){
        for(int j=0; j<size ;j++){
            if(arr[x+i][y+j]!=1)
                result = 0;
        }
    }

    return result;
}

void fill(int x, int y, int size, int value){
    for(int i=0; i<size; i++){
        for(int j=0; j<size ;j++){
            arr[x+i][y+j] = value;
        }
    }
}

void backtrace(int n){ 
    int x = n/N;
    int y = n%N;
    for(int size = 5; size>0; size--){
        if(paper(x, y, size)){
            fill(x, y, size, -size);
            colorpaper[size]--;
            count++;
            for(int i=n+1; ; i++){
                if(i>=N*N){             //all filled!
                    if(min>count)
                        min = count;
                    break;
                }
                if(arr[i/N][i%N]==1){   //next 1!
                    backtrace(i);
                    break;
                }
            }
            fill(x, y, size, 1);
            colorpaper[size]++;
            count--;
        }
    }
}

int main(){

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++)
            scanf("%d",&arr[i][j]);
    }

    int start = -1;
    int check=0;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            if(arr[i][j]==1){
                if(check==0){
                    start = N*i+j;
                    check++;
                }
            }
    
    min = N*N+1;
    count = 0;
    for(int i=1; i<6; i++)
        colorpaper[i] = 5;
    backtrace(start);

    if(min != N*N+1)
        printf("%d\n",min);
    else if(start == -1)
        printf("0\n");
    else
        printf("-1\n");
}