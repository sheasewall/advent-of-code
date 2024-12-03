from puzzle1 import get_report_safety, read_reports

def get_report_safety_dampened(report):
    first_el = report[0]
    second_el = report[1]
    
    #decreasing
    if first_el > second_el:
        for i in range(len(report) - 1):
            if report[i] <= report[i+1] or report[i] - 3 > report[i+1]:
                center_removed_report = report.copy().remove(i)
                right_removed_report = report.copy().remove(i+1)
                if get_report_safety(center_removed_report) or get_report_safety(right_removed_report):
                    return True
        return True
        
    #increasing
    if first_el < second_el:
        for i in range(len(report) - 1):
            if report[i] >= report[i+1] or report[i] + 3 < report[i+1]:
                center_removed_report = report.copy().remove(i)
                right_removed_report = report.copy().remove(i+1)
                if get_report_safety(center_removed_report) or get_report_safety(right_removed_report):
                    return True
        return True
        
    return False

def puzzle2_solver(file_name):
    return 0