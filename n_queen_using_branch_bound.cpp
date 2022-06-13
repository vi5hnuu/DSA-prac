#include<iostream>
using namespace std;

void solve(bool *board[],int dim,int row,bool *cols,bool *ndiag,bool *rdiag,string asf){
    if(row==dim){
        cout<<(asf+"\nAND\n")<<endl;
        return;
    }

    for(int col=0;col<dim;col++){
        if(cols[col]==false && ndiag[row+col]==false && rdiag[row-col+dim-1]==false){
            board[row][col]=true;
            cols[col]=true;
            ndiag[row+col]=true;
            rdiag[row-col+dim-1]=true;
            solve(board,dim,row+1,cols,ndiag,rdiag,asf+to_string(row)+" - "+to_string(col)+"  ");
            cols[col]=false;
            ndiag[row+col]=false;
            rdiag[row-col+dim-1]=false;
        }
    }
}

int main(){
int n;
cout<<"Board of nXn :";
cin>>n;
bool *board[n];
for(int i=0;i<n;i++)
    board[i]=new bool[n];
bool cols[n]={false};
bool ndiag[2*n-1]={false};
bool rdiag[2*n-1]={false};
solve(board,n,0,cols,ndiag,rdiag,"");
}
