#include<iostream>
using namespace std;


int minFlips_naive(int a[],int n){
    int zerogroup=0;
    int onegroup=0;
    for(int i=0;i<n;i++){
        if(a[i]==0){
            while(i<n && a[i]==0){i++;}
            zerogroup++;
            i--;
        }
        else{
            while(i<n && a[i]==1){i++;}
            onegroup++;
            i--;
        }
    }
    int whichToFlip=zerogroup<=onegroup ? 0 : 1;
        for(int i=0;i<n;i++){
            if(a[i]==whichToFlip){
                cout<<"from "<<i<<" to ";
                while(a[i]==whichToFlip){i++;}
                i--;
                cout<<i<<endl;
            }
        }
    return 0;
}
int minFlips(int a[],int n){
    //always flip the second group...
    int whichToFlip;
    if(a[0]==0)
        whichToFlip=1;
    else
        whichToFlip=0;
    for(int i=0;i<n;i++){
        if(a[i]==whichToFlip){
            cout<<"from "<<i<<" to ";
            while(i<n && a[i]==whichToFlip){i++;}
            i--;
            cout<<i<<endl;
            }
        }
    return 0;
}

//OR
/*
void printGroups(int arr[], int n)//geeks sol
{
	for(int i = 1; i < n; i++)
	{
		if(arr[i] != arr[i - 1])
		{
			if(arr[i] != arr[0])
                cout << "From " << i << " to ";
			else
                cout << i - 1 << endl;
		}
	}

	if(arr[n - 1] != arr[0])
        cout << n - 1 << endl;
}
*/
int main(){
int a[]={0,1,1,0,1,0,1,0,1,1,1,0,0};
//int a[]={1,1,1,1,1,1,1,1,1,1,1,1,1};
//int a[]={1,0,1,0,1,0,1,0,1,0,1,0};
minFlips(a,12);
}
