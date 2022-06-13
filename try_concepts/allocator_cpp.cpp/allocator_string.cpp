#include<iostream>
#include<memory>
#include<string>
using namespace std;


int main(){
    allocator<string> myAllocator;

    string *str=myAllocator.allocate(3);
    myAllocator.construct(str,"Vishnu kumar");
    myAllocator.construct(str+1,"Krishan kumar");
    myAllocator.construct(str+2,"Laxmi kumar");

    for(int i=0;i<3;i++){
        cout<<str[i]<<endl;
    }
    myAllocator.destroy(str);
    myAllocator.destroy(str+1);
    myAllocator.destroy(str+2);
    myAllocator.deallocate(str,3);

    return 0;
}
