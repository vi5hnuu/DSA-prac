/*
Given a sorted array of positive integers. Your task is to rearrange  the array elements alternatively i.e first element should be max value, second should be min value, third should be second max, fourth should be second min and so on.
Note: Modify the original array itself.
*/
void rearrange(long long *arr, int n)
    {
       int max=arr[n-1]+1;
       int min_index=0;
       int max_index=n-1;
       for(int i=0;i<n;i++){
        if(i & 1){
            arr[i]+=(arr[min_index++]%max)*max;
        }else{
            arr[i]+=(arr[max_index--]%max)*max;
        }
       }
       for(int i=0;i<n;i++){
           arr[i]/=max;
       }

    }
