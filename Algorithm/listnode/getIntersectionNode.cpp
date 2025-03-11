struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB) return nullptr;
        ListNode* l1 = headA;
        ListNode* l2 = headB;
        int cntA = 0, cntB = 0;
        while (l1 != l2) {
            if (l1->next) {
                l1 = l1->next;
            } else {
                l1 = headB;
                cntA++;
            }
            if (l2->next) {
                l2 = l2->next;
            } else {
                l2 = headA;
                cntB++;
            }
            if (cntA >= 2 || cntB >= 2) return nullptr;
        }
        return l1;
    }
};