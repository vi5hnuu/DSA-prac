#include<iostream>
#include<algorithm>
using namespace std;

template<class T>
class Comparator{
public:
    int operator ()(T x1,T x2){
      /*
      negative tells that x1 comes before x2
      positive tells x2 comes before x1
      0 tells they are equal anc will be placed as per algorithm
      */
      return x1-x2; //-1, 0, 1
    }
};

template<class T>
bool funComparator(T x1,T x2){//return type is bool
        //return x1-x2;
    /*
    if(x1==x2)
        return 0;
    else if(x1<x2)
        return -1;
    else
        return 1;
        */
    return x1<=x2;
}

void show(int a[],int array_size){
    for(int i=0;i<array_size;i++){
            cout<<a[i]<<" ";
    }
}

int main(){
    int a[]={1,5,8,9,6,7,3,4,2,0};
    int asize=sizeof(a)/sizeof(int);
    cout<<"The array before sorting is : ";show(a,asize);
    cout<<endl<<"The array after sorting is(asc) :";sort(a,a+asize);show(a,asize);
    cout<<endl<<"The array after sorting is(desc) :";sort(a,a+asize,greater<int>());show(a,asize);
    cout<<endl<<"The array after sorting is(asc but our comparator class) :";sort(a,a+asize,Comparator<int>());show(a,asize);
    cout<<endl<<"The array after sorting is(asc but our comparator function) :";sort(a,a+asize,funComparator<int>);show(a,asize);

    return 0;
}
