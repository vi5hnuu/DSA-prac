#include<iostream>
#include<vector>
using namespace std;


vector<int> twoOddOccuring(vector<int> &input){
    int res=0;
    for(int x:input){
        res^=x;
    }
    //turnoff all bits except last set bit
    res=res & ~(res-1); // eg res=10110110 => 10110110 & ~10110101 => 10110110 & 01001010 => 00000010

    int res1=0;
    int res2=0;
    for(int x:input){
        if((x & res)!=0)
            res1^=x;
        else{
            res2^=x;
        }
    }
    return {res1,res2};
}
vector<int> findOddOccuringOne_naive(vector<int> &input){
    vector<int> res;
    for(int x:input){
            int count=0;
    for(int y:input){
        if(x==y)
            count++;
        }
        if(count & 1)
            res.push_back(x);
    }
    return res;
}

int main(){
    vector<int> input={4,3,4,4,4,7,5,5};
    vector<int> otpt=twoOddOccuring(input);
    for(int x:otpt)
        cout<<x<<" ";
    cout<<endl;
}
