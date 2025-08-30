# LeetCode 21. Merge Two Sorted Lists
# Link: https://leetcode.com/problems/merge-two-sorted-lists/
#
# Idea (Iterative merge with dummy head):
#   - Both l1 and l2 are sorted linked lists.
#   - Use a dummy head node to simplify edge cases.
#   - Maintain a pointer `cur`:
#       * Compare l1.val and l2.val.
#       * Attach the smaller one to cur.next, advance that list.
#       * Move cur forward.
#   - After loop, if one list still has remaining nodes, attach it directly.
#   - Return dummy.next as the head of the merged list.
#
# Complexity:
#   - Time: O(m + n), each node is visited once.
#   - Space: O(1), only pointers are used (no extra nodes created).
#
# Interview takeaways:
#   - Dummy head avoids handling "first node" separately.
#   - Careful with pointer moves: update `cur.next` first, then advance pointer.

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

class Solution:
    def mergeTwoLists(self, l1, l2):
        dummy = ListNode(-1)
        cur = dummy
        while l1 and l2:
            if l1.val <= l2.val:
                cur.next, l1 = l1, l1.next
            else:
                cur.next, l2 = l2, l2.next
            cur = cur.next
        cur.next = l1 if l1 else l2
        return dummy.next
