#include<iostream>
#include<algorithm>
#include<cmath>

#define C 100005

using namespace std;

struct coordinate{
    int x;
    int y;
};

coordinate arrow[C];

bool compare(const coordinate &a, const coordinate &b){
    if(a.y-arrow[0].y==0 && b.y-arrow[0].y==0){
        if(a.x-arrow[0].x<b.x-arrow[0].x)
            return 1;
        else
            return 0;
    }
    else if(a.y-arrow[0].y==0 && b.y-arrow[0].y!=0)
        return 1;
    else if(a.y-arrow[0].y!=0 && b.y-arrow[0].y==0)
        return 0;
    
    float cotA, cotB;   //간격: 1/2000 = 오차범위 내
    cotA = ((double)a.x-arrow[0].x)/(a.y-arrow[0].y);
    cotB = ((double)b.x-arrow[0].x)/(b.y-arrow[0].y);
    //cot가 작을수록 반시계방향

    if((a.x-arrow[0].x)*(b.y-arrow[0].y)==(a.y-arrow[0].y)*(b.x-arrow[0].x)){  //기울기가 동일한 경우 cotA == cotB가 되기에 오차 위험 존재.
        if(a.x-arrow[0].x<b.x-arrow[0].x)
            return 1;
        else
            return 0;
    }
    else if(cotA<cotB)
        return 0;
    else if(cotA>cotB)
        return 1;
}

bool signArea(int a, int b, int c){
    int sign;
    sign =   arrow[a].x*arrow[b].y-arrow[b].x*arrow[a].y+
            arrow[b].x*arrow[c].y-arrow[c].x*arrow[b].y+
            arrow[c].x*arrow[a].y-arrow[a].x*arrow[c].y;  
    //int계산으로 인한 정확한 0 판별.
    
    if(sign == 0)
        return 1;
    else if(sign>0)
        return 1;
    else
        return 0;
    
}
int main(){
    int c;

    cin >> c;

    for(int i=0; i<c; i++){
        cin >> arrow[i].x;
        cin >> arrow[i].y;
    }

    //find po
    int py = 1001;
    int px = 1001;
    int idx = C;
    for(int i=0; i<c; i++){
        if(py > arrow[i].y){
            py = arrow[i].y;
            px = arrow[i].x;
            idx = i;
        }
        else if(py == arrow[i].y && px > arrow[i].x){
            py = arrow[i].y;
            px = arrow[i].x;
            idx = i;
        }
    }
    if(idx!=0)
        swap(arrow[0], arrow[idx]);

    //sorting
    sort(arrow+1, arrow+c, compare);

    //remove duplication
    int size = 0;   //temp[size]는 늘 비워둔다.
    coordinate temp[C];

    temp[size++] = arrow[0];
    temp[size++] = arrow[1];
    for(int i=2; i<c; i++){
        //temp[size-1]와 arrow[i]의 기울기가 다르면 넣고
        //같으면 길이가 먼 거를 넣는다.
        if(temp[size-1].x*arrow[i].y!=temp[size-1].y*arrow[i].x){
            temp[size++] = arrow[i];
        }
        else{
            if(temp[size-1].x-arrow[0].x==0){
                if(temp[size-1].y-arrow[0].y==0){
                    temp[size-1] = arrow[i];
                }
                else if((arrow[i].y-arrow[0].y)/(temp[size-1].y-arrow[0].y)>0)
                    temp[size-1] = arrow[i];
            }
            else{
                if((arrow[i].x-arrow[0].x)/(temp[size-1].x-arrow[0].x)>0)
                    temp[size-1] = arrow[i];
            }
        }
    }

    for(int i=0; i<size; i++){
        arrow[i] = temp[i];
    }
    
    //convex hull
    int stk[C]; //arrow의 idx만 저장
    int top=0;  //stk[top]은 늘 비워둔다.
    stk[top++] = 0;
    stk[top++] = 1;
    if(size>2)
        stk[top++] = 2;
    for(int i=3; i<size; i++){
        while(signArea(stk[top-1],stk[top-2],i)){
            top--;
        }
        stk[top++] = i;
    }

    //convex polygon's max length (O(n^2))
    double max = 0;
    double distance_square, distance;
    coordinate a, b;
    for(int i=0; i<top; i++){
        for(int j=i+1; j<top; j++){
            distance_square = (arrow[stk[i]].x-arrow[stk[j]].x)*(arrow[stk[i]].x-arrow[stk[j]].x)+(arrow[stk[i]].y-arrow[stk[j]].y)*(arrow[stk[i]].y-arrow[stk[j]].y);
            distance = sqrt(distance_square);
            if(max<distance){
                max = distance;
            }
        }
    }
    printf("%lf\n",max);
}