import solver

def read_reports(file_name):
    reports = []
    with open(file_name, 'r') as file:
        for line in file:
            report = [int(x) for x in line.split()]
            reports.append(report)
    
    return reports

def is_safe_decreasing(report):
    for i in range(len(report) - 1):
        if report[i] <= report[i+1] or report[i] - 3 > report[i+1]:
            return False
        
    return True

def is_safe_increasing(report):
    for i in range(len(report) - 1):
        if report[i] >= report[i+1] or report[i] + 3 < report[i+1]:
            return False
        
    return True

def is_safe_simpler(report):
    return is_safe_decreasing(report) or is_safe_increasing(report)

def is_safe(report):
    first_el = report[0]
    second_el = report[1]
    
    #decreasing
    if first_el > second_el:
        return is_safe_decreasing(report)
        
    #increasing
    if first_el < second_el:
        return is_safe_increasing(report)
    
    return False

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