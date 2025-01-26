/*最长连续序列*/
#include "../leetcode.h"

int longestConsecutive(vector<int>& nums) {
    if (nums.size() == 0) return 0;

    unordered_set<int> num_set;
    for (auto num : nums) {
        num_set.insert(num);
    }

    int max_len = 0;

    for (auto num : num_set) {
        if (!num_set.count(num - 1)) {
            int current_num = num;
            int current_len = 0;

            while (num_set.count(current_num + 1)) {
                current_num++;
                current_len++;
            }

            max_len = max(max_len, current_len);
        }
    }
    return max_len;
}