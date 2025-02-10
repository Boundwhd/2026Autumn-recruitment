/*从前序与中序遍历序列构造二叉树*/
#include "../leetcode.h"
class Solution {
unordered_map<int, int> ht;
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        for (int i = 0; i < n; i++) {
            ht[inorder[i]] = i;
        }     
        return build(preorder, inorder, 0, n-1, 0, n-1);
    }

    TreeNode* build(vector<int>& preorder, vector<int>& inorder, int pl, int pr, int il, int ir) {
        if (pl > pr || il > ir) return nullptr;
    
        int k = ht[preorder[pl]] - il;

        TreeNode* root = new TreeNode(preorder[pl]);
        root->left = build(preorder, inorder, pl + 1, pl + k, il, il + k - 1);
        root->right = build(preorder, inorder, pl + 1 + k, pr, il + k + 1, ir);

        return root;
    }
};




/*
二叉树的前序遍历：
1. 先访问根节点，然后依次访问左、右子树
2. 可以用递归或栈实现
3. 适用于树的深度优先遍历（DFS）
*/

vector<int> preorderTraversal(TreeNode* root) {
    vector<int> result;
    if (!root) return result;

    stack<TreeNode*> stk;
    stk.push(root);

    while(!stk.empty()) {
        TreeNode* node = stk.top();
        stk.pop();

        result.push_back(node->val);
        if (node->right) stk.push(node->right);
        if (node->left) stk.push(node->left);
    }

    return result;
}

/*
二叉树的中序遍历：
1. 中序遍历顺序： 左子树 → 根节点 → 右子树
2. 非递归实现： 需要 栈，模拟递归过程
应用场景：
1. 二叉搜索树（BST）：中序遍历得到的是 递增序列
2. 表达式树：可以转换为中缀表达式
*/

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> stk;
    TreeNode* curr = root;

    while(curr || !stk.empty()){ 
        while (curr) {
            stk.push(curr);
            curr = curr->left;
        }
        curr = stk.top();
        stk.pop();
        result.push_back(curr->val);
        curr = curr->right;
    }

    return result;
}


int main() {
    vector<int> preorder = {1, 2, 4, 5, 3};  // 先序遍历
    vector<int> inorder = {4, 2, 5, 1, 3};   // 中序遍历
    Solution *make_tree = new Solution;

    TreeNode* root = make_tree->buildTree(preorder, inorder);

    return 0;
}
