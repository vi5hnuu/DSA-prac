pair<int, int> findRepeating(int *arr, int n){//TLE idk why
        //consecutive and sorted
        int low=0;
        int high=n-1;
        while(low<high){
            int mid=(low+high)/2;
            if(arr[low]==arr[high] && low!=high)
                return make_pair(arr[mid],high-mid+1);
            if(mid-low+1==(arr[mid]-arr[low]+1)){//no repeating in this side
                if(low==mid)
                    low=mid+1;
                else
                    low=mid;

            }
            else if(high-mid+1==(arr[high]-arr[mid]+1)){//no repeating in this side
                high=mid;
            }
        }
        return make_pair(-1,-1);
    }
