/*
Given an array A[] of size N. Find the number of pairs (i, j) such that
Ai XOR Aj = 0, and 1 ≤ i < j ≤ N.

Example 1:

Input : arr[ ] = {1, 3, 4, 1, 4}
Output : 2
Explanation:
Index( 0, 3 ) and (2 , 4 ) are only pairs
whose xors is zero so count is 2.

Example 2:

Input : arr[ ] = {2, 2, 2}
Output :  3
*/

long long int calculate(int a[], int n)
{
    sort(a,a+n);
    int count=1;
    int total=0;
    int k=0;
    int i=0;
    for(i=1;i<n;i++){
        if(a[k]==a[i]){
            count++;
        }
        else{
            total+=count*(count-1)/2;
            count=1;
            k=i;
        }
    }
    if(a[k]==a[i-1])//because in this case below didnt get chance to execute
        total+=count*(count-1)/2;
    return total;
}
