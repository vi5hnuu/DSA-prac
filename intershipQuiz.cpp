#include<iostream>
#include<string>
using namespace std;

class Test{
    private :
    string name;
    string status;
    string vendorId;
    public:
    Test(string name,string status,string vendorId){
    this->name=name;
    this->status=status;
    this->vendorId=vendorId;
    }

    bool isValid(){
        if(vendorId.length()<10){
                    cout<<"Invalid Vendor ID | "<<"Character length mismatch\n";
                    return false;
                }

        for(int i=0;i<vendorId.length();i++){
            if(i<3){
                if(!(vendorId[i]>='A' && vendorId[i]<='Z')){
                    cout<<"Invalid Vendor ID | "<<"Either of first 3 character not an alphabet\n";
                    return false;
                }
            }else if(i==3){
                if(!(vendorId[i]>='A' && vendorId[i]<='Z'))
                    return false;

                if(status=="Individual"){
                     if(vendorId[3]!='P'){
                        cout<<"Invalid Vendor ID | "<<"status mismatch\n";
                        return false;
                     }

                }
                else if(vendorId[3]!=status[0]){
                    cout<<"Invalid Vendor ID | "<<"status mismatch\n";
                        return false;
                }
            }
            else if(i==4){
                string lastName=name.substr(name.find(" ")+1);
                if(vendorId[i]!=lastName[0]){
                    cout<<"Invalid Vendor ID | "<<(i+1)<<"th character mismatch\n";
                    return false;
                }
            }
            else if(i<9){
                if(!(vendorId[i]>='0' && vendorId[i]<='9')){
                    cout<<"Invalid Vendor ID | "<<"Either of 6th to 9th character not a digit\n";
                    return false;
                }

            }else{
                if(!(vendorId[i]>='A' && vendorId[i]<='Z')){
                    cout<<"Invalid Vendor ID | "<<"last character not an alphabet\n";
                    return false;
                }
            }
        }
        cout<<"Valid Vendor ID\n";
        return true;
    }

};

int main(){
int testCases=15;
string name;
getline(cin,name);
string status;
cin>>status;
do{
string vendorId;
cin>>vendorId;
Test test(name,status,vendorId);
test.isValid();
testCases--;
}while(testCases!=0);
}

/*
Kartik Kumar
Individual
AFZPK7190K
*/
