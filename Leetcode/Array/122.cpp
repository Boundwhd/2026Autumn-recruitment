/*买卖股票的最佳时机2*/
#include "../leetcode.h"

int maxProfit(vector<int>& prices) {
        int l = 0;
        int profit = 0;
        for(int r = 1; r < prices.size(); r++){
            if(prices[r] > prices[l]){
                profit += prices[r] - prices[l];
            }
            l++;
        }
        return profit;
    }

/*
求每个递增段的差值并累加
*/