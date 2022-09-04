#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define N 102
#define NUM 1000006

int main(){
    int n;
    int arr[N];
    bool prime[NUM];
    int primeSeq[NUM/2];
    int primeSet[NUM/2];
    int primeCnt;

    //prime
    memset(prime, 1, NUM);
    for(int i=2; i<NUM; i++){
        for(int j=2; j<=NUM/i; j++){
            if(i*j<NUM)
                prime[i*j] = 0;
        }
    }
    //primeSeq
    primeCnt = 0;
    for(int i=2; i<NUM; i++){
        if(prime[i]==1)
            primeSeq[primeCnt++] = i;
    }
    
    
    //input
    scanf("%d",&n);
    for(int i=0; i<n; i++)
        scanf("%d",&arr[i]);
    
    //check total primeSet
    memset(primeSet, 0, NUM/2);
    int cur;
    for(int i=0; i<n; i++){
        cur = arr[i];
        for(int j=0; j<primeCnt; j++){
            while(cur%primeSeq[j]==0){
                primeSet[j]++;
                cur /= primeSeq[j];
            }
        }
    }

    //maximum score
    int score = 1;
    for(int i=0; i<primeCnt; i++){
        for(int j=0; j<primeSet[i]/n; j++)
            if(primeSet[i]/n>0)
                score *= primeSeq[i];
    }

    //move
    int move = 0;
    int cnt;
    for(int i=0; i<n; i++){
        cur = arr[i];
        for(int j=0; j<primeCnt; j++){
            cnt = 0;
            while(cur%primeSeq[j]==0){
                cnt++;
                cur /= primeSeq[j];
            }
            if(cnt<(primeSet[j]/n))
                move += primeSet[j]/n - cnt;
        }
    }

    printf("%d %d\n",score, move);
}