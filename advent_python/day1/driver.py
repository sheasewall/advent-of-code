import timeit
import sys

from puzzle1 import puzzle1_solver
from puzzle2 import puzzle2_solver, puzzle2_memod_solver

def main(file_name):
    NUMBER_REPEATS = 5
    NUMBER_TRIALS = 10000
    TIME_ROUND = 2
    P1_SOLUTION = 1882714
    P2_SOLUTION = 19437052
    
    p1_time = min(timeit.repeat(lambda: puzzle1_solver(file_name), number=NUMBER_TRIALS, repeat=NUMBER_REPEATS))
    p1_solution = puzzle1_solver(file_name)

    p2_time = min(timeit.repeat(lambda: puzzle2_solver(file_name), number=NUMBER_TRIALS, repeat=NUMBER_REPEATS))
    p2_solution = puzzle2_solver(file_name)

    p2_time_memoized = min(timeit.repeat(lambda: puzzle2_memod_solver(file_name), number=NUMBER_TRIALS, repeat=NUMBER_REPEATS))
    p2_solution_memoized = puzzle2_memod_solver(file_name)

    if p1_solution == P1_SOLUTION:
        print("Puzzle 1:", round(p1_time / NUMBER_TRIALS * 1000000, TIME_ROUND), "microseconds")
    else:
        print("Puzzle 1: incorrect")
    if p2_solution == P2_SOLUTION:
        print("Puzzle 2:", round(p2_time / NUMBER_TRIALS * 1000000, TIME_ROUND), "microseconds")
    else:
        print("Puzzle 2: incorrect")
    if p2_solution_memoized == P2_SOLUTION:
        print("P2 memod:", round(p2_time_memoized / NUMBER_TRIALS * 1000000, TIME_ROUND), "microseconds")
    else:
        print("P2 memod: incorrect")

if __name__ == '__main__':
    main(sys.argv[1])