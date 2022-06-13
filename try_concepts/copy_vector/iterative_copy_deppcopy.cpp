#include<iostream>
#include<vector>
using namespace std;


int main(){
    vector<int> vet1{1,2,3,4};
    vector<int> vect2;

    for(int i=0,len=vet1.size();i<len;i++)
    vect2.push_back(vet1[i]);

    cout<<"Old vector emelnts are : ";
    for(int i=0,len=vet1.size();i<len;i++){
        cout<<vet1[i]<<" ";
    }
    cout<<endl;

    cout<<"New vector elements are : ";
    for(int i=0;i<vect2.size();i++)
    cout<<vect2[i]<<" ";
    cout<<endl;

    vet1[0]=2;
    cout << "The first element of old vector is :";
    cout << vet1[0] << endl;
    cout << "The first element of new vector is :";
    cout << vect2[0] <<endl;

    return 0;
}
