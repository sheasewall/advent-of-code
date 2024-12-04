import solver

## Puzzle 1
# Read file into report list
def read_reports(file_name):
    reports = []
    with open(file_name, 'r') as file:
        for line in file:
            report = [int(x) for x in line.split()]
            reports.append(report)
    
    return reports

# Checks whether a report is safe,
# assuming that it is decreasing
def is_safe_decreasing(report):
    for i in range(len(report) - 1):
        if report[i] <= report[i+1] or report[i] - 3 > report[i+1]:
            return False
        
    return True

# Checks whether a report is safe,
# assuming that it is increasing
def is_safe_increasing(report):
    for i in range(len(report) - 1):
        if report[i] >= report[i+1] or report[i] + 3 < report[i+1]:
            return False
        
    return True

# Checks whether a report is safe.
# Examines the first two elements to
# determine if increasing or decreasing
def is_safe(report):
    first_el = report[0]
    second_el = report[1]
    
    #decreasing
    if first_el > second_el:
        return is_safe_decreasing(report)
        
    #increasing
    if first_el < second_el:
        return is_safe_increasing(report)
    
    #equal -> not safe
    return False

# Checks whether a report is safe.
# Blindly checks both ascending
# and descending.
def is_safe_simpler(report):
    return is_safe_decreasing(report) or is_safe_increasing(report)

# Counts the number of safe reports in a 
# list based on the given safe-determining algo
def get_safe_count(reports, is_safe_algorithm):    
    safety = 0
    for report in reports:
        if is_safe_algorithm(report):
            safety += 1
            
    return safety

def solve_puzzle1(reports):
    return get_safe_count(reports, is_safe)

def solve_puzzle1_simpler(reports):
    return get_safe_count(reports, is_safe_simpler)

puzzle1_solver = solver.Solver("find direction first", 2, 1, read_reports, solve_puzzle1)
puzzle1_solver_simpler = solver.Solver("check both directions", 2, 1, read_reports, solve_puzzle1_simpler)

## Puzzle 2
# Checks whether a report is safe
# assuming up to one value may be
# removed. Since unsafety is a property
# of the change between two values,
# an unsafe reading could be rectified
# by removing either the number being
# jumped FROM or the number being jumped TO.
# This function explores both options
# using the is_safe_decreasing function
def is_safe_decreasing_dampened(report):
    for i in range(len(report) - 1):
        if report[i] <= report[i+1] or report[i] - 3 > report[i+1]:
            left_removed_report = report.copy()
            left_removed_report.pop(i)
            right_removed_report = report.copy()
            right_removed_report.pop(i+1)
            if is_safe_decreasing(left_removed_report) or is_safe_decreasing(right_removed_report):
                return True
            return False
        
    return True

# See is_safe_increasing
def is_safe_increasing_dampened(report):
    for i in range(len(report) - 1):
        if report[i] >= report[i+1] or report[i] + 3 < report[i+1]:
            left_removed_report = report.copy()
            left_removed_report.pop(i)
            right_removed_report = report.copy()
            right_removed_report.pop(i+1)
            if is_safe_increasing(left_removed_report) or is_safe_increasing(right_removed_report):
                return True
            return False
        
    return True

# Uses the get_safe_count function,
# where the safe-determining algo
# checks both increasing and
# decreasing scenarios.
def solve_puzzle2(reports):
    return get_safe_count(reports, lambda report: is_safe_decreasing_dampened(report) or is_safe_increasing_dampened(report))

puzzle2_solver = solver.Solver("checks both directions", 2, 2, read_reports, solve_puzzle2)