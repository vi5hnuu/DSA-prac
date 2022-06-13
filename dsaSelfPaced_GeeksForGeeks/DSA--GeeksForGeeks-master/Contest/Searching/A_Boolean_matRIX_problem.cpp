#include<iostream>
using namespace std;

/*
given M*N matrix of 0 or 1
if any row has 1 fill whole row with one
*/

int main() {
	int T;
	cin>>T;

	while(T--){
	    int M,N,temp;
	    int i,j;
	    cin>>M>>N;

	   int matRIX[M][N];

	    for(i=0; i<M; i++){
	        for(j=0; j<N; j++){
	            cin>>temp;
	            matRIX[i][j] = temp;
	        }
	    }

	    for(int i=0; i<M; i++){
	        for(int j = 0; j<N; j++){
	            if(matRIX[i][j]){
	                matRIX[i][0] = 1;
					break;
	            }
	        }
	    }


	   for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
				if (matRIX[i][0] == 1) {
                    matRIX[i][j] = 1;
                }else{
					break;
				}
            }
        }


	    for(int i=0; i<M; i++){
	        for(int j=0; j<N; j++){
	            cout<<matRIX[i][j]<<" ";
	        }
	        cout<<endl;
	    }
	}
	return 0;
}
