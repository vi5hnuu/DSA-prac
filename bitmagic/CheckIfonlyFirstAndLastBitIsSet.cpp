/*
	int onlyFirstAndLastAreSet(long long int n) {
	   if(!(n&1))
	        return 0;
	        n=n>>1;
	   while(n>1){
	    if((n&1)!=0){
	        return 0;
	    }
	    n=n>>1;
	   }
	   return 1;
	}
	*/
	int onlyFirstAndLastAreSet(long long int n) {
	    if(n%2==0) return 0;
        return ((n-1) & (n-2))==0 ;
	}
