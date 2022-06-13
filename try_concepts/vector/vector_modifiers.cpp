#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> v;
    v.assign(5,10);
    cout<<"The vector elemets are : ";
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<" ";
    }

    v.push_back(15);
    int n=v.size();
    cout<<"\nThe last element is : "<<v[n-1];

    v.pop_back();

    cout<<"\nThe vector elements are : ";
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<" ";
    }
    v.insert(v.begin(),5);
    cout<<"\The first element is : "<<v[0];

    v.erase(v.begin());

    cout<<"\nThe first element is : "<<v[0];

    v.emplace(v.begin(),5);
    cout<<"\nThe first element is : "<<v[0];

    v.emplace(v.begin()+1,15);
    cout<<"\nThe second element is : "<<v[1];

    v.emplace_back(20);
    n=v.size();
    cout<<"\nThe last element is  : "<<v[n-1];

    v.clear();
    cout<<"\nVector size after clear : "<<v.size();

    vector<int> v1={1,2},v2={3,4};
    cout<<"\n\nVector 1 : ";
    for(int i=0;i<v1.size();i++)
        cout<<v1[i]<<" ";
    cout<<"\n\nVector 2 : ";
    for(int i=0;i<v2.size();i++)
        cout<<v2[i]<<" ";

    v1.swap(v2);

    cout<<"\n\nAfter swap Vector 1 : ";
    for(int i=0;i<v1.size();i++)
        cout<<v1[i]<<" ";
    cout<<"\n\nAfter swap Vector 2 : ";
    for(int i=0;i<v2.size();i++)
        cout<<v2[i]<<" ";

    v1={1,2,3,4},v2={3,4};
    cout<<"\n\nVector 1 : ";
    for(int i=0;i<v1.size();i++)
        cout<<v1[i]<<" ";
    cout<<"\nIts size : "<<v1.size();
    cout<<"\n\nVector 2 : ";
    for(int i=0;i<v2.size();i++)
        cout<<v2[i]<<" ";
    cout<<"\nIts size : "<<v2.size();

    v1.swap(v2);

    cout<<"\n\nAfter swap Vector 1 : ";
    for(int i=0;i<v1.size();i++)
        cout<<v1[i]<<" ";
    cout<<"\nIts size after swap : "<<v1.size();
    cout<<"\n\nAfter swap Vector 2 : ";
    for(int i=0;i<v2.size();i++)
        cout<<v2[i]<<" ";
    cout<<"\nIts size after swap : "<<v2.size();

    return 0;
}
