/*LRU缓存*/
#include "../leetcode.h"

struct Node {
    int key, val;
    Node *prev, *next;
    Node(): key(0), val(0), prev(nullptr), next(nullptr) {}
    Node(int _key, int _val): key(_key), val(_val), prev(nullptr), next(nullptr) {}
};

class LRUCache {
public:
    Node *head, *tail;
    unordered_map<int, Node*> h;
    int capacity, size;

    LRUCache(int _capacity) : capacity(_capacity) , size(0){
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (!h.count(key)) return -1;
        Node *node = h[key];
        removeNode(node);
        addNodeToHead(node);
        return node->val;
    }
    
    void put(int key, int value) {
        if (h.count(key)) {
            Node *node = h[key];
            node->val = value;
            removeNode(node);
            addNodeToHead(node);
        } else {
            if (size == capacity) {
                Node* removed = tail->prev;
                h.erase(removed->key);
                removeNode(removed);
                size--;
            }
            Node *node = new Node(key, value);
            addNodeToHead(node);
            h[key] = node;
            size++;
        }
    }

    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void addNodeToHead(Node* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }
};