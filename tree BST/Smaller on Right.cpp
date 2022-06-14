#include<bits/stdc++.h>
using namespace std;

/*
Given an array arr[] of N elements. The task is to count maximum number of distinct smaller elements on right side of any array element.
For example, in {10, 6, 9, 7, 20, 19, 21, 18, 17, 16},
the result is 4.  Note that 20 has maximum
4 smaller elements on right side. Other elements have less count, for example 10 has 3 smaller elements on right side.
*/

int helper(int arr[],int n){
    int count1=0;
    set<int> s;
    for(int i=n-1;i>=0;i--){
        s.insert(arr[i]);
        auto it=s.find(arr[i]);
        int count2=distance(s.begin(),it);
        count1=max(count1,count2);
    }
    return count1;
}

int main()
{
//code
int num;
cin>>num;
while(num--)
{
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)
        cin>>arr[i];
  cout<<helper(arr,n)<<endl;
}
return 0;
}
