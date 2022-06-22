// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

struct petrolPump
{
    int petrol;
    int distance;
};


 // } Driver Code Ends
/*
The structure of petrolPump is 
struct petrolPump
{
    int petrol;
    int distance;
};*/

/*You are required to complete this method*/
class Solution{
  public:
  
     //TLE
    /* 
     int tour(petrolPump p[],int n)
    {
       for(int start=0;start<n;start++){
        int cur_petrol=0;
        int end=start;
        while(true){
          cur_petrol+=(p[end].petrol-p[end].distance);
          if(cur_petrol<0)
            break;
          end=(end+1)%n;
          if(end==start)
            return start;
        }
       }
        return -1;
    }
    */
    //if pi is invalid petrol pump than all 0 to pi-1 are invalid think why
    int tour(petrolPump p[],int n)
    {
        int prev_petrol=0;
        int cur_petrol=0;
        int start=0;
        for(int i=0;i<n;i++){
            cur_petrol+=(p[i].petrol-p[i].distance);
            if(cur_petrol<0){
                prev_petrol+=cur_petrol;
                start=i+1;
                cur_petrol=0;
            }
        }
        return (prev_petrol+cur_petrol>=0) ? start:-1;

    }
};



// { Driver Code Starts.

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        petrolPump p[n];
        for(int i=0;i<n;i++)
            cin>>p[i].petrol>>p[i].distance;
        Solution obj;
        cout<<obj.tour(p,n)<<endl;
    }
}
  // } Driver Code Ends