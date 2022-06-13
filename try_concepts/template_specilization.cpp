/*
#include<iostream>
using namespace std;

template<class T>
void fun(T a){
    cout<<"The main template fun(): "<<a<<endl;
}

template<>//try removing this
void fun(int a){
    cout<<"Specilized template for int type :"<<a<<endl;
}

int main(){
fun<char>('a');
fun<int>(10);
fun<float>(10);
}
*/

#include<iostream>
using namespace std;

template<class T>
void fun(T a){
    cout<<"The main template fun(): "<<a<<endl;
}

template<>//try removing this
void fun<int>(int a){
    cout<<"Specilized template for int type :"<<a<<endl;
}

int main(){
fun<char>('a');
fun<int>(10);
fun<float>(10);
}

/*
#include<iostream>
using namespace std;

template<class T>
class Test{
public:
    Test(){
        cout<<"general template object.\n";
    }
};

template<>
class Test<int>{
public:
    Test(){
        cout<<"Specilized template object of int.\n";
    }
};

int main(){
Test<int> a;
Test<char> b;
Test<float> c;

return 0;
}
*/
