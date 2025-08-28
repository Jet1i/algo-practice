# LeetCode 217. Contains Duplicate
# Link: https://leetcode.com/problems/contains-duplicate/
#
# Idea (HashSet for Fast Lookup):
#   - Use a hash set (Python `set`) to record numbers we've seen.
#   - Iterate through the array:
#       * If the current number is already in the set → duplicate found → return True.
#       * Otherwise, add the number into the set.
#   - If loop finishes without finding duplicates, return False.
#
# Why it works:
#   - HashSet provides average O(1) time for both membership check (`x in set`) 
#     and insertion (`set.add(x)`).
#   - So we can detect duplicates in one pass.
#
# Complexity:
#   - Time: O(n), each element is checked/inserted once.
#   - Space: O(n), extra set stores up to all distinct elements.

class Solution:
    def containsDuplicate(self, nums):
        seen = set()
        for x in nums:
            if x in seen:
                return True
            seen.add(x)
        return False
