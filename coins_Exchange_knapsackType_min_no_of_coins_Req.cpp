int coinChange(vector<int>& coins, int amount) {
        int dp_min[amount+1];
        for(int i=0;i<amount+1;i++)
            dp_min[i]=INT_MAX;
        dp_min[0]=0;
        for(int i=0;i<coins.size();i++){ //traverse coins array
        for(int j=coins[i];j<amount+1;j++){

            int min_coin=dp_min[j-coins[i]];
            if(dp_min[j-coins[i]]<dp_min[j]-1)
                dp_min[j]=min_coin+1;
        }
    }

        if(dp_min[amount]!=INT_MAX)
            return dp_min[amount];
        return -1;
    }
