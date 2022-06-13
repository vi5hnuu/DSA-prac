#include<iostream>
using namespace std;

/*
//if position start from 1
 int helper(int n,int k){
        if(n==1)
            return 0;

       return (helper(n-1,k)+k)%n;
    }
    public:
    int josephus(int n, int k)
    {
       return helper(n,k)+1;
    }
*/

int jos(int n,int k){
    if(n==1){
        return 0;
    }

    return (jos(n-1,k)+k)%n;
}


int main(){
    cout<<jos(5,3)<<endl;

    return 0;
}
