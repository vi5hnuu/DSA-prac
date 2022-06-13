int search(int A[], int l, int h, int key){
        while(l<=h){
            int mid=(l+h)/2;
            if(A[mid]==key)
                return mid;
            else if(A[mid]>=A[l]){ //left part is sorted
                    if(A[mid]>key && A[l]<=key)//and key in sorted part only
                        h=mid-1;
                    else //but key is not in sorted part
                        l=mid+1;
                }
            else{//right part is sorted
                if(A[mid]<key && A[h]>=key)//and key in sorted part only
                        l=mid+1;
                    else //but key is not in sorted part
                        h=mid-1;
            }
            }
            return -1;
    }
