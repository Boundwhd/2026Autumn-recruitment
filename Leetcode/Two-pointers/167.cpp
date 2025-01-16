/*两数之和II-输入有序数组*/
#include "../leetcode.h"

vector<int> twoSum(vector<int>& numbers, int target) {
    int i = 0;
    int j = numbers.size() - 1;

    while(i < j){
        if (numbers[i] + numbers[j] == target) {
            break;
        } else if (numbers[i] + numbers[j] > target) {
            j--;
        } else {
            i++;
        }
    }   
    return {++i, ++j};
}

// 双指针法