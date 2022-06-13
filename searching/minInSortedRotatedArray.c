//Function to find the minimum element in sorted and rotated array.
//the fact is at one point half of the array is sorted
//at last both half is sorted
//sorted and rotated means it must be sorted+rotated
//only sorted is not rotated
//5 4 3 2 1   (X)
int minNumber(int arr[], int low, int high)
{
    int minEle=INT_MAX;
    while(low<=high){
        int mid=(low+high)/2;
        if(arr[mid]>=arr[low]){//this half is sorted and its low can be minimum so far
            minEle=min(minEle,arr[low]);
            low=mid+1;
        }
        else if(arr[mid]<=arr[high]){//right half is sorted
            minEle=min(minEle,arr[mid]);
            high=mid-1;
        }
    }
    return minEle;
}
