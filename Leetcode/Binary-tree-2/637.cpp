/*二叉树的层平均值*/
#include "../leetcode.h"

vector<double> averageOfLevels(TreeNode* root) {
    vector<double> result;
    if (root == nullptr) return result;

    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()) {
        long long sum = 0;
        int n = q.size();
        for (int i = 0; i < n; i++) {
            TreeNode* node = q.front();
            q.pop();
            sum += node->val;
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(static_cast<double>(sum) / n);
    }
    return result;
}