/*二叉树的锯齿形层序遍历*/
#include "../leetcode.h"

vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (root == nullptr) return result;
    queue<TreeNode*> q;
    stack<TreeNode*> stk;
    bool flag = false;
    stk.push(root);

    while (!stk.empty()) {
        int n = stk.size();
        vector<int> temp;
        for (int i = 0; i < n; i++) {
            TreeNode* node = stk.top();
            stk.pop();
            temp.push_back(node->val);
            if (flag) {
                if (node->right) q.push(node->right);
                if (node->left) q.push(node->left);
            }else{
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
        }
        result.push_back(temp);
        flag = !flag;
        while (!q.empty()) {
            stk.push(q.front());
            q.pop();
        }
    }
    return result; 
}