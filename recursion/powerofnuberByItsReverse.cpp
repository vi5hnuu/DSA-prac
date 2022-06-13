long long power(int N,int R)
    {
       long long pow=1;
       long long multiplier=N;
       while(R!=0){

           if(R & 1)
           pow=((pow%1000000007)*(multiplier%1000000007))%1000000007;
           multiplier=(multiplier*multiplier)%1000000007;

          R>>=1;
       }
        return pow;
    }
