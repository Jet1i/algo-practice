# 📘 Study Notes - LeetCode 242. Valid Anagram
#
# 1. Python Function Type Hints
#    - In Python 3.5+, you can annotate parameters and return types:
#        def isAnagram_sorting(self, s: str, t: str) -> bool:
#    - Here `s: str` means s is a string, `-> bool` means the function returns a boolean.
#    - Improves readability and helps with static analysis.
#
# 2. The sorted() Function
#    - Returns a new sorted list from the items of any iterable.
#    - For strings, it sorts characters by Unicode code point.
#    - Example:
#        sorted("listen")  # ['e', 'i', 'l', 'n', 's', 't']
#        sorted("silent")  # ['e', 'i', 'l', 'n', 's', 't']
#    - In Valid Anagram: if sorted(s) == sorted(t), then they are anagrams.
#
# 3. collections.Counter
#    - Counter is a dict subclass that counts hashable objects.
#    - Example:
#        from collections import Counter
#        Counter("anagram")  # Counter({'a': 3, 'n': 1, 'g': 1, 'r': 1, 'm': 1})
#    - In Valid Anagram: compare Counter(s) == Counter(t).
#    - Complexity: O(n) time, O(n) space.
#
# 4. Unicode in Python
#    - In Python 3, str is Unicode by default.
#    - Supports characters from all languages and emojis.
#    - Example:
#        s = "你好🙂"
#        for ch in s:
#            print(ch)
#        # Output:
#        # 你
#        # 好
#        # 🙂
#    - len("你") == 1 (not 3 bytes as in C/C++).
#    - sorted() and Counter() work with Unicode out of the box.
#    - Note: some characters have multiple representations (é vs e + ´).
#      Use unicodedata.normalize() if strict equality is needed.


# LeetCode 242. Valid Anagram
# Link: https://leetcode.com/problems/valid-anagram/
# Idea 1 (Sorting):
#   - If two strings are anagrams, their sorted characters must match.
#   - Compare sorted(s) with sorted(t).
# Complexity: O(n log n) time, O(1) extra space (ignoring sorting output)

# Idea 2 (Hashmap/Counter):
#   - Count the frequency of each character in both strings.
#   - If counts match, they are anagrams.
#   - In Python, collections.Counter makes this easy.
# Complexity: O(n) time, O(n) space

class Solution:
    # Sorting approach
    def isAnagram_sorting(self, s: str, t: str) -> bool:
        if len(s) != len(t):
            return False
        return sorted(s) == sorted(t)

    # Hashmap / Counter approach
    def isAnagram_hashmap(self, s: str, t: str) -> bool:
        from collections import Counter
        return Counter(s) == Counter(t)
