# https://leetcode.com/problems/longest-palindromic-substring/

class Solution:
    def longestPalindrome(self, s: str) -> str:
        dp = [[0 for x in range(len(s))] for x in range(len(s))]
        start = 0
        end = 1
        
        # let's make all the diagonals 1
        for i in range(len(s)):
            dp[i][i] = 1
        
        for j in range(1, len(s)): # col
            for i in range(j): # row, not j + 1 since don't need to go to diagonal which is 1
                if s[i] == s[j]:
                    if s[i] == s[j] and dp[i + 1][j - 1]:
                        dp[i][j] = 1
                    elif (s[i] == s[j] and s[i] == s[j - 1]) and j - i == 1:
                        dp[i][j] = 1
        
        start = 0
        end = 0
        for i in range(len(dp)):
            for j in range(len(dp[i])):
                if dp[i][j] and j - i > end - start:
                    start = i;
                    end = j;
        
        return s[start:end+1]