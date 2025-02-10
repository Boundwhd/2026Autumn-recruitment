/*从中序与后序遍历构造二叉树*/
#include "../leetcode.h"

class Solution {
    public:
        unordered_map<int, int> pos;
        TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
            int n = inorder.size();
            for (int i = 0; i < n; i++) {
                pos[inorder[i]] = i;
            }

            return build(inorder, postorder, 0, n-1, 0, n-1);
        }

        TreeNode* build(vector<int>& inorder, vector<int>& postorder, int il, int ir, int pl, int pr) {
            if (il > ir || pl > pr) return nullptr;

            int k = pos[postorder[pr]] - il;
            
            TreeNode *node = new TreeNode(postorder[pr]);
            node->right = build(inorder, postorder, il + k + 1, ir, pl + k, pr - 1);
            node->left = build(inorder, postorder, il, il + k - 1, pl, pl + k - 1);

            return node;
        }
    };


/*
后序遍历顺序： 左子树 → 右子树 → 根节点
递归实现： 简单直观
非递归实现： 需要栈，模拟递归过程
应用场景：
表达式树计算：后序遍历适用于计算表达式树
删除目录/文件系统：先删除子目录，再删除父目录
二叉树释放内存
*/

void postorderTraversal(TreeNode* root, vector<int>& result) {
    if (!root) return;
    postorderTraversal(root->left, result);
    postorderTraversal(root->right, result);
    result.push_back(root->val);
}