#include <vector>
using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int total_gas = 0;
        int total_cost = 0;
        int cur_gas = 0;
        int possible_cur = 0;

        for (int i = 0; i < gas.size(); i++) {
            total_gas += gas[i];
            total_cost += cost[i];

            cur_gas = cur_gas + gas[i] - cost[i];
            if (cur_gas < 0) {
                cur_gas = 0;
                possible_cur = i + 1;
            }
        }
        if (possible_cur < gas.size() && total_gas >= total_cost) return possible_cur;
        return -1;
    }
};