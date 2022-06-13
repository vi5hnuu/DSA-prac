#include<iostream>
using namespace std;


void solution(string str,string asf,int countt,int pos){
    if(pos==str.length()){
        if(countt==0)
        cout<<asf<<endl;
        else{
        cout<<(asf+to_string(countt))<<endl;
        }
        return;
    }
    if(countt>0)
    solution(str,asf+to_string(countt)+str[pos],0,pos+1);
    else
    solution(str,asf+str[pos],0,pos+1);

    solution(str,asf,countt+1,pos+1);
}

int main(){
string input;
cin>>input;

solution(input,"",0,0);

}
