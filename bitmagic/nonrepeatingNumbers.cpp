/*
Given an array A containing 2*N+2 positive numbers, out of which 2*N numbers exist in pairs whereas the other two number occur exactly once and are distinct. Find the other two numbers.
*/
vector<int> singleNumber(vector<int> nums) {
        int xorr=0;
        for(int i=0,len=nums.size();i<len;i++){
            xorr^=nums[i];
        }
        //turn off all others bits except first set bit
        int pattern=xorr & ~(xorr-1);
        int num1=0;
        int num2=0;
        for(int i=0,len=nums.size();i<len;i++){
            if((nums[i]&pattern)==pattern)
                num1^=nums[i];
            else
                num2^=nums[i];
        }
        if(num1<num2)
            return {num1,num2};
        return {num2,num1};
    }
