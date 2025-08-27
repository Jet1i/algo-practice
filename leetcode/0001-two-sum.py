# LeetCode 1. Two Sum
# Link: https://leetcode.com/problems/two-sum/
# Idea:
#   - Use a hashmap to store seen numbers.
#   - For each number, check if target - num exists.
# Complexity: O(n) time, O(n) space

class Solution:
    def twoSum(self, nums, target):
        lookup = {}
        for i, num in enumerate(nums):
            if target - num in lookup:
                return [lookup[target - num], i]
            lookup[num] = i


# 📘 Study Notes
# 1. What is a Hash Table?
#    - A hash table stores key–value pairs, maps key → index via a hash function.
#    - Fast lookup/insert/delete: average O(1).
#    - Unordered, may have collisions (solved by chaining or open addressing).
#    - Examples: Python dict, C++ unordered_map, Java HashMap.
#    - Example:
#        phonebook = {"Alice": "1234", "Bob": "5678"}
#        print(phonebook["Alice"])  # Output: 1234
#
# 2. The Function of enumerate in Python
#    - enumerate(iterable) adds an index to each element.
#    - Example:
#        nums = [10, 20, 30]
#        for i, num in enumerate(nums):
#            print(i, num)
#      Output:
#        0 10
#        1 20
#        2 30
#    - In Two Sum:
#        for i, num in enumerate(nums):
#      gives both index and value at once.