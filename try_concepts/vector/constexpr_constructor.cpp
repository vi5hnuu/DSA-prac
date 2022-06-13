#include<bits/stdc++.h>
using namespace std;

class Rectangle{
private:
    int _h,_w;
public:
    constexpr Rectangle(int h,int w):_h(h),_w(w){}
    constexpr int getArea() const {return _h*_w;}
};

int main(){
    constexpr Rectangle obj(10,20);
    cout<<obj.getArea();

    return 0;
}
