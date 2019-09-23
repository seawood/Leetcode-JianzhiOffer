//Leetcode 322:换硬币，每种硬币个数不限
//输入【1,2,5] 11
//输出3
//f(n,m) = min(f(n-1,m), f(n, m-coins[n])+1)


int coinChange(vector<int>& coins, int amount) {
        int len = coins.size();
        vector<int> record(amount+1, amount+1); //注意初始化
        record[0] = 0;  //注意初始化
        for(int i = 0; i <len; ++i){
            for(int j = 0; j <= amount; ++j){
                if(j >= coins[i] && record[j-coins[i]]+1 < record[j])
                    record[j] = record[j-coins[i]]+1;
            }
        }
        return record[amount]==amount+1 ? -1 : record[amount];
    }