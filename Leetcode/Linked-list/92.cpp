/*反转链表II*/
#include "../leetcode.h"

ListNode* reverseBetween(ListNode* head, int left, int right) {
    if (left == right) return head;

    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    ListNode *pre = dummy;
    for (int i = 0; i < left - 1; i++) {
        pre = pre->next;
    }
    ListNode *cur = pre->next;
    for (int i = 0; i < right - left; i++) {
        ListNode *nextt = cur->next;
        cur->next = nextt->next;
        nextt->next = pre->next; 
        pre->next = nextt;
    }
    return dummy->next;
}