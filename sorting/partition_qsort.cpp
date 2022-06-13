#include<iostream>
using namespace std;

ostream& operator <<(ostream &out,int arr[]){
    int sz=9;//flaw use vector instead so that size can be known
    for(int i=0;i<sz;i++){
        out<<arr[i]<<" ";
    }
    cout<<endl;
    return out;
}

int partition(int arr[],int low,int high){//not stable //pivot is first element
    int pivotEle=arr[low];
    int count=0;//Elements less than or equal to pivot
    for(int i=low+1;i<=high;i++){
        if(arr[i]<=pivotEle){
            count++;
        }
    }
    int pivotIndex=low+count;
    swap(arr[low],arr[pivotIndex]);

    int p=low,q=high;
    while(p<pivotIndex && q>pivotIndex){
        while(p<pivotIndex && arr[p]<=pivotEle){p++;}
        while(q>pivotIndex && arr[q]>pivotEle){q--;}
         if(p<pivotIndex && q>pivotIndex){
            swap(arr[p++],arr[q--]);
        }
    }
    return pivotIndex;
}

int partition_ns(int arr[],int low,int high,int pi){//not stable //pivot index is p
    int pivotEle=arr[pi];
    int count=0;//Elements less than or equal to pivot
    for(int i=low;i<=high;i++){
        if(i!=pi && arr[i]<=pivotEle){
            count++;
        }
    }
    int pivotIndex=low+count;
    swap(arr[pi],arr[pivotIndex]);

    int p=low,q=high;
    while(p<pivotIndex && q>pivotIndex){
        while(p<pivotIndex && arr[p]<=pivotEle){p++;}
        while(q>pivotIndex && arr[q]>pivotEle){q--;}
         if(p<pivotIndex && q>pivotIndex){
            swap(arr[p++],arr[q--]);
        }
    }
    return pivotIndex;
}
int partition(int arr[],int low,int high,int pi){//stable //pivot index is p
   int temp[high-low+1],index=0;
   for(int i=low;i<=high;i++){
    if(arr[i]<arr[pi]){
            temp[index++]=arr[i];
    }
   }
   for(int i=low;i<=high;i++){
    if(arr[i]==arr[pi]){
            temp[index++]=arr[i];
    }
   }

   int posOfPivot=low+index-1;
   for(int i=low;i<=high;i++){
    if(arr[i]>arr[pi]){
        temp[index++]=arr[i];
    }
   }

   for(int i=low;i<=high;i++){
    arr[i]=temp[i-low];
   }

   return posOfPivot;
}
int main(){
int arr[]={12,11,15,16,18,71,35,12,15};
//partition(arr,0,8);
cout<<"index of pivot  :"<<partition(arr,0,8,6)<<endl;

cout<<arr;

return 0;
}
