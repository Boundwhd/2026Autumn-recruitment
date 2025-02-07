/*删除排序链表中的重复元素II*/
#include "../leetcode.h"

ListNode* deleteDuplicates(ListNode* head) {
    if (!head || !head->next) return head;

    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    ListNode *p = dummy;

    while (p->next) {
        ListNode *q = p->next;

        while (q->next && q->val == q->next->val) q = q->next;

        if (q == p->next) p = p->next;
        else p->next = q->next;
    }

    return dummy->next;
}