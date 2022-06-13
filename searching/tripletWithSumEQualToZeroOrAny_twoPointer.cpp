bool findTriplets(int arr[], int n)
    {
        sort(arr,arr+n);//nlogn ....constrainet O(n^2)
        for(int i=0;i<n;i++){
            int p=i+1,q=n-1;
            while(p<q){
                if(arr[p]+arr[q]+arr[i]==0){
                    return true;
                }
                else if(arr[p]+arr[q]+arr[i]<0){
                    p++;
                }
                else{
                    q--;
                }
            }
        }
        return false;
    }
