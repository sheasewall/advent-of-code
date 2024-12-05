import re 

import solver

get_mults_pattern = re.compile("(mul\([0-9]{1,3},[0-9]{1,3}\))")
get_digits_pattern = re.compile("[0-9]{1,3}")

## Puzzle 1
def read_str(file_name):
    with open(file_name, 'r') as file:
        str = file.read()
    
    return str

def do_multiplication(mul_str):
    nums = re.findall(get_digits_pattern, mul_str)
    return int(nums[0]) * int(nums[1])

def solve_puzzle1(str):
    matches = re.findall(get_mults_pattern, str)
    sum = 0 
    for match in matches:
        sum += do_multiplication(match)
        
    return sum

puzzle1_solver = solver.Solver("regex", 3, 1, read_str, solve_puzzle1)

## Puzzle 2
get_mults_and_conds_pattern = re.compile("(mul\([0-9]{1,3},[0-9]{1,3}\))|(do\(\))|(don\'t\(\))")

def solve_puzzle2(str):
    matches = re.findall(get_mults_and_conds_pattern, str)
    sum = 0
    is_enabled = True
    for match in matches:
        if match[1]:
            is_enabled = True 
        elif match[2]:
            is_enabled = False
        elif is_enabled:
            sum += do_multiplication(match[0])

    return sum

puzzle2_solver = solver.Solver("regex", 3, 2, read_str, solve_puzzle2)
