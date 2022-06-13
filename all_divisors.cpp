#include<iostream>
using namespace std;

void all_divisors(int n){
    for(int i=1;i<=n;i++){
        if(n%i==0){
            cout<<i<<" ";
        }
    }
    cout<<endl;
}

void all_divisors_unsorted_o(int n){ //not in sorted order
    for(int i=1;i*i<=n;i++){
        if(n%i==0){
            cout<<i<<" ";
            if(i!=n/i)//(x,y) => x!=y (this if find the y in the pair)
                cout<<(n/i)<<" ";
        }
    }
    cout<<endl;
}
void all_divisors_sorted_o(int n){ //in sorted order
    int i;
    int last_divisor=1;
    for(i=1;i*i<=n;i++){
        if(n%i==0){
            cout<<i<<" ";
            last_divisor=i;
        }
    }
    for(;i>=1;i--){
        if(n%i==0){
                if(last_divisor!=(n/i))
                cout<<(n/i)<<" ";
        }
    }
    cout<<endl;
}

void all_divisors_sorted_oo(int n){ //in sorted order
    int i;
    for(i=1;i*i<n;i++){
        if(n%i==0){
            cout<<i<<" ";
        }
    }
    for(;i>=1;i--){
        if(n%i==0){
                cout<<(n/i)<<" ";
        }
    }
    cout<<endl;
}
int main(){
    all_divisors(6);
    all_divisors(12);
    all_divisors(100);
    all_divisors(7);
    all_divisors_sorted_oo(15);
    all_divisors_sorted_oo(100);
    all_divisors_sorted_oo(7);
}
