/*验证二叉搜索树*/
#include "../leetcode.h"

class Solution {
    long long last_Val = INT64_MIN;
    public:
        bool isValidBST(TreeNode* root) {
            
            if (!root) return true;

            if(!isValidBST(root->left)) return false;

            if (root->val <= last_Val) return false;

            last_Val = root->val;

            return isValidBST(root->right);
        }
    };
