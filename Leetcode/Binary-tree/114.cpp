/*二叉树展开为链表*/
#include "../leetcode.h"

class Solution {
    public:
        void flatten(TreeNode* root) {
            if(!root) return;

            flatten(root->left);
            flatten(root->right);

            TreeNode* right = root->right;
            root->right = root->left;
            root->left = nullptr;

            TreeNode* cur = root;
            while (cur->right) {
                cur = cur->right;
            }
            cur->right = right;
        }
};

/*
flatten 函数：
首先递归展开左子树和右子树。
然后将左子树插入到右子树的位置。
最后找到当前右子树的末尾，并将原来的右子树接上去。
*/