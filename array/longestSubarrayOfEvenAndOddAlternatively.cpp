int maxEvenOdd(int arr[], int n)
    {
       int count=1;
       int tempcount=1;
       for(int i=1;i<n;i++){
           if((arr[i] & 1)!=(arr[i-1] & 1))
                tempcount++;
            else{
                tempcount=1;
            }
            count=max(count,tempcount);
       }
       return count;
    }
