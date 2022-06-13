int trailingZeroes(int N)
    {
        //count 5's
        int count=0;
        for(int i=5;i<=N;i*=5){
            count+=N/i;
        }
        return count;
    }
