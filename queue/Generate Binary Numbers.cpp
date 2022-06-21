// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;



 /*
 Input:
N = 5
Output: 
1 10 11 100 101
Explanation: 
Binary numbers from
1 to 5 are 1 , 10 , 11 , 100 and 101.
 */
//Function to generate binary numbers from 1 to N using a queue.
vector<string> generate(int N)
{
    if(N<=1)
        return {"1"};
	vector<string> bin;
	bin.push_back("1");
	int i=0,count=1;
	while(count<=N){
	    string x=bin[i];
	    bin.push_back(x+"0");
	    count++;
	    if(count==N)
	    break;
	    bin.push_back(x+"1");
	    count++;
	    if(count==N)
	    break;
	    i++;
	}
	return bin;
}


// { Driver Code Starts.

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		vector<string> ans = generate(n);
		for(auto it:ans) cout<<it<<" ";
		cout<<endl;
	}
	return 0;
}  // } Driver Code Ends