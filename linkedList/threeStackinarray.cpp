#include<iostream>
using namespace std;

class Stack{
private:
    int *stack;
    int top1;
    int top2;
    int top3;
    int start3;
    int fullSize;

    bool shiftRight(int from,int top,int rightBoundryLimit){
        if(top<0){//stack 3 do not have any element
            if(from+1==rightBoundryLimit){
                return false;
            }
            else{
                start3++;
                return true;
            }
        }
        else{
            if(top==rightBoundryLimit){
                return false;
            }
            else{
                for(int i=top;i>=from+1;i--){
                    stack[i]=stack[i-1];
                }
                start3++;
                top3++;
                return true;
            }
        }
    }
    bool shiftLeft(int from,int top,int leftBoundryLimit){
        if(from-1==-1 || from-1==leftBoundryLimit){
            return false;
        }
        else{
            for(int i=from-1;i<top-1;i++){
                stack[i]=stack[i+1];
            }
            top3--;
            start3--;
            return true;
        }
    }
public:
    Stack(){
        fullSize=15;
        stack=new int[fullSize];
        top1=-1;
        top2=fullSize;
        start3=fullSize/3;
        //start3 have element if top3>=0
        //else start3 just tell where to start
        top3=-1;
    }
    Stack(int initialSize){
        fullSize=initialSize;
        stack=new int[fullSize];
        top1=-1;
        top2=fullSize;
        start3=fullSize/3;
        //start3 do not  have element if top3>0
        top3=-1;
    }
    void push1(int n){//increment top1 and put element => so if top1>=0 is has element at top1
        if(top1+1!=start3){
                stack[++top1]=n;
            }else{//try to shiift stack3 forward
                bool isShiftDone=shiftRight(start3,top3,top2);
                if(isShiftDone){
                    stack[++top1]=n;
                }else{
                    throw string("All stack full.");
                }
            }
    }
    void push2(int n){//top3 do not have any element
        if((top3>0 && top2-1>=top3) || (top3<0 && top2-1>start3 )){
                stack[--top2]=n;
            }else{//try to shiift stack3 forward
                bool isShiftDone=shiftLeft(start3,top3,top1);
                if(isShiftDone){
                    stack[--top2]=n;
                }else{
                    throw string("All stack full.");
                }
            }
    }
      void push3(int n){//put in top3 and move ahead [middle stack]
        if(top3<0){
            top3=start3;
        }
        if(top3==top2){
           bool isShiftDone=shiftLeft(start3,top3,top1);
                if(isShiftDone){
                    stack[top3++]=n;
                }else{
                    throw string("All stack full.");
                }
        }
        else{
                stack[top3++]=n;
            }
    }
    void display() const{
        cout<<"\nStack 1 :\n";
        if(top1<0)
            cout<<"Empty.\n top1 "<<top1<<endl;
        else{
            for(int i=0;i<=top1;i++){
                cout<<stack[i]<<" ";
            }
            cout<<endl;
        }
        ///////////////
        cout<<"\nStack 2 :\n";//at end of array one
        if(top2==fullSize)
            cout<<"Empty.\n top2 "<<top2<<endl;
        else{
            for(int i=fullSize-1;i>=top2;i--){
                cout<<stack[i]<<" ";
            }
            cout<<endl;
        }
        ///////////////
        cout<<"\nStack 3 :\n";//at end of array one
        if(top3<0)
            cout<<"Empty.\n top3 :"<<top3<<endl;
        else{
            for(int i=start3;i<top3;i++){
                cout<<stack[i]<<" ";
            }
            cout<<endl;
        }
    }
    int pop1(){
        if(top1<0){
            throw string("Stack1 empty.");
        }
        return stack[top1--];
    }
    int pop2(){//end stack
        if(top2==fullSize){
            throw string("Stack2 empty.");
        }
        return stack[top2++];
    }
    int pop3(){//mid stack
        if(top3<0){
            throw string("Stack2 empty.");
        }
        int data=stack[--top3];
        if(top3==start3){
            top3=-1;
        }
        return data;
    }
};

int main(){
Stack stck;
try{
/*
stck.push1(10);
stck.push1(11);
stck.push1(12);
stck.push1(13);
stck.push1(14);
stck.push1(15);
stck.push1(16);
stck.push1(17);
stck.push1(18);
stck.push1(19);
stck.push1(20);
stck.push1(21);
stck.push1(22);
stck.push1(23);
stck.display();
*/

/*
stck.push2(10);
stck.push2(11);
stck.push2(12);
stck.push2(13);
stck.push2(14);
stck.push2(15);
stck.push2(16);
stck.push2(17);
stck.push2(18);
stck.push2(19);
stck.push2(20);
stck.push2(21);
stck.push2(22);
stck.push2(23);
stck.push2(24);
*/
/*
stck.push3(10);
stck.push3(11);
stck.push3(12);
stck.push3(13);
stck.push3(14);
stck.push3(15);
stck.push3(16);
stck.push3(17);
stck.push3(18);
stck.push3(19);
stck.push3(20);
stck.push3(21);
stck.push3(22);
stck.push3(23);
*/

/*
stck.push1(10);
stck.push1(11);
stck.push1(12);
stck.push1(13);
stck.push1(14);
//stck.push1(14);
stck.push2(15);
stck.push2(16);
stck.push2(17);
stck.push2(18);
stck.push2(19);
//stck.push2(19);
stck.push3(20);
stck.push3(21);
stck.push3(22);
stck.push3(23);
stck.push3(24);
//stck.push3(24);
*/

/*
stck.push1(10);
stck.push1(11);
stck.push1(12);
stck.push1(13);
stck.push1(14);
stck.push1(15);
stck.push1(16);
stck.push1(17);
stck.push2(18);
stck.push2(19);
stck.push2(19);
stck.push2(20);
stck.push3(21);
stck.push3(22);
stck.push3(23);
//stck.push3(24);
*/

stck.push1(10);
stck.push1(11);
stck.push1(12);
cout<<stck.pop1()<<endl;
//cout<<stck.pop2()<<endl;
stck.push1(13);
stck.push1(14);
stck.push1(15);
stck.push1(16);
stck.push1(17);
cout<<stck.pop1()<<endl;//
stck.push2(18);
stck.push2(19);
stck.push2(45);
cout<<stck.pop2()<<endl;
cout<<stck.pop2()<<endl;
stck.push2(46);
stck.push2(47);
stck.push2(20);
stck.push3(21);
stck.push3(22);
cout<<stck.pop3()<<endl;
cout<<stck.pop2()<<endl;
cout<<stck.pop1()<<endl;
stck.push3(23);
stck.push3(48);
stck.push1(49);
stck.push1(50);
stck.push1(51);
stck.push1(52);

stck.display();
}catch(string s){
    cout<<s;
}
return 0;
}
