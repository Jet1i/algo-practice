# LeetCode 155. Min Stack
# Link: https://leetcode.com/problems/min-stack/
#
# Idea (Stack + Auxiliary Min Stack):
#   - Maintain two stacks:
#       * st     : normal stack, stores all pushed values.
#       * min_st : auxiliary stack, keeps track of the current minimums.
#   - Push:
#       * Always push val into st.
#       * If min_st is empty OR val <= current min, also push val into min_st.
#   - Pop:
#       * Pop from st.
#       * If popped value equals min_st[-1], pop from min_st as well.
#   - Top:
#       * Return the top of st.
#   - getMin:
#       * Return the top of min_st (current minimum).
#
# Why it works:
#   - min_st only updates when a new minimum appears (or ties).
#   - When that minimum is removed, it’s popped from both stacks.
#   - Thus min_st[-1] always represents the minimum of st.
#
# Complexity:
#   - Time: O(1) for all operations (push, pop, top, getMin).
#   - Space: O(n) for the two stacks.
#
# Interview takeaway:
#   - This is a classic “support getMin in O(1)” design.
#   - Key is to maintain an auxiliary stack that mirrors the minima.

class MinStack:
    def __init__(self):
        self.st = []
        self.min_st = []

    def push(self, val: int) -> None:
        self.st.append(val)
        if not self.min_st or val <= self.min_st[-1]:
            self.min_st.append(val)

    def pop(self) -> None:
        x = self.st.pop()
        if x == self.min_st[-1]:
            self.min_st.pop()

    def top(self) -> int:
        return self.st[-1]

    def getMin(self) -> int:
        return self.min_st[-1]
# Your MinStack object will be instantiated and called as such:
# obj = MinStack()
# obj.push(val)
# obj.pop()
# param_3 = obj.top()
# param_4 = obj.getMin()