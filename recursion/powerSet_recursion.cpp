#include<iostream>
using namespace std;

void powerSet(string &str,string res="",int pos=0){
    if(pos==str.length()){
        cout<<(res)<<endl;
        return;
    }

    powerSet(str,res,pos+1);
    powerSet(str,res+str[pos],pos+1);
}


int main(){
    string str="abc";
    powerSet(str);

    return 0;
}
