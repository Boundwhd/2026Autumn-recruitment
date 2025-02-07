/*合并两个有序链表*/
#include "../leetcode.h"

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode *dummy = new ListNode(0);
    ListNode *cur = dummy;

    while (list1 && list2) {
        if (list1->val <= list2->val) {
            cur->next = new ListNode(list1->val);
            list1 = list1->next;
        } else {
            cur->next = new ListNode(list2->val);
            list2 = list2->next;
        }
        cur = cur->next;
    }
    while (list1) {
        cur->next = new ListNode(list1->val);
        list1 = list1->next;
        cur = cur->next;
    }
    while (list2) {
        cur->next = new ListNode(list2->val);
        list2 = list2->next;
        cur = cur->next;
    }

    return dummy->next;
}