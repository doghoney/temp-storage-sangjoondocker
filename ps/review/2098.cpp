#include<cstdio>

#define N 16
#define SET 65536   //2^16
#define INF 987654321

int w[N][N];
int dp[N][SET];

int main(){
    int n;
    int weight;
    scanf("%d", &n);

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%d",&weight);
            if(weight==0&&i!=j)
                w[i][j] = INF;
            else
                w[i][j] = weight;
        }
    }

    for(int start=0; start<n; start++){
        for(int i=0; i<N; i++)
            if(i!=start)
                dp[i][0] = w[start][i];
        
        for(int cnt=1; cnt<=16; cnt++){
            for()
        }
    }
}