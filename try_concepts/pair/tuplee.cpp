
/*
#include<iostream>
#include<tuple>
using namespace std;

int main(){
    tuple<char,int,float> geek;
    geek=make_tuple('a',10,15.5);
    cout<<"The initial value of tuple are : ";
    cout<<get<0>(geek)<<" "<<get<1>(geek)
    <<" "<<get<2>(geek)<<endl;

    get<0>(geek)='b';
    get<2>(geek)=20.5;

    cout<<"The modified values of tuple are :";
    cout<<get<0>(geek)<<" "<<get<1>(geek)
    <<" "<<get<2>(geek)<<endl;

    return 0;
}

*/

/*
#include<iostream>
#include<tuple>
using namespace std;

int main(){
    tuple<char,int,float> geek(20,'g',17.5);
    cout<<"The size of tuple is : ";
    cout<<tuple_size<decltype(geek)>::value<<endl;

    return 0;
}
*/

/*
#include<iostream>
#include<tuple>
using namespace std;

int main(){
    tuple<int,char,float> tup1(20,'g',17.5);
    tuple<int,char,float> tup2(10,'f',15.5);

    cout << "The first tuple elements before swapping are : ";
    cout <<  get<0>(tup1) << " " << get<1>(tup1) << " "
         << get<2>(tup1) << endl;
    cout << "The second tuple elements before swapping are : ";
    cout <<  get<0>(tup2) << " " << get<1>(tup2) << " "
         << get<2>(tup2) << endl;

    // Swapping tup1 values with tup2
    tup1.swap(tup2);

    // Printing 1st and 2nd tuple after swapping
    cout << "The first tuple elements after swapping are : ";
    cout <<  get<0>(tup1) << " " << get<1>(tup1) << " "
         << get<2>(tup1) << endl;
    cout << "The second tuple elements after swapping are : ";
    cout <<  get<0>(tup2) << " " << get<1>(tup2) << " "
         << get<2>(tup2) << endl;

    return 0;
}
*/

/*
#include<iostream>
#include<tuple>
using namespace std;

int main(){
    int i_val;
    char ch_val;
    float f_val;

    tuple<int,char,float> tup1(20,'g',17.5);
    tie(i_val,ch_val,f_val)=tup1;

    cout << "The unpacked tuple values (without ignore) are : ";
    cout << i_val << " " << ch_val << " " << f_val;
    cout << endl;

    tie(i_val,ignore,f_val)=tup1;

    cout << "The unpacked tuple values (with ignore) are : ";
    cout << i_val  << " " << f_val;
    cout << endl;

    return 0;
}
*/

#include<iostream>
#include<tuple>
using namespace std;

int main(){
    tuple<int,char,float> tup1(20,'g',17.5);
    tuple<int,char,float> tup2(30,'f',10.5);

    auto tup3=tuple_cat(tup1,tup2);

    cout << "The new tuple elements in order are : ";
    cout << get<0>(tup3) << " " << get<1>(tup3) << " ";
    cout << get<2>(tup3) << " " << get<3>(tup3) << " ";
    cout << get<4>(tup3) << " " << get<5>(tup3) << endl;

    return 0;
}
