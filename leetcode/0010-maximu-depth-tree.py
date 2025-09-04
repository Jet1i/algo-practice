# LeetCode 104. Maximum Depth of Binary Tree
# Link: https://leetcode.com/problems/maximum-depth-of-binary-tree/
#
# Idea (Recursion / Divide & Conquer):
#   - Definition: depth(root) = 0 if root is None,
#                 else 1 + max(depth(root.left), depth(root.right)).
#   - Base case:
#       * If root == None → return 0.
#   - Recursive case:
#       * Call maxDepth on left and right children.
#       * Return 1 + max(left_depth, right_depth).
#
# Why recursion works:
#   - Each subtree is itself a binary tree.
#   - So we can directly call self.maxDepth(root.left) and self.maxDepth(root.right).
#   - Recursion naturally terminates at empty nodes (None).
#
# Example:
#       3
#      / \
#     9  20
#        / \
#       15  7
#   depth(3) = 1 + max(depth(9), depth(20))
#   depth(9) = 1
#   depth(20) = 1 + max(depth(15), depth(7)) = 2
#   → total = 3
#
# Complexity:
#   - Time: O(n), each node visited once.
#   - Space: O(h), recursion stack, h = tree height.
#
# Interview takeaway:
#   - This is a classic recursion pattern on trees:
#       "Answer at node = f(answer(left), answer(right))".
#   - Base case: return 0 for None.
#   - Recursive case: 1 + max(left, right).

class Solution:
    def maxDepth(self, root):
        if not root:
            return 0
        return 1 + max(self.maxDepth(root.left), self.maxDepth(root.right))
