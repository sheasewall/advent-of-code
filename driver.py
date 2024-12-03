import timeit
import sys

from day1.puzzle1 import puzzle1_solver as day1_puzzle1_solver
from day1.puzzle2 import puzzle2_solver as day1_puzzle2_solver
from day1.puzzle2 import puzzle2_memod_solver as day1_puzzle2_memod_solver
from day2.puzzle1 import puzzle1_solver as day2_puzzle1_solver

# Returns the average time for a solver to give an answer
# over the best cumulative batch. Does not verify answer.
def time_solver(solver, file_name, num_batches, num_reps):
    # For each batch, we time how long it cumulatively takes
    # to run the calculation $num_reps number of times.
    # We then take the best batch time.
    time = min(timeit.repeat(lambda: solver(file_name), number=num_reps, repeat=num_batches))
    # We divide the best batch time to get the average time
    # per single calculation and convert it to microseconds
    return round(time / num_reps * 1000000)

def verify_solver(solver, day_index, puzzle_index):
    return compute_solution(solver, day_index) == get_correct_solution(day_index, puzzle_index)

def compute_solution(solver, day_index):
    return solver(f"day{day_index}/input.txt")

# Gets the solution for a given day and puzzle assuming
# that days and puzzles are valid integers started at 1. 
def get_correct_solution(day_index, puzzle_index):
    solution_file = open(f"day{day_index}/solutions.txt", 'r')
    lines = solution_file.readlines()
    return int(lines[puzzle_index - 1])

# Times and verifies a set of solvers over a given day.
# Use puzzle_indices to indicate which solver corresponds
# to which puzzle within the day. Use timing_info to 
# indicate how many reps and batches for each solver.
def time_day(solvers, puzzle_indices, day_index, timing_info):
    for solver_idx, solver in enumerate(solvers):
        file_name = f"day{day_index}/input.txt"
        num_batches, num_reps = timing_info[solver_idx]
        best_avg = time_solver(solver, file_name, num_batches, num_reps)
        
        solution = get_correct_solution(day_index, puzzle_indices[solver_idx])
        is_correct = compute_solution(solver, day_index) == solution
        print("Solver", solver_idx, "computed a", is_correct, 
              "answer in", best_avg, "microseconds")

def time_day_1():
    time_day([day1_puzzle1_solver, day1_puzzle2_solver, day1_puzzle2_memod_solver], 
             [1, 2, 2], 1, [(5, 10), (10, 20), (10, 20)] )

def main():
    print(verify_solver(day2_puzzle1_solver, 2, 1))
    
if __name__ == '__main__':
    main()