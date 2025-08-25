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


📘 Study Notes
1. What is a Hash Table?

A hash table is a data structure that stores data in key–value pairs.

It uses a hash function to map a key to an index in an internal array, where the value is stored.

Main features:

Fast lookup, insert, delete: average time complexity ≈ O(1).

Unordered: keys are not stored in a predictable sequence.

Collision handling: different keys may map to the same index, solved by chaining or open addressing.

Examples in programming languages:

Python → dict

C++ → unordered_map

Java → HashMap

Example (Python):

phonebook = {"Alice": "1234", "Bob": "5678"}
print(phonebook["Alice"])  # Output: 1234

2. The Function of enumerate in Python

enumerate(iterable) is a built-in Python function that adds a counter (index) to an iterable.

It returns pairs (index, value) for each element in the sequence.

Example:

nums = [10, 20, 30]
for i, num in enumerate(nums):
    print(i, num)


Output:

0 10
1 20
2 30


Without enumerate, you’d have to write:

for i in range(len(nums)):
    num = nums[i]


which is more verbose.

In LeetCode Two Sum:

for i, num in enumerate(nums):


means we get both the index (i) and the number (num) at the same time while iterating.