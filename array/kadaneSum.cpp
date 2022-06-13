#include<iostream>
using namespace std;


int kadMaxSum(int arr[],int n){
    int res = arr[0];
	int maxEnding = arr[0];

	for(int i = 1; i < n; i++){
		maxEnding = max(maxEnding + arr[i], arr[i]);
		res = max(maxEnding, res);
	}
	return res;
}

int main(){
    int a[]={-1,-2,-3};
    cout<<kadMaxSum(a,3)<<endl;

    return 0;
}
