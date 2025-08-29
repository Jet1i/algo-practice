# LeetCode 350. Intersection of Two Arrays II
# Link: https://leetcode.com/problems/intersection-of-two-arrays-ii/
#
# Idea 1 (Hash Counting, recommended):
#   - Count frequency of elements in nums1 using a hash map (dict/Counter).
#   - Iterate through nums2:
#       * If element exists in the counter (count > 0), add to result and decrement count.
#   - To save space, always build the counter on the shorter array.
#
# Complexity:
#   - Time: O(m + n), where m = len(nums1), n = len(nums2).
#   - Space: O(min(m, n)) for the counter.
#
# Idea 2 (Sorting + Two Pointers):
#   - Sort both arrays.
#   - Use two pointers to traverse:
#       * If nums1[i] == nums2[j], add to result and move both pointers.
#       * Otherwise, move the smaller one forward.
#
# Complexity:
#   - Time: O(m log m + n log n) due to sorting.
#   - Space: O(1), if sort is in-place (depends on implementation).
#
# Interview takeaways:
#   - "If memory is fine, counting on the shorter array gives O(m+n). 
#      If I must avoid extra memory, sort both arrays and use two pointers."

# Hash counting solution
class Solution:
    def intersect(self, nums1, nums2):
        if len(nums1) > len(nums2):  # ensure nums1 is shorter for space
            nums1, nums2 = nums2, nums1
        from collections import Counter
        cnt = Counter(nums1)
        res = []
        for x in nums2:
            if cnt.get(x, 0) > 0:
                res.append(x)
                cnt[x] -= 1
        return res

# Sorting + two pointers solution
class Solution:
    def intersect(self, nums1, nums2):
        nums1.sort(); nums2.sort()
        i = j = 0
        res = []
        while i < len(nums1) and j < len(nums2):
            if nums1[i] == nums2[j]:
                res.append(nums1[i]); i += 1; j += 1
            elif nums1[i] < nums2[j]:
                i += 1
            else:
                j += 1
        return res
