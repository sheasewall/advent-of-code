#include "../day2/puzzle.cpp"
#include "../day5/puzzle.cpp"
#include "../day6/puzzle.cpp"

std::array<solve::TrialParameters, 2> getDefaultParams()
{
    static const solve::TrialParameters parsing = {true, 5, 100};
    static const solve::TrialParameters non_parsing = {false, 5, 50};
    return {parsing, non_parsing};
}

std::array<solve::TrialParameters, 2> getQuickParams()
{
    static const solve::TrialParameters parsing = {true, 1, 10};
    static const solve::TrialParameters non_parsing = {false, 1, 5};
    return {parsing, non_parsing};
}

std::array<solve::TrialParameters, 2> getLongParams()
{
    static const solve::TrialParameters parsing = {true, 5, 5000};
    static const solve::TrialParameters non_parsing = {false, 10, 200};
    return {parsing, non_parsing};
}

void timeDay2()
{
    auto params = getDefaultParams();
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

void timeDay5()
{
    day5::Puzzle1Solver d5p1 = day5::Puzzle1Solver();
    d5p1.reportDefaultTrials(getLongParams());

    day5::Puzzle2Solver d5p2 = day5::Puzzle2Solver();
    d5p2.reportDefaultTrials(getLongParams());
}

int main(int argc, char *argv[])
{
    day6::Puzzle1Solver d6p1 = day6::Puzzle1Solver();
    // d6p1.reportVerification("day6/test.txt", "day6/test sols.txt");
    d6p1.reportDefaultTrials(getDefaultParams());

    day6::Puzzle2Solver d6p2 = day6::Puzzle2Solver();
    d6p2.reportVerification("day6/test.txt", "day6/test sols.txt");
    d6p2.reportDefaultVerification();
    return 0;
}
