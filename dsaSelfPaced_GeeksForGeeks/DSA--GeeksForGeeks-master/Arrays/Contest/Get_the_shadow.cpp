#include <bits/stdc++.h>
using namespace std;
///////////////////////////////////////////////////////

/*Method m1*/
/*
int *findTwoElement(int *A, int n) {//correct
        sort(A,A+n);
    int repeated=-1;
    int missing=-1;
    //printA(A,n);
    for(int i=1;i<n;i++){
        if(A[i]==A[i-1]){
            repeated=A[i];
            if(missing!=-1)
                break;
        }
        else if(A[i]!=A[i-1]+1){
            missing=A[i]-1;
            if(repeated!=-1)
                break;
        }
    }
    if(n==2)//eg [2,2] => [1,2],[1,1]=[1,2]
        missing=repeated==2 ? 1 : 2;
        else if(missing==-1)
            missing=A[0]==1 ? A[n-1]+1 : 1;//1 1 2 3 4 5 6 7 8 9 10 11 12 13
    int *a=new int[2];
    a[0]=repeated;
    a[1]=missing;
    return a;
    }
*/
//////////////////////////////////////////////////////
void repeated_Numbers_my(vector<int> A){//wrong
    int xxor=0;
    for(int i=0;i<A.size();i++){
        xxor^=A[i]^(i+1);
    }
    //turnoff all bits except first on bit
    xxor=xxor & ~(xxor-1);

    int x=0,y=0;
    for(int i=0;i<A.size();i++){
        if(A[i]&xxor!=0)
            x^=A[i];
        else
            y^=A[i];

        if((i+1) & xxor !=0)
            x^=(i+1);
        else
            y^=(i+1);
    }
    cout<<x<<" "<<y;
}
//////////////////////////////////////////////////////
int *findTwoElement(int *A, int n) {//correct
    int temp[n+1]={0};
    int *a=new int[2];
    for(int i=0;i<n;i++){
        temp[A[i]]++;
    }
    //printA(temp,n+1);
    for(int i=1;i<=n;i++){
       if(temp[i]==2)
       a[0]=i;
       else if(temp[i]==0)
       a[1]=i;
    }
    return a;
    }
//////////////////////////////////////////////////////
// C++ program to Find the repeating
// and missing elements

#include <bits/stdc++.h>
using namespace std;

void printTwoElements(int arr[], int size)
{
	int i;
	cout << "The repeating element is ";

	for (i = 0; i < size; i++) {
		if (arr[abs(arr[i]) - 1] > 0)
			arr[abs(arr[i]) - 1] = -arr[abs(arr[i]) - 1];
		else
			cout << abs(arr[i]) << "\n";
	}

	cout << "and the missing element is ";
	for (i = 0; i < size; i++) {
		if (arr[i] > 0)
			cout << (i + 1);
	}
}

/* Driver code */
/*
int main()
{
	int arr[] = { 7, 3, 4, 5, 5, 6, 2 };
	int n = sizeof(arr) / sizeof(arr[0]);
	printTwoElements(arr, n);
}
*/
//////////////////////////////////////////////////////
void repeated_Numbers(vector<int> A) {//correct [1-N],one repeating(x,x) one missing
    long long int act_a = 0;
    long long int act_sum_sq = 0;
    long long int exp_b;
    long long int exp_sum_sq;
    long long int i = 0;

    for(i = 0; i < A.size(); i++){
        act_a = act_a + (long long int)A[i];
        act_sum_sq = act_sum_sq + (long long int)A[i]*A[i];
    }

    exp_b = (long long int)(A.size())*(A.size()+1)/2;
    exp_sum_sq = (long long int)(A.size())*(A.size()+1)*(2*A.size()+1)/6;

    long long int diff_sum_sq = exp_sum_sq - act_sum_sq;//repeat sq-miss sq=diff_sum_sq
    long long int diff_a = exp_b - act_a; //repeat-miss=diff_a

    long long int toggle = diff_sum_sq/diff_a;//repeat+miss=toggle

    long long int miss = (toggle + diff_a)/2;
    long long int repp = miss - diff_a;

    cout<<(int)repp<<" "<<(int)miss<<endl;

    return ;
}


int main() {
	int T;
	cin>>T;
	while(T--){
	    int N;
	    cin>>N;
	    vector<int> vect;

	    for(int i=0; i<N; i++){
	        int temp;
	        cin>>temp;
	        vect.push_back(temp);
	    }
	    repeated_Numbers(vect);
	}
	return 0;
}
