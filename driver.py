from solver import test_solvers
from day2.puzzle import puzzle1_solver as d2p1, puzzle1_solver_simpler as d2p1_simpler, puzzle2_solver as d2p2
from day3.puzzle import puzzle1_solver as d3p1, puzzle2_solver as d3p2
from day4.puzzle import puzzle1_solver as d4p1, puzzle1_solver_fast_parse as d4p1f, puzzle2_solver_fast_parse as d4p2, puzzle2_solver_new_line as d4p2nl, puzzle2_solver_kura as d4p2k
        
def test_day_2():
    solvers = [d2p1, d2p1_simpler, d2p2]
    # testing_metadatas = [{"parsing":(5, 1), "no_parsing":(10, 10)}, {"parsing":(10,10), "no_parsing":(100,1)}]
    # test_solvers(solvers, input_file_name="day2/input1.txt", solution_file_name="day2/solutions1.txt")
    test_solvers(solvers)
    
def test_day_3():
    test_solvers([d3p1, d3p2])
    
def test_day_4():
    test_solvers([d4p1, d4p1f, d4p2, d4p2nl, d4p2k])

def main():
    test_day_4()

if __name__ == '__main__':
    main()