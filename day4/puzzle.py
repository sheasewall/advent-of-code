import re
import numpy as np
import solver

## Puzzle 1
XMAS_pattern = re.compile("XMAS")

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

def parse_word_search_simpler(file_name):
    with open(file_name, 'r') as file:
        return np.array([list(line.strip()) for line in file])

def pad_array(array):
    return np.pad(array, 1)

def diagonals(array):
    diags = []
    
    for i in range(array.shape[1]):
        diag = array.diagonal(i)
        diags.append(''.join(diag.tolist()))
        
    for i in range(1, array.shape[0]):
        diag = array.diagonal(-i)
        diags.append(''.join(diag.tolist()))
    
    return ''.join(diags)

def slice_and_count_diags(padded_array):
    score = 0
    
    diags = diagonals(padded_array)
    anti_diags = diagonals(np.rot90(padded_array))
        
    score += count_xmas(diags)
    score += count_xmas(diags[::-1])
    score += count_xmas(anti_diags)
    score += count_xmas(anti_diags[::-1])
    
    return score

def slice_and_count_orthogs(padded_array):
    score = 0
    
    rows = padded_array.flatten('C').tolist()
    rows_concatenated = ''.join(rows)
    cols = padded_array.flatten('F').tolist()
    cols_concatenated = ''.join(cols)
    
    score += count_xmas(rows_concatenated)
    score += count_xmas(rows_concatenated[::-1])
    score += count_xmas(cols_concatenated)
    score += count_xmas(cols_concatenated[::-1])

    return score
    
def count_xmas(str):
    return len(re.findall(XMAS_pattern, str))

def solve_puzzle1(array):
    array = pad_array(array)
    return slice_and_count_orthogs(array) + slice_and_count_diags(array)

puzzle1_solver = solver.Solver("wordsearch", 4, 1, parse_word_search, solve_puzzle1)
puzzle1_solver_fast_parse = solver.Solver("uses pythonic parser", 4, 1, parse_word_search_simpler, solve_puzzle1)

## Puzzle 2
""" 
The X- MAS pattern can still be found with a regex. 
For an R x C shaped word search and the shape:
            M . M   
            . A . 
            S . S 
we want M, a char, M, then R-3 worth of chars to 
line back up with the edge of the square pattern.
Then we want a char, A, a char, then R-3 chars.
Then we need S, a char, then S. 
"M.M.{R-3}.A..{R-3}S.S"

Those {R-3} chars must allow newlines, but the other
dots must not, else they will match squares that 
are split across lines.
"M.M(.|\\n){R-3}.A.(.|\\n){R-3}S.S"

In all configurations, the middle part is the same.
"(.|\\n){R-3}.A.(.|\\n){R-3}"

We also want to use non-capturing groups, so that 
the long stretches of characters in the middle 
doesn't overlap other potential matches
M . M  M . S  S . S  S . M  
. A .  . A .  . A .  . A .
S . S  M . S  M . M  S . M


"""
def count_mas_xs(array, middle_section, pad_with):
    array = np.pad(array, ((0, 0), (0, 1)), constant_values=pad_with)
    rows = array.flatten('C').tolist()
    rows_concatenated = ''.join(rows)
    
    pos_1 = f'(?=(M.M{middle_section}S.S))'
    pos_2 = f'(?=(M.S{middle_section}M.S))'
    pos_3 = f'(?=(S.S{middle_section}M.M))'
    pos_4 = f'(?=(S.M{middle_section}S.M))'
    x_regex = re.compile(f"{pos_1}|{pos_2}|{pos_3}|{pos_4}")
    
    return len(re.findall(x_regex, rows_concatenated))

def solve_puzzle2(array):
    # It takes len(row) - 3 to go from the end of #.# to the 
    # beginning of .A.  If we include the . on either side of
    # the A, then it takes len(row) - 2 to get to the A
    # Then, we have to capture an additional . for the 
    # 0 that we pad at the end of every row. 
    offset = array[0].size - 1
    middle_section = f".{{{offset}}}A.{{{offset}}}"
    return count_mas_xs(array, middle_section, pad_with=0)

puzzle2_solver_fast_parse = solver.Solver("puzzle2", 4, 2, parse_word_search_simpler, solve_puzzle2)

def solve_puzzle2_newline(array):
    # The offset here is one less, as we do not include the . 
    # on either side of the A. This is because we are padding
    # with newlines, which those dots on either side of A 
    # should NOT match in order for the edge of the array
    # to not split the X. The other junk characters, however, 
    # must be able to include the newline otherwise. In fact,
    # both stretches necessarily have a single newline contained 
    # within it. 
    offset = array[0].size - 2
    middle_section = f"(.|\\n){{{offset}}}.A.(.|\\n){{{offset}}}"
    return count_mas_xs(array, middle_section, '\n')

puzzle2_solver_new_line = solver.Solver("newline", 4, 2, parse_word_search_simpler, solve_puzzle2_newline)

def count_kura(array, middle_section, pad_with):
    array = np.pad(array, ((0, 0), (0, 1)), constant_values=pad_with)
    rows = array.flatten('C').tolist()
    rows_concatenated = ''.join(rows)
    
    x = f'(?=(M|S).(S|M){middle_section}(?!\2)[MS].(?!\1)[MS])'
    x_regex = re.compile(x)
    
    return len(re.findall(x_regex, rows_concatenated))

def solve_puzzle2_kura(array):
    offset = array[0].size - 1
    middle_section = f".{{{offset}}}A.{{{offset}}}"
    return count_kura(array, middle_section, pad_with=0)

puzzle2_solver_kura = solver.Solver("kura", 4, 2, parse_word_search_simpler, solve_puzzle2_kura)