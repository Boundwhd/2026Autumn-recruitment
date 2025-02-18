/*二叉树的层序遍历*/
#include "../leetcode.h"

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    queue<TreeNode*> q;
    
    if(!root) return result;
    q.push(root);
    while(!q.empty()) {
        int n = q.size();
        vector<int> temp;
        for (int i = 0; i < n; i++) {
            TreeNode* node = q.front();
            q.pop();
            temp.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(temp);
    }
    return result;
}