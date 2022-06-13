#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> g1;

    for (int i = 1; i <= 10; i++)
        g1.push_back(i * 10);

    cout << "\nReference operator [g] : g1[2] = " << g1[2];
    g1[2]=4;
    cout << "\nat : g1.at(4) = " << g1.at(4);
    g1.at(4)=8;
    cout << "\nfront() : g1.front() = " << g1.front();
    g1.front()=0;
    cout << "\nback() : g1.back() = " << g1.back();
    g1.back()=500;

    cout << "\nReference operator [g] : g1[2] = " << g1[2];
    cout << "\nat : g1.at(4) = " << g1.at(4);
    cout << "\nfront() : g1.front() = " << g1.front();
    cout << "\nback() : g1.back() = " << g1.back();

    int *pos=g1.data();
    pos[0]=78;
    *(pos+g1.size()-1)=999;
    cout<<"\nFirst element changed :"<<g1[0]<<endl;
    cout<<"\Last element changed :"<<g1[g1.size()-1]<<endl;

    return 0;
}
