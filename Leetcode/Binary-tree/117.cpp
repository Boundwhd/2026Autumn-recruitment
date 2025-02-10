/*填充每个节点的下一个右侧节点指针*/
#include "../leetcode.h"

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
    
class Solution {
public:
    Node* connect(Node* root) {
        if (!root) {
            return nullptr;
        }
        queue<Node*> q;
        q.push(root);
        while(!q.empty()) {
            int n = q.size();
            Node *last = nullptr;
            for (int i = 1; i <= n; ++i) {
                Node *f = q.front();
                q.pop();
                if (f->left) {
                    q.push(f->left);
                }
                if (f->right) {
                    q.push(f->right);
                }
                if (i != 1) {
                    last->next = f;
                }
                last = f;
            }
        }
        return root;
    }
};

/*层次遍历*/