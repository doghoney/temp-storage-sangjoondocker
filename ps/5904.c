#include<stdio.h>

#define N 1000000009

int moo[28];    //moo[27]에서 10^9 길이 넘어감
char answer;

void func(int size, int loc);

int main(){
    int n;

    moo[0] = 3;
    for(int i=1; i<28; i++){
        moo[i] = 2*moo[i-1]+i+3;
    }

    scanf("%d",&n);

    int i;
    for(i=0; i<28; i++){
        if(moo[i]<n)
            continue;
        else
            break;
    }
    
    func(i,n);

    printf("%c\n",answer);
}

void func(int size, int loc){
    if(size == 0){
        if(loc==1)
            answer='m';
        else
            answer = 'o';
        return;
    }

    if(loc<=moo[size-1])
        func(size-1, loc);
    else if(moo[size-1]<loc && loc <=moo[size-1]+size+3){
        if(loc == moo[size-1]+1)
            answer = 'm';
        else
            answer = 'o';
        return;
    }
    else
        func(size-1,loc-(moo[size-1]+size+3));
}