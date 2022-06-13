#include<iostream>
using namespace std;

int secondLargestEleIndex_naive(int array[],int n){
    if(n<2)
        return -1;
    int first=0;
    int second=-1;
    //for first
    for(int i=1;i<n;i++){
        if(array[i]>array[first]){
            first=i;
        }
    }
    //for second
    for(int i=0;i<n;i++){
        if(array[i]!=array[first]){
            if(second==-1){
                second=i;
            }
            else if(array[i]>array[second]){
                second=i;
            }
        }
    }
    return second;
}


int secondLargestEleIndex(int array[],int n){
    if(n<2)
        return -1;
    int first=array[0]>array[1] ? 0 : 1;
    int second=array[0]>array[1] ? 1 : 0;
    for(int i=2;i<n;i++){
        if(array[i]<array[first] && array[first]==array[second]){
            second=i;
        }
        else if(array[i]>array[first]){
            second=first;
            first=i;
        }
    }
    if(array[first]==array[second])
        return -1;
    return second;
}

//compact
int secondLargestEleIndex_c(int array[],int n){
    if(n==0)
        return -1;
    int first=0;
    int second=-1;
    for(int i=1;i<n;i++){
      if(array[i]>array[first]){
        second=first;
        first=i;
      }
      else if(array[i]!=array[first]){
        if(second==-1 || array[i]>array[second]){
            second=i;
        }
      }
    }
    return second;
}

int main(){
    //int input[]={1,2,5,8,4,9,6,3,2};
    //int input[]={12,12,12,12,2};
    int input[]={10,10,10};
    cout<<secondLargestEleIndex_c(input,3)<<endl;
    //cout<<input[secondLargestEleIndex_c(input,3)]<<endl;

    return 0;
}
