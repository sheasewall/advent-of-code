#include <fstream>
#include <string>
#include <vector>

#include "day1/puzzle2.cpp"
#include "day2/puzzle1.cpp"

// void timeDay1()
// {
//     std::vector<int> puzzle_indices = {1, 2, 2};
//     std::vector<int (*)(std::string file_name)> puzzle_solver_pointers = {day1::puzzle1Solver, day1::puzzle2Solver, puzzle2SortedSolver};
//     std::vector<std::array<int, 2>> timing_info = {{{2, 20}}, {{2, 20}}, {{2, 20}}};
//     Solver::timeDay(1, puzzle_indices, puzzle_solver_pointers, timing_info);
// }

// void timeDay2()
// {
//     std::vector<int> puzzle_indices = {1, 1};
//     std::vector<int (*)(std::string file_name)> puzzle_solver_pointers = {day2::puzzle1Solver, day2::puzzle1Solver2Comps};
//     std::vector<std::array<int, 2>> timing_info = {{{5, 1000}}, {5, 1000}};
//     Solver::timeDay(2, puzzle_indices, puzzle_solver_pointers, timing_info);
// }

void timeDay2()
{
    day2::Puzzle1Solver d2p1 = day2::Puzzle1Solver();
    d2p1.reportTrial(5, 100);
    d2p1.reportTrial(5, 100, d2p1.parseFile());

    day2::Puzzle1SolverSimple d2p1Simple = day2::Puzzle1SolverSimple();
    d2p1Simple.reportTrial(5, 100);
    d2p1Simple.reportTrial(5, 100, d2p1Simple.parseFile());
}

int main(int argc, char *argv[])
{
    timeDay2();
//     Solver<std::vector<std::vector<unsigned int>>, int> d2p1 =
//         Solver<std::vector<std::vector<unsigned int>>, int>(2, 1, day2::puzzle1Solver, day2::parseFile);
    // timeDay1();
    //  timeDay2();
    return 0;
}
