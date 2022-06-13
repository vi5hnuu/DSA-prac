int isBitSet(int N){
        return N && !(N&(N+1));
}

/*
if all bits are set then N & (N+1) is zero
    7=0111
    8=1000
     =0000
*/
