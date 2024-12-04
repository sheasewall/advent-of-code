from day2.puzzle1 import is_safe_decreasing, is_safe_increasing, get_safe_count

def is_safe_decreasing_dampened(report):
    for i in range(len(report) - 1):
        if report[i] <= report[i+1] or report[i] - 3 > report[i+1]:
            center_removed_report = report.copy()
            center_removed_report.pop(i)
            right_removed_report = report.copy()
            right_removed_report.pop(i+1)
            if is_safe_decreasing(center_removed_report) or is_safe_decreasing(right_removed_report):
                return True
            return False
        
    return True

def is_safe_increasing_dampened(report):
    for i in range(len(report) - 1):
        if report[i] >= report[i+1] or report[i] + 3 < report[i+1]:
            center_removed_report = report.copy()
            center_removed_report.pop(i)
            right_removed_report = report.copy()
            right_removed_report.pop(i+1)
            if is_safe_increasing(center_removed_report) or is_safe_increasing(right_removed_report):
                return True
            return False
        
    return True
        
def is_safe_dampened(report):
    return is_safe_decreasing_dampened(report) or is_safe_increasing_dampened(report)

def puzzle2_solver(file_name):
    return get_safe_count(file_name, is_safe_dampened)