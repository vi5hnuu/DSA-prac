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

    //Function to find list of all words possible by pressing given numbers.
    vector<string> possibleWords(int a[], int N)
    {
            vector<string> possibleWords;
            helper(a,N,possibleWords,"");
            return possibleWords;
    }
