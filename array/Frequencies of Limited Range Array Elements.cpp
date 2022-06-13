// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
class Solution{//see youtube video (playlist DRA prep) => frequency of limited range
    public:
    //Function to count the frequency of all elements from 1 to N in the array.
    void frequencyCount(vector<int>& arr,int N, int P)
    {
        int pointIndex=0;
       while(pointIndex<N){
           while(arr[pointIndex]<=0){pointIndex++;}
           if(pointIndex<N && arr[pointIndex]<=N){
               if(arr[arr[pointIndex]-1]<0){
                    arr[arr[pointIndex]-1]+=-1;
                   arr[pointIndex]=0;
               }
                else{

                    if(pointIndex!=arr[pointIndex]-1){
                    int temp=arr[arr[pointIndex]-1];
                   arr[arr[pointIndex]-1]=-1;
                   arr[pointIndex]=temp;
                    }else{
                        arr[arr[pointIndex]-1]=-1;
                    }

                }

                }
           else{
               if(pointIndex<N)
               arr[pointIndex]=0;
           }
       }
       for(int i=0;i<N;i++){
           if(arr[i]<0)
           arr[i]=-arr[i];
        }
       }
};


// { Driver Code Starts.

int main()
{
	long long t;

	//testcases
	cin >> t;

	while(t--){

	    int N, P;
	    //size of array
	    cin >> N;

	    vector<int> arr(N);

	    //adding elements to the vector
	    for(int i = 0; i < N ; i++){
	        cin >> arr[i];
	    }
        cin >> P;
        Solution ob;
        //calling frequncycount() function
		ob.frequencyCount(arr, N, P);

		//printing array elements
	    for (int i = 0; i < N ; i++)
			cout << arr[i] << " ";
	    cout << endl;
	}
	return 0;
}




  // } Driver Code Ends// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
class Solution{
    public:
    //Function to count the frequency of all elements from 1 to N in the array.
    void frequencyCount(vector<int>& arr,int N, int P)
    {
        int pointIndex=0;
       while(pointIndex<N){
           while(arr[pointIndex]<=0){pointIndex++;}
           if(pointIndex<N && arr[pointIndex]<=N){
               if(arr[arr[pointIndex]-1]<0){
                    arr[arr[pointIndex]-1]+=-1;
                   arr[pointIndex]=0;
               }
                else{

                    if(pointIndex!=arr[pointIndex]-1){
                    int temp=arr[arr[pointIndex]-1];
                   arr[arr[pointIndex]-1]=-1;
                   arr[pointIndex]=temp;
                    }else{
                        arr[arr[pointIndex]-1]=-1;
                    }

                }

                }
           else{
               if(pointIndex<N)
               arr[pointIndex]=0;
           }
       }
       for(int i=0;i<N;i++){
           if(arr[i]<0)
           arr[i]=-arr[i];
        }
       }
};


// { Driver Code Starts.

int main()
{
	long long t;

	//testcases
	cin >> t;

	while(t--){

	    int N, P;
	    //size of array
	    cin >> N;

	    vector<int> arr(N);

	    //adding elements to the vector
	    for(int i = 0; i < N ; i++){
	        cin >> arr[i];
	    }
        cin >> P;
        Solution ob;
        //calling frequncycount() function
		ob.frequencyCount(arr, N, P);

		//printing array elements
	    for (int i = 0; i < N ; i++)
			cout << arr[i] << " ";
	    cout << endl;
	}
	return 0;
}




  // } Driver Code Ends
