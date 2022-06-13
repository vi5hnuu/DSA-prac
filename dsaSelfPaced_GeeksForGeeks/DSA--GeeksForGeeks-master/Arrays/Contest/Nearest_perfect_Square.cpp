#include<bits/stdc++.h>
using namespace std;
///////////////////////////////////////////////
/*
bool isperfect(int N){
    if((sqrt(N)-floor(sqrt(N)))!=0){
        return false;
    }
    return true;
}

void getClosestPerfectSquare(int N){
    if(isperfect(N)){
        cout<<N<<" "<<"0"<<endl;
        return;
    }
    int aboveN=-1,belowN=-1;
    int n1;
    n1=N+1;
    while(true){
        if(isperfect(n1)){
            aboveN=n1;
            break;
        }
        else
            n1++;
    }
    n1=N-1;
    while(true){
        if(isperfect(n1)){
            aboveN=n1;
            break;
        }
        else
            n1--;
    }

    int diff1=aboveN-N;
    int diff2=N-belowN;
    if(diff1>diff2)
        cout<<belowN<<" "<<diff2;
    else
        cout<<aboveN<<" "<<diff1;
}
*/
///////////////////////////////////////////////
void getClosestPerfectSquare(int N){
    int x=sqrt(N);
    if((x*x)==N){
        cout<<N<<" "<<0;
        return;
    }
    int aboveN=(x+1)*(x+1),belowN=x*x;
    int diff1=aboveN-N;
    int diff2=N-belowN;
    if(diff1>diff2)
        cout<<belowN<<" "<<diff2;
    else
        cout<<aboveN<<" "<<diff1;
}

//////////////////////////////////////////////
long long int NearestPerfectSquare(long long int N){

	long long int abovenumBER = ceil(sqrt(N+1)) * ceil(sqrt(N+1));
	long long int belownumBER = floor(sqrt(N-1)) * floor(sqrt(N-1));

	long long int difference_1 = N - abovenumBER;
	long long int difference_2 = belownumBER - N;

	if(difference_1 == difference_2){
		return belownumBER;
	}else if(difference_1 > difference_2){
		return abovenumBER;
	}else{
		return belownumBER;
	}
}


int main(){

	int T;
	cin>>T;
	while(T--){
		long long int N;
		cin>>N;
		cout<<NearestPerfectSquare(N)<<endl;

	}

	return 0;
}
