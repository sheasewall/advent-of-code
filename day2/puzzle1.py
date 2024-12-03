import numpy as np

def read_reports(file_name):
    reports = []
    with open(file_name, 'r') as file:
        for line in file:
            report = [int(x) for x in line.split()]
            reports.append(report)
    
    return reports

def get_report_safety(report):
    first_el = report[0]
    second_el = report[1]
    
    #decreasing
    if first_el > second_el:
        for i in range(len(report) - 1):
            if report[i] <= report[i+1] or report[i] - 3 > report[i+1]:
                return False
        return True
        
    #increasing
    if first_el < second_el:
        for i in range(len(report) - 1):
            if report[i] >= report[i+1] or report[i] + 3 < report[i+1]:
                return False
        return True
        
    return False

def puzzle1_solver(file_name):
    reports = read_reports(file_name)
    
    safety = 0
    for report in reports:
        if get_report_safety(report):
            safety += 1
            
    return safety