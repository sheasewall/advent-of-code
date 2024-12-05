import re
import numpy as np
import solver

XMAS_pattern = re.compile("XMAS")

def pad_array(array):
    return np.pad(array, 1)

def diagonals(array):
    strs = []
    
    for i in range(array.shape[1]):
        diag = array.diagonal(i)
        strs.append(_1d_to_string(diag))
        
    for i in range(1, array.shape[0]):
        diag = array.diagonal(-i)
        strs.append(_1d_to_string(diag))
    
    arr = np.array(strs).T
    diag = _1d_to_string(arr[0])[0]
    diag_rev = _1d_to_string(arr[1])[0]
        
    return (diag, diag_rev)

def count_diags(array):
    score = 0
    array = pad_array(array.copy())
    
    diags = diagonals(array)
    score += count_xmas(diags[0])
    score += count_xmas(diags[1])
    
    diags_up = diagonals(np.rot90(array))
    score += count_xmas(diags_up[0])
    score += count_xmas(diags_up[1])
    
    return score
        
def _1d_to_string(_1d_arr):
    char_list = _1d_arr.tolist()
    char_list_rev = char_list.copy()
    char_list_rev.reverse()
    return (''.join(char_list), ''.join(char_list_rev))

def count_rows_and_cols(array):
    score = 0
    array = pad_array(array.copy())
    row_arr = array.flatten('C')
    col_arr = array.flatten('F')
    row_str, row_str_rev = _1d_to_string(row_arr)
    col_str, col_str_rev = _1d_to_string(col_arr)
    
    score += count_xmas(row_str)
    score += count_xmas(row_str_rev)
    score += count_xmas(col_str)
    score += count_xmas(col_str_rev)

    return score
    

def count_xmas(str):
    return len(re.findall(XMAS_pattern, str))


def parse_word_search(file_name):
    cols = []
    with open(file_name, 'r') as file:
        row = []
        for line in file:
            for char in line:
                if char != '\n':
                    row.append(char)
            cols.append(row.copy())
            row.clear()
                
    return np.array(cols)

def solve_puzzle1(array):
    return count_rows_and_cols(array) + count_diags(array)

puzzle1_solver = solver.Solver("wordsearch", 4, 1, parse_word_search, solve_puzzle1)