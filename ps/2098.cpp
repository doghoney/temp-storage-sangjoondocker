#include<iostream>

#define N 16
#define SET 65536   //2^16
#define COMB 12870  //16C8
#define INF 123456789

int W[N][N];
int tsp[N][SET/2];
int set[N][COMB];
int setCnt[N];
int power2[N+1];
int h[N-1];     //hash
bool exist[N-1];

int main(){
    //input
    int n;
    scanf("%d", &n);

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            scanf("%d", &W[i][j]);
    }

    //change 0 to INF
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(W[i][j]==0)
                W[i][j] = INF;
        }
    }

    //2 power n
    int tmp = 1;
    for(int i=0; i<N+1; i++){
        power2[i] = tmp;
        tmp *= 2;
    }
    
    //set by number of elements
    int one;
    int setnum = power2[n];
    for(int i=0; i<setnum/2; i++){
        one = 0;
        tmp = i;
        for(int j=0; j<n-1; j++){
            if(tmp%2==1)
                one++;
            tmp /= 2;
        }
        set[one][setCnt[one]] = i;
        setCnt[one]++;
    }
    

    //solve
    int min, dist, idx, cur;
    int result = INF;
    for(int start=0; start<n; start++){
        //hash
        idx = 0;
        for(int i=0; i<n; i++){
            if(i!=start){
                h[idx++] = i;
            }
        }
        
        //initialize
        for(int i=0; i<n-1; i++){ 
            tsp[h[i]][0] = W[start][h[i]];
        }

        for(int cnt=1; cnt<n; cnt++){
            for(int i=0; i<n-1; i++){
                for(int j=0; j<setCnt[cnt]; j++){
                    //element check
                    cur = set[cnt][j];
                    for(int k=0; k<n-1; k++){
                        if(cur%2==1)
                            exist[k] = true;
                        else
                            exist[k] = false;
                        cur /= 2;
                    }
                    if(exist[i]==true)
                        continue;
                    
                    //renewal
                    min = INF;
                    for(int k=0; k<n-1; k++){
                        if(exist[k]==true){
                            dist = W[h[k]][h[i]] + tsp[h[k]][set[cnt][j]-power2[k]];
                            if(min>dist)
                                min = dist;
                        }
                    }
                    tsp[h[i]][set[cnt][j]] = min;
                }
            }
        }

        //connect to start & renewal
        for(int i=0; i<n-1; i++){
            dist = W[h[i]][start]+tsp[h[i]][setnum/2-1-power2[i]];
            if(result > dist)
                result = dist;
        }
    }
    
    printf("%d\n",result);
}