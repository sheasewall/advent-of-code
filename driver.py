from solver import test_solvers
from day2.puzzle import puzzle1_solver as d2p1, puzzle1_solver_simpler as d2p1_simpler, puzzle2_solver as d2p2
from day3.puzzle import puzzle1_solver as d3p1, puzzle2_solver as d3p2
from day4.puzzle import puzzle1_solver as d4p1   
        
def test_day_2():
    solvers = [d2p1, d2p1_simpler, d2p2]
    # testing_metadatas = [{"parsing":(5, 1), "no_parsing":(10, 10)}, {"parsing":(10,10), "no_parsing":(100,1)}]
    # test_solvers(solvers, input_file_name="day2/input1.txt", solution_file_name="day2/solutions1.txt")
    test_solvers(solvers)
    
def test_day_3():
    test_solvers([d3p1, d3p2])
    
def test_day_4():
    test_solvers([d4p1])

def main():
    d4p1.report_verification(input_file_name="day4/test.txt", solution_file_name="day4/testsols.txt")
    d4p1.report_verification()
    test_day_4()

if __name__ == '__main__':
    main()