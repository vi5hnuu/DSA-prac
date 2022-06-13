    /*
    Given n integer ranges, the task is to find the maximum occurring integer in these ranges. If more than one such integer exits, find the smallest one. The ranges are given as two arrays L[] and R[].  L[i] consists of starting point of range and R[i] consists of corresponding end point of the range.

    For example consider the following ranges.
    L[] = {2, 1, 3}, R[] = {5, 3, 9)
    Ranges represented by above arrays are.
    [2, 5] = {2, 3, 4, 5}
    [1, 3] = {1, 2, 3}
    [3, 9] = {3, 4, 5, 6, 7, 8, 9}
    The maximum occurred integer in these ranges is 3.
    */

    int maxOccured(int L[], int R[], int n, int maxx){

        int res[maxx+1] ={0};
        int ans=INT_MIN;
        int idx=0;


        for(int i=0;i<n;i++){

            int counter = L[i];

            while(counter<=R[i]){
            res[counter]++;
            counter++;
            }
        }

        for(int i=0; i<=maxx;i++){
            if(ans<res[i]){
                ans=res[i];
                idx = i;
            }
        }
        return idx;
    }
};
