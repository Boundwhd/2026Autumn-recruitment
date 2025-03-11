struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
    public:
        ListNode* swapPairs(ListNode* head) {

            if (!head || !head->next) return head;
    
            ListNode* newHead = head->next;  
            ListNode* prev = nullptr;
            ListNode* curr = head;
    
            while (curr && curr->next) {
                ListNode* next = curr->next;
                curr->next = next->next;
                next->next = curr;
    
                if (prev) {
                    prev->next = next;
                }
    
                prev = curr;
                curr = curr->next;
            }
    
            return newHead;
        }
    };