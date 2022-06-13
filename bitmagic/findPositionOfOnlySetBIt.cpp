int findPosition(int N) {
        if(N==0 || (N&(N-1))!=0)//N&(N-1) turns off the first Set bit
            return -1;
        int pos=0;
        while(N){
            pos++;
            N=N>>1;
        }
        return pos;
    }
/*
Given a number N having only one �1� and all other �0�s in its binary representation,
find position of the only set bit. If there are 0 or more than 1 set bit the answer should
be -1. Position of  set bit '1' should be counted starting with 1 from LSB side in binary
representation of the number.
*/
