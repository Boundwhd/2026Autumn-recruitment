/*旋转链表*/
#include "../leetcode.h"

ListNode* rotateRight(ListNode* head, int k) {
    if (k == 0 || !head || !head->next) return head;

    int cnt = 0;
    ListNode* cnt_node = head;
    while (cnt_node->next) {
        cnt++;
        cnt_node = cnt_node->next;
    }
    cnt++;
    cnt_node->next = head;

    k %= cnt;

    for (int i = 0; i < cnt - k; i++) {
        cnt_node = cnt_node->next;
    }

    ListNode* ans = cnt_node->next;
    cnt_node->next = nullptr;
    return ans;
}