#include<iostream>
using namespace std;


bool tripletSum(int arr[],int n,int x){
    bool solutionFound=false;
    for(int i=0;i<n-2;i++)
    for(int j=i+1;j<n-1;j++)
    for(int k=j+1;k<n;k++)
    if(arr[i]+arr[j]+arr[k]==x){
            solutionFound=true;
        cout<<"i : "<<i<<" j : "<<j<<" k : "<<k<<endl;
        //return true; //or search another pair
    }
    if(solutionFound)
        return true;
    return false;
}

//for unsorted we first sort (nlogn) then apply this method (n^2)
bool tripletSum_threepointer(int arr[],int n,int x){
    bool solutionSound=false;
    for(int i=0;i<n-2;i++){
        int p=i+1;
        int q=n-1;
        int targetSum=x-arr[i];
        while(p<q){
            if(arr[p]+arr[q]==targetSum){
                    solutionSound=true;
                cout<<"i : "<<i<<" j : "<<p<<" k : "<<q<<endl;
                //return true;

                break;//or search for other pairs(solutionFound var is used to return true at end)
                //if 3(p) 3 7 7(q) = > 3 3(p) 7(q) 7 elements repeat we do no break we do p++;q--;
                //we break if elements are distinct
                //we return true if we just want to know if there exist such pair
            }
            else if(arr[p]+arr[q]>targetSum){
                q--;
            }
            else{
                p++;
            }
        }
    }
    if(solutionSound)
        return true;
    return false;
}

int main(){
    int arr[]={2,3,4,8,9,20,40};
    cout<<(tripletSum(arr,7,32)==1 ? "Yes" : "No")<<endl;
    cout<<(tripletSum_threepointer(arr,7,32)==1 ? "Yes" : "No")<<endl;

    return 0;
}
