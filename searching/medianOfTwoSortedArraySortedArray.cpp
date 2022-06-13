#include<iostream>
using namespace std;

/*
example 1.
a1[]={10,20,30,40,50}
a2[]={5,15,25,35,45}

temp[]={5,10,15,20,25,30,35,40,45,50}
med=27.5

example 2.
a1[]={1,2,3,4,5,6}
a2[]={10,20,30,40,50}

temp[]={1,2,3,4,5,6,10,20,30,40,50}
med=6.0
*/

double medianSorted(int a1[],int n1,int a2[],int n2){
    int temp[n1+n2];
    int k=0;
    int i,j;
    for(i=0,j=0;i<n1 && j<n2;){
        if(a1[i]==a2[j]){
            temp[k++]=a1[i];
            temp[k++]=a2[j];
            i++;j++;
        }
        else if(a1[i]<a2[j]){
            temp[k++]=a1[i];
            i++;
        }
        else{
            temp[k++]=a2[j];
            j++;
        }
    }
    if(i<n1){
        while(i<n1){
            temp[k++]=a1[i];
            i++;
        }
    }
    if(j<n2){
        while(j<n2){
            temp[k++]=a2[j];
            j++;
        }
    }
    bool isLengthEven=((n1+n2) & 1) == 0;
    return isLengthEven ? (temp[(n1+n2)/2]*1.0+temp[(n1+n2)/2-1])/2 : temp[(n1+n2)/2];
}


double medianSorted_o(int a1[],int n1,int a2[],int n2){
    if(n1>n2){
     swap(a1,a2);
     swap(n1,n2);
    }

    int begin1=0,end1=n1;
    while(begin1<=end1){
        int i1=(begin1+end1)/2;
        int i2=(n1+n2+1)/2-i1;
        int min1=(i1==n1) ? INT_MAX:a1[i1];
        int max1=(i1==0) ? INT_MIN : a1[i1-1];

        int min2=(i2==n2) ? INT_MAX:a2[i2];
        int max2=(i2==0) ? INT_MIN : a2[i2-1];

        if(max1<=min2 && max2<=min1){
            if((n1+n2)%2==0){
                return (max(max1,max2)*1.0+min(min1,min2))/2;
            }
            else{
                return max(max1,max2)*1.0;
            }
        }
        else if(max1>min2)
            end1=i1-1;
        else
            begin1=i1+1;
    }
}

int main(){
    int a1[]={10,20,30,40,50};
    int a2[]={5,15,25,35,45};
    cout<<medianSorted(a1,5,a2,5)<<endl;
    cout<<medianSorted_o(a1,5,a2,5)<<endl;


    int aa1[]={1,2,3,4,5,6};
    int aa2[]={10,20,30,40,50};
    cout<<medianSorted(aa1,6,aa2,5)<<endl;
    cout<<medianSorted_o(aa1,6,aa2,5)<<endl;

    return 0;
}
