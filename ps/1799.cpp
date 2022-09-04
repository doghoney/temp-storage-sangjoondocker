#include <iostream>
#include <vector>
#include <utility>
#include <cstdlib>

#define N 10

using namespace std;
using P=pair<int, int>;

int board[N][N];
vector<P> diag[2*N-1];
int n, maximum;

bool promise(P bishop, vector<P> completes){
    for(P complete : completes){
        if(abs(bishop.first-complete.first)==abs(bishop.second-complete.second))
            return false;
    }
    return true;
}

void bt(int line, vector<P> completes){
    //end condition
    if(line>=2*n-1){
        // for(auto i : completes)
        //     printf("[%d,%d] ",i.first, i.second);
        // printf("\n");
        if(maximum < completes.size())
            maximum = completes.size();
        return;
    }

    bt(line+2, completes);
    
    for(P bishop : diag[line]){
        if(promise(bishop, completes)){
            completes.push_back(bishop);
            bt(line+2, completes);
            completes.pop_back();
        }
    }
}

int main(){

    scanf("%d", &n);

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            scanf("%d", &board[i][j]);
            if(board[i][j]==1)
                diag[j-i+n-1].push_back(P(i,j));
        }
    }
    int result = 0;
    maximum = 0;
    vector<P> None;
    bt(0, None);
    result += maximum;
    
    maximum = 0;
    None.clear();
    bt(1, None);
    result += maximum;
    
    printf("%d\n",result);
}