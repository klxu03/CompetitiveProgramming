#  https://leetcode.com/problems/longest-palindromic-substring/

class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        myMap = {}
        start = 0
        res = 0

        for i in range(len(s)):
            if s[i] in myMap:
                start = myMap[s[i]] + 1
            res = max(res, i - start + 1)
            myMap[s[i]] = i

        return res           