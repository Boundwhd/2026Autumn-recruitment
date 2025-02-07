/*随机链表的复制*/
#include "../leetcode.h"

class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

Node* copyRandomList(Node* head) {
    unordered_map<Node*, Node*> ht;
    for (Node* cur = head; cur; cur = cur->next) {
        ht[cur] = new Node(cur->val);
    }

    for (Node* cur = head; cur; cur = cur->next) {
        if (cur->next) ht[cur]->next = ht[cur->next];
        if (cur->random) ht[cur]->random = ht[cur->random];
    }

    return ht[head];
}
/*
哈希表实现深拷贝
1. 每个节点作为key，先创建和他们value一样的节点，不添加连接关系。
2. 第二次循环通过哈希表和原始的关系，创建链接关系。
*/