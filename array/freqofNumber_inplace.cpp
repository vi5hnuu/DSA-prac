/*
Given an array A[] of N positive integers which can contain integers from 1 to P where elements can be repeated or can be absent from the array. Your task is to count the frequency of all elements from 1 to N.
Note: The elements greater than N in the array can be ignored for counting and please read your task section of the problem carefully to understand how to output the array.

Complete the function frequencycount() that takes the array and n as input parameters and modify the array itself in place to denote the frequency count of each element from 1 to N. i,e element at index 0 should represent the frequency of 1 and so on.
*/

void frequencyCount(vector<int>& arr,int N, int P)//with extra space
    {
        vector<int> res=arr;
        fill(arr.begin(),arr.end(),0);
        for(int i=0;i<N;i++){
            if(arr[i]<=N)
            arr[((res[i]-1)%N)]++;
        }
    }
