/*将每个元素替换为右侧最大元素*/
#include "../leetcode.h"

vector<int> replaceElements(vector<int>& arr) {
    vector<int> result(arr.size());
    int n = arr.size();
    result[n - 1] = -1;
    if (n == 1) return result;

    int max_ = INT32_MIN;
    for (int i = n - 2; i >= 0; i--){
        max_ = max(max_, arr[i + 1]);
        result[i] = max_;
    }
    return result;
}