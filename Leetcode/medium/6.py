# https://leetcode.com/problems/zigzag-conversion/

class Solution:
    def convert(self, s: str, numRows: int) -> str:        
        if (numRows == 1):
            return s
        
        group_len = 1 + numRows - 2 # number of cols per group
        group_chars = numRows + group_len - 1 # number of chars in a group
        # print(group_len, group_chars)
        
        num_full_groups = floor(len(s)/group_chars) # number of full groups
        num_chars_in_last_group = len(s) % group_chars
        # print(num_full_groups, num_chars_in_last_group)
        num_cols_last_group = max(1, num_chars_in_last_group - numRows + 1)
        # print(num_cols_last_group)
        
        # print(num_full_groups, group_len)
        arr_num_cols = num_full_groups * group_len
        # print(arr_num_cols)
        if num_chars_in_last_group > 0:
            arr_num_cols += num_cols_last_group
            
        # print(arr_num_cols)
        arr = [['_' for x in range(arr_num_cols)] for x in range(numRows)]
        
        curr_row = 0 # reallyy the next row
        curr_col = 0 # ry the next col
        
        for i in range(len(s)):
            arr[curr_row][curr_col] = s[i]
            if curr_col % group_len == 0:
                curr_row += 1
                if curr_row >= numRows:
                    curr_row -= 2
                    curr_col += 1
            else:
                curr_row -= 1
                curr_col += 1
                    
        # for i in range(numRows):
        #     print(arr[i])
            
        res_list = []
        for i in range(numRows):
            for j in range(arr_num_cols):
                if arr[i][j] != '_':
                    res_list.append(arr[i][j])
        
        return "".join(res_list)
            