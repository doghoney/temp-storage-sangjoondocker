#include<stdio.h>

#define N 100005
#define NUM 10004

int arr[N];
int n, m;
int answer;

void bsearch(int left, int right);

int main(){
    
    scanf("%d %d",&n,&m);
    
    for(int i=0; i<n; i++){
        scanf("%d",&arr[i]);
    }

    int sum = 0;
    int max = -1;
    for(int i=0; i<n; i++){
        if(max < arr[i])
            max = arr[i];
        sum += arr[i];
    }

    bsearch(max, sum);

    printf("%d\n",answer);
}

void bsearch(int left, int right){
    int mid = (left+right)/2;
    int cur = mid;
    int cnt = 1;

    if(left>=right){
        answer = left;
        return;
    }

    for(int i=0; i<n; i++){
        if(cur-arr[i] >= 0)
            cur -= arr[i];
        else{
            cnt++;
            cur = mid;
            cur -= arr[i];
        }
    }

    if(cnt > m)
        bsearch(mid+1, right);
    else{
        bsearch(left, mid);
    }
}