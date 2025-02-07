/*两数相加*/
#include "../leetcode.h"

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int sum = 0;
    ListNode *dummy = new ListNode(0);
    ListNode *cur = dummy;
    while (l1 || l2 || sum) {
        if (l1) {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2) {
            sum += l2->val;
            l2 = l2->next;
        }
        cur->next = new ListNode(sum % 10);
        cur = cur->next;
        sum /= 10;
    } 
    return dummy->next;
}