
/*
#include<iostream>
#include<utility>
using namespace std;

int main(){
pair<int,char> pair1;
pair1.first=100;
pair1.second='G';
cout<<pair1.first<<" "<<pair1.second<<endl;

return 0;
}

*/

/*
#include<iostream>
#include<utility>
using namespace std;

int main(){
pair<string,double> pair("Vishnu kumar",8.98);
cout<<pair.first<<" "<<pair.second<<endl;

return 0;
}
*/

/*
#include<iostream>
#include<utility>
using namespace std;

int main(){
pair<int,double> pair1;
pair<string,char> pair2;
cout<<pair1.first<<" "<<pair1.second<<endl;
cout<<pair2.first<<" "<<pair2.second<<endl;

return 0;
}
*/

/*
#include<iostream>
#include<utility>
using namespace std;

int main(){
pair<int,char> pair1;
pair<string,double> pair2("Vishnu kumar",1.23);
pair<string,double> pair3;

pair1.first=100;
pair1.second='G';

pair3=make_pair("Geeks of geeks is the best",4.56);

cout<<pair1.first<<" "<<pair1.second<<endl;
cout<<pair2.first<<" "<<pair2.second<<endl;
cout<<pair3.first<<" "<<pair3.second<<endl;

return 0;
}
*/

#include<iostream>
#include<utility>
using namespace std;

int main(){
pair<char,int> pair1=make_pair('A',1);
pair<char,int> pair2=make_pair('B',2);

cout<<"Before swapping: \n";
cout<<"Contents of pair1 = "<<pair1.first<<" "<<pair1.second<<endl;
cout<<"Contents of pair2 = "<<pair2.first<<" "<<pair2.second<<endl;
pair1.swap(pair2);
cout<<"After swapping: \n";
cout<<"Contents of pair1 = "<<pair1.first<<" "<<pair1.second<<endl;
cout<<"Contents of pair2 = "<<pair2.first<<" "<<pair2.second<<endl;


return 0;
}

