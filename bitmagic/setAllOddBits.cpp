long long int setAllOddBits(long long int n) {
        return (~(0xFFFFFFFF<<((int)log2(n)+1)))&(n|0x55555555);
        //0x55555555=01010101010101010101010101010101
        //0xFFFFFFFF=11111111111111111111111111111111
    }
