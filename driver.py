from solver import test_solvers
from day2.puzzle import puzzle1_solver as d2p1, puzzle1_solver_simpler as d2p1_simpler, puzzle2_solver as d2p2
from day3.puzzle import puzzle1_solver as d3p1, puzzle2_solver as d3p2
           
def test_day_2():
    solvers = [d2p1, d2p1_simpler, d2p2]
    # testing_metadatas = [{"parsing":(5, 1), "no_parsing":(10, 10)}, {"parsing":(10,10), "no_parsing":(100,1)}]
    # test_solvers(solvers, input_file_name="day2/input1.txt", solution_file_name="day2/solutions1.txt")
    test_solvers(solvers)

def main():
    # test_day_2()
    d3p1.report_verification()
    d3p2.report_verification()

if __name__ == '__main__':
    main()