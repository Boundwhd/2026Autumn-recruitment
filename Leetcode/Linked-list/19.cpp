/*删除链表的倒数第N个节点*/
#include "../leetcode.h"

ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode* slow = dummy;
        ListNode* fast = dummy;

        for (int i = 0; i < n; i++) {
            fast = fast->next;
        }

        while (fast->next) {
            slow = slow->next;
            fast = fast->next;
        }

        slow->next = slow->next->next;

        return dummy->next;
    }

/*快慢指针，最后一步只通过慢指针找位置*/