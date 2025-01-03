/*买卖股票的最佳时机*/
#include "../leetcode.h"

int maxProfit(vector<int>& prices) {
        int max_profit = 0;
        int min_price = prices[0];
        for(int i = 1; i < prices.size(); i++){
            if (prices[i] < min_price){
                min_price = prices[i];
            }else{
                max_profit = max(max_profit, prices[i] - min_price);
            }
        }
        return max_profit;
    }

/*
维护两个变量：1.直到这一天的最大利润是多少；2.直到这一天最小买入价格是多少
*/