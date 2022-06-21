// { Driver Code Starts
//Initial Template for C++

#include <bits/stdc++.h>
#include <string>

using namespace std;

/*
Given a keypad as shown in the diagram, and an N digit number which is represented by array a[ ], the task is to list all words which are possible by pressing these numbers.
//phonedigits.png


Input: N = 3, a[] = {2, 3, 4}
Output:
adg adh adi aeg aeh aei afg afh afi 
bdg bdh bdi beg beh bei bfg bfh bfi 
cdg cdh cdi ceg ceh cei cfg cfh cfi 
Explanation: When we press 2,3,4 then 
adg, adh, adi, ... cfi are the list of 
possible words.
Example 2:

Input: N = 3, a[] = {3, 4, 5}
Output:
dgj dgk dgl dhj dhk dhl dij dik dil 
egj egk egl ehj ehk ehl eij eik eil 
fgj fgk fgl fhj fhk fhl fij fik fil
Explanation: When we press 3,4,5 then 
dgj, dgk, dgl, ... fil are the list of 
possible words.
*/

class Solution
{
    private:
        string getAlphabets(int n){
            switch(n){
                case 0:
                case 1:return "";
                case 2:return "abc";
                case 3:return "def";
                case 4:return "ghi";
                case 5:return "jkl";
                case 6:return "mno";
                case 7:return "pqrs";
                case 8:return "tuv";
                case 9:return "wxyz";
                
            }
        }
    
    void helper(int a[],int N,vector<string> &res,string str,int k=0){
        if(k==N){
            res.push_back(str);
            return;
        }
        
        for(int i=0;i<getAlphabets(a[k]).length();i++){
            helper(a,N,res,str+getAlphabets(a[k])[i],k+1);
        }
    }
    public:
    //Function to find list of all words possible by pressing given numbers.
    vector<string> possibleWords(int a[], int N)
    {
            vector<string> possibleWords;
            helper(a,N,possibleWords,"");
            return possibleWords;
    }
};


// { Driver Code Starts.

int main() {
  
	int T;
	
	cin >> T; //testcases
	
	while(T--){ //while testcases exist
	   int N;
	    
	   cin >> N; //input size of array
	   
	   int a[N]; //declare the array
	   
	   for(int i =0;i<N;i++){
	       cin >> a[i]; //input the elements of array that are keys to be pressed
	   }
	   
	   Solution obj;
	   
	  vector <string> res = obj.possibleWords(a,N);
	  for (string i : res) cout << i << " ";
	   cout << endl;
	}
	
	return 0;
}  // } Driver Code Ends