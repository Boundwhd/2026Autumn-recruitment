class MyLinkedList {
public:
    struct ListNode {
        int val;
        ListNode* next;
        ListNode(int x) : val(x), next(nullptr) {}
    };

    MyLinkedList() {
        _dummyHead = new ListNode(0);
        _size = 0;
    }
    
    int get(int index) {
        if (index > (_size - 1) || index < 0) {
            return -1;
        }
        ListNode* cur = _dummyHead->next;
        while (index--) {
            cur = cur->next;
        }
        return cur->val;
    }
    
    void addAtHead(int val) {
        ListNode* node = new ListNode(val);
        ListNode* head = _dummyHead->next;
        _dummyHead->next = node;
        node->next = head;
        _size++;
    }
    
    void addAtTail(int val) {
        ListNode* cur = _dummyHead;
        while (cur && cur->next) {
            cur = cur->next;
        }
        cur->next = new ListNode(val);
        _size++;
    }
    
    void addAtIndex(int index, int val) {
        if (index == _size) {
            addAtTail(val);
        } else {
            if(index < 0 || index > _size) {
                return;
            } else {
                ListNode* cur = _dummyHead;
                for (int i = 0; i < index; i++) {
                    cur = cur->next;
                }
                ListNode* node = new ListNode(val);
                ListNode* next = cur->next;
                cur->next = node;
                node->next = next;
                _size++;
            }
        }
    }
    
    void deleteAtIndex(int index) {
        if (index >= _size || index < 0) {
            return;
        }
        ListNode* cur = _dummyHead;
        while(index--) {
            cur = cur ->next;
        }
        ListNode* tmp = cur->next;
        cur->next = cur->next->next;
        delete tmp;
        tmp=nullptr;
        _size--;
    }

private:
    ListNode* _dummyHead;
    int _size;
};