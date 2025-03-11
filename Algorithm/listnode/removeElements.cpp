struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        ListNode* cur = dummy;
        while (cur) {
            ListNode* next = cur->next;
            if (next && next->val == val) {
                cur->next = next->next;
            } else {
                cur = cur->next;
            }
        }
        return dummy->next;
    }
};