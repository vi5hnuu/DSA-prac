#include<iostream>
#include<math.h>
using namespace std;

int digitsInFactorial(int N)
    {
        double count=0;
        for(int i=1;i<=N;i++){
            count+=log10(i);
            cout<<log10(i)<<endl;
        }

        return int(count)+1;
    }


    int main(){
        cout<<digitsInFactorial(10)<<endl;
        cout<<digitsInFactorial(20)<<endl;
        cout<<digitsInFactorial(500)<<endl;
    }
