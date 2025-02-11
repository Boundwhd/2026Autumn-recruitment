/*二叉搜索树迭代器*/
#include "../leetcode.h"

class BSTIterator {
    stack<TreeNode*> stk;
    TreeNode* cur;
public:
    BSTIterator(TreeNode* root) {
        cur = root;
    }
    
    int next() {
        while (cur) {
            stk.push(cur);
            cur = cur->left;
        }
        cur = stk.top();stk.pop();
        int ans = cur->val;
        cur = cur->right;
        return ans;
    }
    
    bool hasNext() {
        return cur || !stk.empty();
    }
};
    