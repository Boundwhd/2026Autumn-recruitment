/*分隔链表*/
#include "../leetcode.h"

ListNode* partition(ListNode* head, int x) {
    ListNode* ll = new ListNode(0);
    ListNode* lr = new ListNode(0);
    ListNode* ll_cur = ll;
    ListNode* lr_cur = lr;
    ListNode* cur = head;

    while (cur) {
        if (cur->val < x) {
            ll_cur->next = new ListNode(cur->val);
            ll_cur = ll_cur->next;
        } else {
            lr_cur->next = new ListNode(cur->val);
            lr_cur = lr_cur->next;
        }
        cur = cur->next;
    }
    ll_cur->next = lr->next;
    
    return ll->next; 
}