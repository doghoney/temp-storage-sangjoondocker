#include<stdio.h>

#define N 5000
#define NUM 10004
int arr[N];
int answer;
int n,m;
int answer;

void ps(int left, int right);

int main(){
    
    scanf("%d %d",&n, &m);

    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }

    int max = -1;
    int min = NUM+1;

    for(int i=0; i<n; i++){
        if(max < arr[i])
            max = arr[i];
        if(min > arr[i])
            min = arr[i];
    }
    ps(0, max-min);

    printf("%d\n",answer);
}

void ps(int left, int right){
    int mid = (left+right)/2;
    
    if(left == right){
        answer = left;
        return;
    }

    int cnt = 1;
    int min = NUM+1;
    int max = -1;  
    int score;

    for(int i=0; i<n; i++){
        if(min>arr[i])
            min = arr[i];
        if(max<arr[i])
            max = arr[i];
        score = max - min;
        
        if(score > mid){
            min = arr[i];
            max = arr[i];
            cnt ++;
        }
    }
    
    if(cnt > m){
        ps(mid+1, right);
    }
    else{
        ps(left, mid);
    }
}