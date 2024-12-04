#include <fstream>
#include <string>
#include <vector>

#include "day1/puzzle2.cpp"
#include "day2/puzzle1.cpp"

#include "solver.cpp"

void timeDay1() 
{
    std::vector<int> puzzle_indices = {1, 2, 2};
    std::vector<int (*)(std::string file_name)> puzzle_solver_pointers = {day1::puzzle1Solver, day1::puzzle2Solver, puzzle2SortedSolver};
    std::vector<std::array<int, 2>> timing_info = {{{2, 20}}, {{2, 20}}, {{2, 20}}};
    Solver::timeDay(1, puzzle_indices, puzzle_solver_pointers, timing_info);
}

void timeDay2() 
{
    std::vector<int> puzzle_indices = {1, 1};
    std::vector<int (*)(std::string file_name)> puzzle_solver_pointers = {day2::puzzle1Solver, day2::puzzle1Solver2Comps};
    std::vector<std::array<int, 2>> timing_info = {{{5, 1000}}, {5, 1000}};
    Solver::timeDay(2, puzzle_indices, puzzle_solver_pointers, timing_info);
}

int main(int argc, char *argv[])
{
    //timeDay1();
    timeDay2();
}
