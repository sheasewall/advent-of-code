from solver import test_solvers
from day2.puzzle1 import puzzle1_solver as day2_puzzle1_solver, puzzle1_solver_simpler as day2_puzzle1_solver_simpler
           
def test_day_2():
    solvers = [day2_puzzle1_solver, day2_puzzle1_solver_simpler]
    testing_metadatas = [{"parsing":(5, 1), "no_parsing":(10, 10)}, {"parsing":(10,10), "no_parsing":(100,1)}]
    test_solvers(solvers, testing_metadatas)

def main():
    test_day_2()

if __name__ == '__main__':
    main()