#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define N 1120
#define K 14

bool check[N];
int prime[N/2];
int primecnt;
int dp[N/2][K+1][N+1];

int main(){
    int t,n,num;

    //prime initial
    memset(check, 1, N);
    for(int i=2; i<N; i++){
        for(int j=2; j<=N/i; j++){
            if(i*j<N)
                check[i*j] = 0;
        }
    }
    primecnt = 0;
    for(int i=2; i<N; i++)
        if(check[i]==1)
            prime[primecnt++] = i;

    scanf("%d",&t);

    for(int i=0; i<t; i++){
        scanf("%d %d",&n,&num);
        
        for(int i=0; i<primecnt; i++){
            for(int j=1; j<=i&&j<=num; j++){
                for(int k=1; k<=N; k++){
                    printf("%d %d %d\n", i,j,k);
                    dp[i][j][k] = dp[i-1][j][k];
                    for(int l=1; k-prime[i]*l>0; l--){
                        dp[i][j][k] += dp[i-1][j-1][k-prime[i]*l];
                    }
                }
            }
        }

        printf("%d\n",dp[primecnt-1][num][n]);
    }
}