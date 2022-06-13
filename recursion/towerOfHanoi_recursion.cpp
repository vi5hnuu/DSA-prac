#include<iostream>
using namespace std;

void move(int n,char from,char usingg,char to){
    if(n==1){
        cout<<"Move disc "<<n<<" from "<<from<<" to "<<to<<endl;
        return;
    }

    move(n-1,from,to,usingg);
    cout<<"Move disc "<<n<<" from "<<from<<" to "<<to<<endl;
    move(n-1,usingg,from,to);
}

/*
  long long toh(int N, int from, int to, int aux) {
        long long moves=1;
        if(N==1){
            cout<<"move disk 1 from rod 1 to rod 2"<<endl;
            return 1;
        }

        moves+=toh(N-1,from,aux,to);
        cout<<"move disk "<<N<<" from rod "<<from<<" to rod "<<to<<endl;
        moves+=toh(N-1,aux,to,from);
        return moves;
    }
*/

int main(){
    move(5,'A','B','C');
}
