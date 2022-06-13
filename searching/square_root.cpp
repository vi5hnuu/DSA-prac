#include<iostream>
using namespace std;


int square_root_naive(int x){//O(sqrt x)
    int i;
    for(i=0;i*i<=x;i++);
    return (i-1);
}

long long sqrt(int x){//binary search method
    //array is 0 to x/2(to be precise root x)
    long long low=0;
    long long high=x/2;
    while(low<=high){
        long long mid=(low+high)/2;
        if(mid*mid<=x && (mid+1)*(mid+1)>x)
            return mid;
        else if(mid*mid>x)
            high=mid-1;
        else
            low=mid+1;
    }
    return 1;//x=1
}

int main(){
    cout<<sqrt(6179767)<<" "<<square_root_naive(0)<<endl;
    cout<<sqrt(0)<<" "<<square_root_naive(0)<<endl;
    cout<<sqrt(1)<<" "<<square_root_naive(1)<<endl;
    cout<<sqrt(15)<<" "<<square_root_naive(15)<<endl;
    cout<<sqrt(16)<<" "<<square_root_naive(16)<<endl;
    cout<<sqrt(1125)<<" "<<square_root_naive(1125)<<endl;

    return 0;
}
