// #include "day1/puzzle2.cpp"
#include "../day2/puzzle.cpp"
#include "../day5/puzzle.cpp"
// #include "day5/puzzle.cpp"


void timeDay2()
{
    solve::TrialParameters parsing = {true, 5, 100};
    solve::TrialParameters non_parsing = {false, 10, 50};
    std::array<solve::TrialParameters, 2> params = {parsing, non_parsing};

    day2::Puzzle1Solver d2p1 = day2::Puzzle1Solver();
    d2p1.reportDefaultTrials(params);

    day2::Puzzle1SolverSimple d2p1Simple = day2::Puzzle1SolverSimple();
    d2p1Simple.reportDefaultTrials(params);

    day2::Puzzle1SolverRecursive d2p1Recursive = day2::Puzzle1SolverRecursive();
    d2p1Recursive.reportDefaultTrials(params);

    day2::Puzzle2SolverRecursive d2p2Recursive = day2::Puzzle2SolverRecursive();
    d2p2Recursive.reportDefaultTrials(params);

    // ALMOST WORKS
    day2::Puzzle2SolverRecursiveK d2p2RecursiveK = day2::Puzzle2SolverRecursiveK();
    d2p2RecursiveK.reportDefaultTrials(params);
}

int main(int argc, char *argv[])
{
    // timeDay2();
    // solve::TrialParameters parsing = {true, 1, 10};
    // solve::TrialParameters non_parsing = {false, 1, 5};
    // std::array<solve::TrialParameters, 2> params = {parsing, non_parsing};
    day5::Puzzle1Solver d5p1 = day5::Puzzle1Solver();
    d5p1.reportVerification("day5/test.txt", "day5/testsols.txt");
    return 0;
}
