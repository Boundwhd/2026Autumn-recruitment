/*二叉树的右视图*/
#include "../leetcode.h"


vector<int> rightSideView(TreeNode* root) {
    vector<int> result;
    queue<TreeNode*> q;
    if (!root) return result;
    
    q.push(root);
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0;i < n; i++) {
            TreeNode* node = q.front();
            q.pop();
            if (i == 0) {
                result.push_back(node->val);
            }
            if(node->right) q.push(node->right);
            if(node->left) q.push(node->left);
        }
    }
    return result;
}

