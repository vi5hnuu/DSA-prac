void AllPossibleStrings(string &S,vector<string> &res,string s="",int index=0){
            //every character has two choice => take it or leave it
            if(S.length()==index){
                if(s!="")
                res.push_back(s);
                return;
            }
            AllPossibleStrings(S,res,s+S[index],index+1);
            AllPossibleStrings(S,res,s,index+1);
        }

		vector<string> AllPossibleStrings(string s){
		    vector<string> res;
		    AllPossibleStrings(s,res);
		    sort(res.begin(),res.end());
		    return res;
		}

/*
Given a string S find all possible subsequences of the string in lexicographically-sorted order.
*/
