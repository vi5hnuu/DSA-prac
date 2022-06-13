#include<iostream>
#include<math.h>
using namespace std;


struct data{
    int count;
    unsigned long long fact;
};
//////////////////////////1.//////////////////////////////every function do independent job (good)
//but the flaw is that fact of higher no cant be calculated without overflow
unsigned long long factorial(int n){
    if(n==0)
    return 1;

    unsigned long long fact=1;
    for(int i=1;i<=n;i++)
    fact*=i;
    return fact;
}

int trailing_zero(int n){
    int count=0;
    while(n%10==0 && n!=0){
        count++;
        n/=10;
    }
    return count;
}

data* trailing_zero_fact(int n){
  data *a=new data;
  a->fact=factorial(n);
  a->count=trailing_zero(a->fact);
  return a;
}

/////////////////////////////////////////////////good solution
//each group of 5 digit has one 5=>[n/5]
//each 25 group of digit contain one more 5 like in 25=>[n/5]+[n/25]
//each 125 group of digit contain one more 5 like in 25=>[n/5]+[n/25]+[n/125]
//etc
int trailing_zero_in_fact_of(int n){
    int count=0;
    for(int i=5;i<=n;i*=5){
        count+=floor(n/i);
    }
    return count;

}
/////////////////////////////////////////////////

int main(){
data *dt0=trailing_zero_fact(12);
cout<<(dt0->count)<<"\t"<<(dt0->fact)<<endl;

/*data *dt1=trailing_zero_fact(0);
cout<<(dt1->count)<<"\t"<<(dt1->fact)<<endl;*/

data *dt1=trailing_zero_fact(50);//wrong
cout<<(dt1->count)<<"\t"<<(dt1->fact)<<endl;

delete dt0;
delete dt1;

cout<<trailing_zero_in_fact_of(12)<<endl;
cout<<trailing_zero_in_fact_of(50)<<endl;
cout<<trailing_zero_in_fact_of(100)<<endl;
cout<<trailing_zero_in_fact_of(1000000)<<endl;

return 0;
}

