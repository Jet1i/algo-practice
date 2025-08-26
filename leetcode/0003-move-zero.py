# LeetCode 283. Move Zeroes
# Link: https://leetcode.com/problems/move-zeroes/
#
# Idea 1 (Two Pointers with Swapping):
#   - Use two pointers: fast scans all elements, slow tracks the next 
#     position to place a non-zero.
#   - If nums[fast] != 0:
#       swap nums[slow] and nums[fast], then increment slow.
#   - Ensures non-zero elements keep their relative order, 
#     zeros are pushed to the end.
# Complexity: O(n) time, O(1) space
#
# Idea 2 (Two Pointers with Overwrite + Fill Zeros):
#   - Use fast to read and slow to write non-zero elements sequentially.
#   - After placing all non-zeros, fill the rest of the array with zeros.
#   - Avoids some unnecessary swaps when slow == fast.
# Complexity: O(n) time, O(1) space

class Solution:
    # Idea 1: Swapping version
    def moveZeroes_swap(self, nums):
        slow = 0
        for fast in range(len(nums)):
            if nums[fast] != 0:
                nums[slow], nums[fast] = nums[fast], nums[slow]
                slow += 1

    # Idea 2: Overwrite + fill zeros version
    def moveZeroes_fill(self, nums):
        slow = 0
        for fast in range(len(nums)):
            if nums[fast] != 0:
                nums[slow] = nums[fast]
                slow += 1
        for i in range(slow, len(nums)):
            nums[i] = 0
