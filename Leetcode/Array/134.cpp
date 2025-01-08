/*加油站*/
#include "../leetcode.h"

int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int total_gas = 0;
        int total_cost = 0;
        int current_tank = 0;
        int start = 0;

        for (int i = 0; i < gas.size(); i++) {
            total_gas += gas[i];
            total_cost += cost[i];
            current_tank += gas[i] - cost[i];

            if (current_tank < 0) {
                start = i + 1;
                current_tank = 0;
            }
        }

        return total_gas < total_cost ? -1 : start;
    }

/*
total_gas：所有加油站的汽油总和。
total_cost：所有加油站到下一个加油站所需的汽油总和。
current_tank：当前油箱的油量。
start：当前可能的起点加油站。

遍历 gas 和 cost 数组，更新 total_gas 和 total_cost。
同时，更新 current_tank 来追踪从当前起点开始能否继续走到下一个加油站。
如果 current_tank 为负值，说明从当前起点出发无法继续下去，那么我们更新起点 start 
为当前加油站的下一个加油站，并重置 current_tank 为 0。
如果 total_gas < total_cost，说明总的油量不足以支撑一圈，直接返回 -1。
*/