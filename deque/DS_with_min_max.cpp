/*
design a data structure such that getmin and getmax is o(1)
it is give that successive min is always less than cur min and succ max in input is alway greater that cur max.
*/
#include<iostream>
#include<deque>
using namespace std;

class DD{
  private:
    deque<int> dq;
  public:
    int getMin()const{
      if(!dq.empty())
      return dq.front();
      return -1;
    }
    int getMax()const{
      if(!dq.empty())
      return dq.back();
      return -1;
    }
    int extrachMin(){
      if(!dq.empty()){
        int x = dq.front();
        dq.pop_front();
        return x;
      }
      return -1;
    }
    int extrachMax(){
      if(!dq.empty()){
        int x = dq.back();
        dq.pop_back();
        return x;
      }
      return -1;
    }
    void insertMax(int data){
      dq.push_back(data);
    }
    void insertMin(int data){
      dq.push_front(data);
    }
};