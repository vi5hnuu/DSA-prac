#include<iostream>
#include<queue>
using namespace std;

/*
given a set of {5,6}
you have to generate numbers in increasing order using those set of elements.
*/

void printFirstN(int n){
  queue<string> q;
  q.push("5");
  q.push("6");
  while(n>0){
    string x=q.front();
    q.pop();
    q.push(x+"5");
    q.push(x+"6");
    cout<<x<<" ";
    n--;
  }
}

int main(){
  printFirstN(10);
}