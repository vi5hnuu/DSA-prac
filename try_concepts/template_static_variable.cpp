/*
#include<iostream>
using namespace std;

template<typename T>
void fun(const T& x){
    static int i=10+x;
    cout<<++i;
    return;
}

int main(){
fun<int>(1);
cout<<endl;
fun<int>(2);
cout<<endl;
fun<double>(1.1);
cout<<endl;
fun<double>(2.2);

return 0;
}

*/


#include<iostream>
using namespace std;

template<class T>
class Test{
private:
    T val;
public:
    static int count;
    Test(){
        count++;
        cout<<count<<endl;
    }
};

template<class T>
int Test<T>::count=0;

int main(){
    Test<int> a;
    Test<int> b;
    Test<double> c;
    Test<double> d;
}
