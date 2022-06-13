//store freq of its element at its own number as index
    //i.e element at index 2 store freq of element 2(in negative number)
    //-5 at index 2 represent 2 is 5 times in array

    //when order of repeated element does not matter
    vector<int> twoRepeated (int arr[], int N) {//O(N)
        vector<int> res;
        int k=0;
        while(k<N+2){
            while(arr[k]<=0){
                k++;
            }
            if(k>=N+2)
                break;
            if(arr[arr[k]]>0){
                int index=arr[k];
                if(arr[k]!=arr[arr[k]]){// {1,2,1,3,4,3}
                    arr[k]=arr[arr[k]];
                }
                arr[index]=-1;
            }
            else{//neg is there
                arr[arr[k]]--;
                arr[k]=0;
            }
        }
        for(int i=0;i<N+2;i++){
            if(arr[i]==-2){
                res.push_back(i);
            }
        }
        return res;
    }

/*
You are given an array of N+2 integer elements. All elements of the array are in range 1 to N. Also, all elements occur once except two numbers which occur twice. Find the two repeating numbers.

Example 1:

Input:
N = 4
array[] = {1,2,1,3,4,3}
Output: 1 3
Explanation: In the given array,
1 and 3 are repeated two times.
Example 2:

Input:
N = 2
array[] = {1,2,2,1}
Output: 2 1
Explanation: In the given array,
1 and 2 are repeated two times
and second occurence of 2 comes
before 1. So the output is 2 1.

Note: Return the numbers in their order of appearing twice.
So, if X and Y are the repeating numbers, and X repeats twice before Y repeating twice, then the order should be (X,Y).
*/
