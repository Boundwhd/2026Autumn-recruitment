/*二叉搜索树的最小绝对差*/
#include "../leetcode.h"

class Solution {
        vector<int> nums;
    public:
        int getMinimumDifference(TreeNode* root) {
            int result = INT32_MAX;
            dfs(root);
            for (int i = 1; i < nums.size(); i++) {
                result = min(result, abs(nums[i] - nums[i - 1]));
            }
            return result;
        }

        void dfs(TreeNode* root) {
            if (!root) return;
            dfs(root->left);
            nums.push_back(root->val);
            dfs(root->right);
        }
    };



class Solution {
public:
    int getMinimumDifference(TreeNode* root) {
        int pre = -1, ans = INT32_MAX;
        dfs(root, pre, ans);
        return ans;
    }

    void dfs(TreeNode* root, int& pre, int& ans) {
        if (!root) return;

        dfs(root->left, pre, ans); 
        if (pre != -1) {
            ans = min(ans, abs(root->val - pre));
        }
        pre = root->val;
        dfs(root->right, pre, ans);
    }
};