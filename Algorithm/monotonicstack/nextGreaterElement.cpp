#include <vector>
#include <unordered_map>
#include <stack>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> hash;
        stack<int> stk;
        vector<int> result(nums1.size(), -1);
        for (int i = 0; i < nums1.size(); i++) {
            hash[nums1[i]] = i;
        }
        for (int i = 0; i < nums2.size(); i++) {
            if (stk.empty() || nums2[i] <= nums2[stk.top()]) {
                stk.push(i);
            } else {
                while (!stk.empty() && nums2[i] > nums2[stk.top()]) {
                    if (hash.count(nums2[stk.top()])) {
                        result[hash[nums2[stk.top()]]] = nums2[i];
                    }
                    stk.pop();
                }
                stk.push(i);
            }
        }
        return result;
    }
};