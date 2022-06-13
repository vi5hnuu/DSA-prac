#include<iostream>
#include<vector>

using namespace std;

void pVector(const vector<int> &x){
    for(int ele:x)
        cout<<ele;
    cout<<endl;
}

int main(){
    vector<int> g1;

    for(int i=1;i<=5;i++){
        g1.push_back(i);
    }
    pVector(g1);
    cout<<"Size : "<<g1.size()<<endl;
    cout<<"Capacity : "<<g1.capacity()<<endl;
    cout<<"Max size : "<<g1.max_size()<<endl;

    g1.resize(4);
    pVector(g1);
    cout<<"Size : "<<g1.size()<<endl;
    cout<<"Capacity : "<<g1.capacity()<<endl;
    cout<<"Max size : "<<g1.max_size()<<endl;

    g1.resize(7);
    pVector(g1);
    cout<<"Size : "<<g1.size()<<endl;
    cout<<"Capacity : "<<g1.capacity()<<endl;
    cout<<"Max size : "<<g1.max_size()<<endl;

    if(g1.empty())
        cout<<"Vector is empty.\n";
    else
        cout<<"Vector is not empty.\n";

    g1.reserve(100);
    cout<<"Size : "<<g1.size()<<endl;
    cout<<"Capacity : "<<g1.capacity()<<endl;
    cout<<"Max size : "<<g1.max_size()<<endl;

    g1.shrink_to_fit();
    cout<<"Size : "<<g1.size()<<endl;
    cout<<"Capacity : "<<g1.capacity()<<endl;
    cout<<"Max size : "<<g1.max_size()<<endl;

    return 0;
}
