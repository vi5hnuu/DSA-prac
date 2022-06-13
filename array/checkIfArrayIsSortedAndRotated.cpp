private:
        bool isSorted(int arr[],int n,int order){
            bool isSort=false;
            for(int i=1;i<n;i++){
                if(!order && arr[i]<arr[i-1]){
                    isSort=true;
                }
                else{
                    isSort=false;
                }
                ////////////////////////////
                if(order && arr[i]>arr[i-1]){
                    isSort=true;
                }
                else{
                    isSort=false;
                }
            }
            return isSort;
        }
        int findMin(int arr[],int n){
            int min=INT_MAX;
            for(int i=0;i<n;i++){
                if(arr[i]<min)
                    min=arr[i];
            }
            return min;
        }
    public:
    // arr: input array
    // num: length of array
    // This function returns true or false
    //Function to check if array is sorted and rotated.
    bool checkRotatedAndSorted(int arr[], int n){
        int order=arr[0]>arr[n-1] ? 0 : 1;//0 increasing, 1 decreasing


        if(isSorted(arr,n,order)){
            return false;
        }

        int minElem=findMin(arr,n);

        int i=0;
        while(!order && (arr[i]>minElem)){i++;}
        if(!order)
        for(int k=i+1;k<i+n;k++){
            if(arr[k%n]<arr[(k-1)%n]){
            return false;
            }
        }
        /////////////////////////////////////////

        while(order && (arr[i]>minElem)){i++;}
        //cout<<i;
        if(order)
        for(int k=i+2;k<n+i;k++){
            if(arr[k%n]>arr[(k-1)%n]){
                //cout<<(k%n)<<" ";
            return false;
            }
        }

        return true;
    }
