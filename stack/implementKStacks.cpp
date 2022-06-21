#include<iostream>
using namespace std;

class KStack{
  int *arr,*top,*next;
  int k,freetop,cap;
  public:
  KStack(int k1,int n){
    k=k1,cap=n;
    arr=new int[cap];
    top=new int[k];
    next=new int[cap];
    for(int i=0;i<k;i++)
    top[i]=-1;
    freetop=-1;
    for(int i=0;i<cap-1;i++)
    next[i]=i+1;
    next[cap-1]=-1;
  }
  ~KStack(){
    delete[] arr;
    delete[] top;
    delete[] next;
  }
  void push(int data,int sn){
    int i=freetop;
    freetop=next[i];
    next[i]=top[sn];
    top[sn]=i;
    arr[i]=data;
  }
  int pop(int sn){
      int i=top[sn];
      top[sn]=next[i];
      next[i]=freetop;
      freetop=i;
      return arr[i];
  }
};