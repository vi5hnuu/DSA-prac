#include<iostream>
using namespace std;

/*
int maxProfit(int price[],int start,int end){
    if(end<=start)
        return 0;

    int profit=0;
    for(int i=start;i<end;i++){
        for(int j=i+1;j<=end;j++){
            if(price[j]>price[i]){
                int curProfit=price[j]-price[i]+maxProfit(price,start,i-1)+maxProfit(price,j+1,end);
                profit=max(curProfit,profit);
            }
        }
    }
    return profit;
}
*/

int maxProfit(int price[],int start,int end){
    int profit=0;
    for(int i=1;i<=end;i++){
        if(price[i-1]<price[i])
            profit+=(price[i]-price[i-1]);
    }
    return profit;
}

int main(){
    int a[]={1,5,3,8,12};
    cout<<maxProfit(a,0,4);

    return 0;
}
