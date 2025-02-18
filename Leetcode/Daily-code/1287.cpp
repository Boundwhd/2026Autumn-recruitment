/*有序数组中出现次数超过25%的元素*/
#include "../leetcode.h"

int findSpecialInteger(vector<int>& arr) {
    if (arr.size() == 1) return arr[0];
    float th = static_cast<float>(arr.size()) / 4;
    int cur_num_cnt = 1;
    int i = 1;
    for (; i < arr.size(); i++) {
        if (arr[i] == arr[i - 1]) {
            cur_num_cnt++;
        } else {
            cur_num_cnt = 1;
        }
        
        if (cur_num_cnt > th) {
            break;
        }
    }
    return arr[i];
}