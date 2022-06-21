// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;


 // } Driver Code Ends


class Solution
{
    public:
    //naive = > TLE
    /*vector <int> calculateSpan(int price[], int n)//O(n^2)
    {
       vector<int> res(n,0);
       res[0]=1;
       for(int i=1;i<n;i++){
           int count=0;
           for(int j=i;j>=0 && price[i]>=price[j];j--){
            count++;
           }
           res[i]=count;
       }
       return res;
    }*/
    
    
    //concept => find the nearest big on left and  now visualize the solution
    vector <int> calculateSpan(int price[], int n)//O(N)
    {
       vector<int> res(n,0);
       stack<int> indexes;
       /*
       if stack is empty then no big on left means total span is index+1
       else span curIndex-indexOfBig(top of stack)
       */
       for(int i=0;i<n;i++){
           if(indexes.empty()){
                res[i]=i+1;
           }else{
               while(!indexes.empty() && price[indexes.top()]<=price[i]){
                   indexes.pop();
               }
               if(indexes.empty())
                res[i]=i+1;
               else{
                res[i]=i-indexes.top();
               }
                
           }
                indexes.push(i);
       }
       return res;
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
		int i,a[n];
		for(i=0;i<n;i++)
		{
			cin>>a[i];
		}
		Solution obj;
		vector <int> s = obj.calculateSpan(a, n);
		
		for(i=0;i<n;i++)
		{
			cout<<s[i]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
  // } Driver Code Ends