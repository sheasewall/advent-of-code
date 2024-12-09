#include "../day2/puzzle.cpp"
#include "../day5/puzzle.cpp"
#include "../day6/puzzle.cpp"
#include "../day7/puzzle.cpp"
#include "../day8/puzzle.cpp"

#include "matrix.cpp"
#include <cassert>

std::array<solve::TrialParameters, 2> getWickedFastParams()
{
    static const solve::TrialParameters parsing = {true, 2, 10};
    static const solve::TrialParameters non_parsing = {false, 2, 5};
    return {parsing, non_parsing};
}

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

void timeDay6()
{
    day6::Puzzle1Solver d6p1 = day6::Puzzle1Solver();
    d6p1.reportDefaultTrials(getLongParams());

    day6::Puzzle2Solver d6p2 = day6::Puzzle2Solver();
    d6p2.reportDefaultTrials(getDefaultParams());
}

void timeDay7()
{
    day7::Puzzle1Solver d7p1 = day7::Puzzle1Solver();
    d7p1.reportDefaultTrials(getWickedFastParams());

    day7::Puzzle1SolverNp d7p1Np = day7::Puzzle1SolverNp();
    d7p1Np.reportDefaultTrials(getWickedFastParams());

    day7::Puzzle2Solver d7p2 = day7::Puzzle2Solver();
    d7p2.reportDefaultTrials(getWickedFastParams());

    day7::Puzzle2SolverNp d7p2Np = day7::Puzzle2SolverNp();
    d7p2Np.reportDefaultTrials(getWickedFastParams());
}

// void testTileEntity()
// {
//     vec::TileEntity<char, int, 1> tile = vec::TileEntity<char, int, 1>({0}, 'c');
//     vec::operator<<(std::cout, tile);

//     vec::TileEntity<std::string, long, 1> tile2 = vec::TileEntity<std::string, long, 1>({1000}, "jo");
//     vec::operator<<(std::cout, tile2);

//     vec::TileEntity<std::string, long, 2> tile3 = vec::TileEntity<std::string, long, 2>({-10, 10}, "jo");
//     vec::operator<<(std::cout, tile3);
// }

void testMultiDimVectors()
{
    // 1D vector tests
    spaces::Matrix<int, 1, size_t> vec1d;
    vec1d.add(1);
    vec1d.add(2);
    vec1d.add(3);

    assert(vec1d.getElement({0}) == 1);
    assert(vec1d.getElement({1}) == 2);
    assert(vec1d.size() == 3);

    // 2D vector tests
    spaces::Matrix<int, 2, size_t> vec2d;
    spaces::Matrix<int, 1, size_t> row1;
    row1.add(1);
    row1.add(2);

    spaces::Matrix<int, 1, size_t> row2;
    row2.add(3);
    row2.add(4);

    vec2d.add(row1);
    vec2d.add(row2);

    assert(vec2d.getElement({0, 0}) == 1);
    assert(vec2d.getElement({1, 1}) == 4);
    assert(vec2d.size() == 2);

    // 3D vector tests
    spaces::Matrix<int, 3, size_t> vec3d;
    spaces::Matrix<int, 2, size_t> plane1;
    plane1.add(row1);
    plane1.add(row2);
    vec3d.add(plane1);

    assert(vec3d.getElement({0, 0, 0}) == 1);
    assert(vec3d.getElement({1, 1, 0}) == 4);

    // fill constructor tests
   // spaces::MultiDimVector<char, 1, size_t> fill_vec1d = vec::MultiDimVector<char, 1, size_t>('k', 5);

    // Error handling tests
    try
    {
        // vec1d.getElement({999}); // Should throw
        // assert(false);  // Should not reach here
    }
    catch (const std::nested_exception &e)
    {
        std::cout << "Successfully caught out of range error\n";
    }

    try
    {
        // vec1d.getElement({-1}); // Should throw
        // assert(false);  // Should not reach here
    }
    catch (const std::nested_exception &e)
    {
        std::cout << "Successfully caught negative index error\n";
    }

    std::cout << "All Matrix tests passed!\n";
}

void testMDV()
{
    spaces::Matrix<char, 1, int> x1a = spaces::Matrix<char, 1, int>();
    spaces::Matrix<char, 1, int> x1b = spaces::Matrix<char, 1, int>();
    x1a.add('a');
    x1a.add('b');
    x1a.add('c');
    x1a.add('e');
    x1b.add('f');
    x1b.add('g');
    x1b.add('h');
    x1b.add('i');
    spaces::Matrix<char, 2, int> x2a = spaces::Matrix<char, 2, int>();
    x2a.add(x1a);
    x2a.add(x1b);

    spaces::Matrix<char, 1, int> x1c = spaces::Matrix<char, 1, int>();
    spaces::Matrix<char, 1, int> x1d = spaces::Matrix<char, 1, int>();
    x1c.add('j');
    x1c.add('k');
    x1c.add('l');
    x1c.add('m');
    x1d.add('n');
    x1d.add('o');
    x1d.add('p');
    x1d.add('q');
    spaces::Matrix<char, 2, int> x2b = spaces::Matrix<char, 2, int>();
    x2b.add(x1c);
    x2b.add(x1d);

    spaces::Matrix<char, 1, int> x1e = spaces::Matrix<char, 1, int>();
    spaces::Matrix<char, 1, int> x1f = spaces::Matrix<char, 1, int>();
    x1e.add('r');
    x1e.add('s');
    x1e.add('t');
    x1e.add('u');
    x1f.add('v');
    x1f.add('w');
    x1f.add('x');
    x1f.add('y');
    spaces::Matrix<char, 2, int> x2c = spaces::Matrix<char, 2, int>();
    x2c.add(x1e);
    x2c.add(x1f);

    spaces::Matrix<char, 3, int> x3a = spaces::Matrix<char, 3, int>();
    x3a.add(x2a);
    x3a.add(x2b);
    x3a.add(x2c);

    auto &x3av = x3a.getVector();

    auto ex1 = x1a.getElement({0});

    auto ex2 = x2a.getElement({0, 1});

    auto ex3 = x3a.getElement({0, 1, 1});
    return;
}

int main(int argc, char *argv[])
{
    testMultiDimVectors();
    // testMDV();
    // timeDay7();
    return 0;
}
