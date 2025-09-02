# LeetCode 206. Reverse Linked List
# Link: https://leetcode.com/problems/reverse-linked-list/
#
# Idea (Iterative with 3 pointers):
#   - Maintain three pointers:
#       * cur  = current node being processed
#       * prev = already reversed part (initially None)
#       * nxt  = temporarily stores cur.next
#   - Steps in each iteration:
#       1) Save nxt = cur.next (avoid losing the rest of the list).
#       2) Reverse the pointer: cur.next = prev.
#       3) Advance pointers: prev = cur, cur = nxt.
#   - Continue until cur == None.
#   - At the end, prev points to the new head.
#
# Example:
#   Input:  1 -> 2 -> 3 -> None
#   Iter1:  1 -> None, prev=1, cur=2
#   Iter2:  2 -> 1 -> None, prev=2, cur=3
#   Iter3:  3 -> 2 -> 1 -> None, prev=3, cur=None
#   Output: prev = 3 (new head)
#
# Complexity:
#   - Time: O(n), each node visited once.
#   - Space: O(1), only constant extra pointers.
#
# Interview takeaways:
#   - Key is to avoid breaking the chain → always store cur.next in nxt first.
#   - prev accumulates the reversed part step by step.

class Solution:
    def reverseList(self, head):
        prev, cur = None, head
        while cur:
            nxt = cur.next
            cur.next = prev
            prev, cur = cur, nxt
        return prev
# Definition for singly-linked list.