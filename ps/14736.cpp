#include <iostream>

int main(){
    int n0, n1, n2, n3, n4;
    int i=1;
    while(true){
        scanf("%d",&n0);
        if(n0==0)
            break;
        printf("%d. ",i);
        n1 = 3*n0;
        if(n1%2==0){
            n2 = n1/2;
            printf("odd ");
        }
        else{
            n2 = (n1+1)/2;
            printf("even ");
        }
        
        n3 = 3*n2;

        n4 = n3/9;

        printf("%d\n",n4);
    }
    
        
}