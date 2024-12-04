#include <fstream>
#include <string>
#include <vector>

#include "day1/puzzle2.cpp"
#include "day2/puzzle.cpp"

void timeDay2()
{
    day2::Puzzle1Solver d2p1 = day2::Puzzle1Solver();
    d2p1.reportTrial(5, 100);
    d2p1.reportTrial(5, 100, d2p1.parseFile());

    day2::Puzzle1SolverSimple d2p1Simple = day2::Puzzle1SolverSimple();
    d2p1Simple.reportTrial(5, 100);
    d2p1Simple.reportTrial(5, 100, d2p1Simple.parseFile());

    day2::Puzzle1SolverRecursive d2p1Recursive = day2::Puzzle1SolverRecursive();
    d2p1Recursive.reportTrial(5, 100);
    d2p1Recursive.reportTrial(5, 100, d2p1Recursive.parseFile());

    day2::Puzzle2SolverRecursive d2p2Recursive = day2::Puzzle2SolverRecursive();
    d2p2Recursive.reportTrial(5, 100);
    d2p2Recursive.reportTrial(5, 100, d2p2Recursive.parseFile());
}

int main(int argc, char *argv[])
{

    return 0;
}
