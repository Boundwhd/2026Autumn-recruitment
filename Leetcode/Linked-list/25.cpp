/*k个一组翻转链表*/
#include "../leetcode.h"

ListNode* reverseKGroup(ListNode* head, int k) {
    if (k == 1) return head;

    int num_node = 0;
    for (ListNode *node_cnt = head; node_cnt; node_cnt = node_cnt->next) {
        num_node++;
    }
    int group = num_node / k;

    ListNode* dummy = new ListNode(0);
    dummy->next = head;
    ListNode* pre = dummy;
    ListNode* cur = pre->next;
    while (group) {
        for (int i = 0; i < k - 1; i++) {
            ListNode *nextt = cur->next;
            cur->next = nextt->next;
            nextt->next = pre->next; 
            pre->next = nextt;
        }
        pre = cur;
        cur = cur->next;
        group--;
    }
    return dummy->next;
}