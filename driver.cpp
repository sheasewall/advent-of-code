#include <fstream>
#include <string>
#include <vector>

#include "day1/puzzle2.cpp"
#include "solver.cpp"

void timeDay1() 
{
    std::vector<int> puzzle_indices = {1, 2, 2};
    std::vector<int (*)(std::string file_name)> puzzle_solver_pointers = {puzzle1Solver, puzzle2Solver, puzzle2SortedSolver};
    std::vector<std::array<int, 2>> timing_info = {{{2, 20}}, {{2, 20}}, {{2, 20}}};
    Solver::timeDay(1, puzzle_indices, puzzle_solver_pointers, timing_info);
}

int main(int argc, char *argv[])
{
    timeDay1();
}
