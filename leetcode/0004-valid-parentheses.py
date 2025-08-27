# LeetCode 20. Valid Parentheses
# Link: https://leetcode.com/problems/valid-parentheses/
#
# Idea (Stack Matching):
#   - Use a stack to check if every closing bracket has a matching opening bracket.
#   - Store mapping of closing -> opening in a dictionary: {')':'(', ']':'[', '}':'{'}.
#   - Iterate through characters in the string:
#       - If it's an opening bracket, push it to the stack.
#       - If it's a closing bracket:
#           * Check if stack is not empty AND top of stack matches the expected opening.
#           * If not, return False immediately.
#           * Otherwise, pop the stack.
#   - At the end, if the stack is empty, return True (all matched).
#   - If stack is not empty, return False (some openings have no closing).
#
# Complexity:
#   - Time: O(n), each character is pushed and popped at most once.
#   - Space: O(n), in worst case stack holds all opening brackets.

class Solution:
    def isValid(self, s: str) -> bool:
        pairs = {')': '(', ']': '[', '}': '{'}
        stack = []
        for ch in s:
            if ch in '([{':
                stack.append(ch)
            else:
                if not stack or stack[-1] != pairs.get(ch, '#'):
                    return False
                stack.pop()
        return not stack
