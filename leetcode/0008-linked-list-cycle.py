# LeetCode 142. Linked List Cycle II
# Link: https://leetcode.com/problems/linked-list-cycle-ii/
#
# Idea (Floyd’s Tortoise and Hare algorithm):
#   - Phase 1: Detect if a cycle exists
#       * Use two pointers: slow moves 1 step, fast moves 2 steps.
#       * If fast reaches the end (null), no cycle.
#       * If slow == fast, cycle detected (first meeting point).
#
#   - Phase 2: Find the cycle entrance
#       * Place a new pointer p at head.
#       * Move p and slow one step at a time.
#       * They will meet at the cycle entry node.
#
# Why Phase 2 works:
#   - Let: 
#       * head → entry distance = a
#       * entry → meeting point distance = b
#       * cycle length = c
#   - After meeting: slow走了 a+b，fast走了 2(a+b)。
#   - 由 fast = slow + k*c 得 2(a+b) = a+b + k*c → a = k*c - b。
#   - 所以从 head 走 a 步、从 meeting 走 (k*c - b) 步，都会到 entry。
#
# Complexity:
#   - Time: O(n), at most 2 passes.
#   - Space: O(1), only constant pointers.
#
# Interview takeaway:
#   - “Floyd’s cycle detection” has two phases: detect cycle, then find entry.
#   - Proof relies on distance analysis in the cycle.

class Solution:
    def detectCycle(self, head):
        slow = fast = head
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            if slow == fast:            # first meeting
                p = head                # new pointer from head
                while p != slow:        # move together
                    p = p.next
                    slow = slow.next
                return p                # cycle entry
        return None
