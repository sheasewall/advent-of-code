import numpy as np

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

def get_safe_count(file_name, is_safe_algorithm):
    reports = read_reports(file_name)
    
    safety = 0
    for report in reports:
        if is_safe_algorithm(report):
            safety += 1
            
    return safety

def puzzle1_solver(file_name):
    return get_safe_count(file_name, is_safe)

def puzzle1_solver_simpler(file_name):
    return get_safe_count(file_name, is_safe_simpler)
