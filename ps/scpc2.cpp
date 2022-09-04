#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <map>
#define N 500005
#define K 500005

using namespace std;
using P = pair<long long, int>;

long long Answer;
int value[N+1];
P sum[N+1];
map<int, vector<int>> m;
long long dp[N+1];

int main(int argc, char** argv)
{
	int T, test_case;
	setbuf(stdout, NULL);

	scanf("%d",&T);
	for(test_case = 0; test_case  < T; test_case++)
	{
        int n, k;
        long long total = 0, grp;
        Answer = 0;
        
        scanf("%d %d",&n, &k);
        sum[0] = P(0,0);
		for(int i=1; i<=n; i++){
            scanf("%d",&value[i]);
            total += value[i];
            sum[i] = P(sum[i-1].first+value[i], i);
        }

        if(total%k == 0){
            
            grp = total/k;
            sort(sum, sum+n+1);

            long long idx = -1;
            vector<int> tmp;
            for(int i=0; i<=n; i++){
                if(grp == 0){
                    if(sum[i].first == 0){
                        m.insert({idx, tmp});
                        idx++;
                        tmp.clear();
                        tmp.push_back(sum[i].second);
                    }
                    if(i >= n){
                        m.insert({idx, tmp});
                        tmp.clear();
                    }
                }
                else if(sum[i].first%grp == 0){
                    if(idx != sum[i].first/grp){
                        m.insert({idx, tmp});
                        
                        idx = sum[i].first/grp;
                        tmp.clear();
                    }

                    tmp.push_back(sum[i].second);
                    if(i >= n){
                        m.insert({idx, tmp});
                        tmp.clear();
                    }
                }
            }
            
            // for(auto i : m){
            //     printf("[%d] : ",i.first);
            //     for(auto j : i.second)
            //         printf("%d ",j);
            //     printf("\n");
            // }

            // printf("==\n");
            // for(int i=0; i<=n; i++)
            //     if(sum[i].first%grp==0)
            //     printf("[%d] : %d %d\n",i,sum[i].first/grp, sum[i].second);

            dp[0] = 1;
            for(int i=1; i<=n; i++){
                dp[i] = 0;
            }
            
            map<int, vector<int>>::iterator pre;
            for(auto i=m.begin(); i!=m.end(); i++){
                if(i==m.begin()){
                    pre = i;
                    continue;
                }
                for(auto j : i->second){
                    for(auto k : pre->second)
                        if(j>k)
                            dp[j] += dp[k];
                }
                pre = i;
            }

            // printf("==\n");
            // for(int i=0; i<=n; i++)
            //     printf("[%d] : %lld\n",i,dp[i]);

            m.clear();
        }
        Answer = dp[n];
		// Print the answer to standard output(screen).
        printf("Case #%d\n",test_case+1);
		printf("%lld\n",Answer);
	}

	return 0;
}