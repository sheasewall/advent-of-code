#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include "../solver.cpp"

std::vector<unsigned int> parseReport(std::string line)
{
    std::vector<unsigned int> report;
    std::stringstream stream(line);
    std::string buf;
    while (getline(stream, buf, ' '))
    {
        report.push_back(stoul(buf));
    }
    return report;
}

bool isSafeIncreasingSimple(std::vector<unsigned int> report)
{
    for (int i = 0; i < report.size() - 1; i++)
    {
        if (report[i] >= report[i + 1])
        {
            return false;
        }
        if (report[i] + 3 < report[i + 1])
        {
            return false;
        }
    }

    return true;
}

bool isSafeDecreasingSimple(std::vector<unsigned int> report)
{
    for (int i = 0; i < report.size() - 1; i++)
    {
        if (report[i] <= report[i + 1])
        {
            return false;
        }
        if (report[i] > report[i + 1] + 3)
        {
            return false;
        }
    }

    return true;
}

bool isSafeSimple(std::vector<unsigned int> report)
{
    unsigned int first_element = report[0];
    unsigned int second_element = report[1];

    if (first_element > second_element)
    {
        return isSafeDecreasingSimple(report);
    }

    if (first_element < second_element)
    {
        return isSafeIncreasingSimple(report);
    }

    return false;
}

bool isSafeIncreasing(std::vector<unsigned int> report)
{
    for (int i = 0; i < report.size() - 1; i++)
    {
        unsigned int diff = report[i + 1] - report[i] - 1;
        if (diff >= 3)
        {
            return false;
        }
        // x 2 1 -> diff = -1  -1 = -2 x OVERFLOW TO HIGH
        // x 2 2 -> diff = 0   -1 = -1 x OVERFLOW TO HIGH
        // o 2 3 -> diff = 1   -1 =  0 o
        // o 2 4 -> diff = 2   -1 =  1 o
        // o 2 5 -> diff = 3   -1=   2 o
        // x 2 6 -> diff = 4   -1 =  3 x
    }

    return true;
}

bool isSafeDecreasing(std::vector<unsigned int> report)
{
    for (int i = 0; i < report.size() - 1; i++)
    {
        unsigned int diff = (-(report[i + 1] - report[i])) - 1;
        if (diff >= 3)
        {
            return false;
        }
        // x 6 7 -> diff = 1 neg -1   = -2 x OVERFLOW TO HIGH
        // x 6 6 -> diff = 0 neg  0   = -1 x OVERFLOW TO HIGH
        // o 6 5 -> diff =-1 neg  1   =  0 o
        // o 6 4 -> diff =-2 neg  2   =  1 o
        // o 6 3 -> diff =-3 neg  3   =  2 o
        // x 6 2 -> diff =-4 neg  4   =  3 x
    }

    return true;
}

bool isSafe(std::vector<unsigned int> report)
{
    unsigned int first_element = report[0];
    unsigned int second_element = report[1];

    if (first_element > second_element)
    {
        return isSafeDecreasing(report);
    }

    if (first_element < second_element)
    {
        return isSafeIncreasing(report);
    }

    return false;
}

bool isSafeDampened(std::vector<unsigned int> report) {

}

int countSafety(std::vector<std::vector<unsigned int>> reports, bool (*pSafetyDeterminer)(std::vector<unsigned int> report))
{
    int safety_score = 0;
    for (int i = 0; i < reports.size(); i++)
    {
        if (pSafetyDeterminer(reports[i]))
        {
            safety_score++;
        }
    }
    return safety_score;
}

namespace day2
{
    class Day2Solver : public Solver<std::vector<std::vector<unsigned int>>, int>
    {
    public:
        Day2Solver(int puzzle_index) : Solver(2, puzzle_index) {}

        std::vector<std::vector<unsigned int>> parseFile() override
        {
            std::vector<std::vector<unsigned int>> reports;
            std::ifstream file(getInputFileName());
            std::string buf;
            while (getline(file, buf, '\n'))
            {
                reports.push_back(parseReport(buf));
            }
            return reports;
        }

        int getCorrectSolution() override
        {
            std::ifstream file(getSolutionFileName());
            std::string str;
            int solutions[2];
            std::getline(file, str);
            solutions[0] = std::stoi(str);
            std::getline(file, str);
            solutions[1] = std::stoi(str);
            return solutions[puzzle_index - 1];
        }
    };

    class Puzzle1Solver : public Day2Solver
    {
    public:
        Puzzle1Solver() : Day2Solver(1) {}

        int computeSolution(std::vector<std::vector<unsigned int>> reports) override
        {
            return countSafety(reports, isSafe);
        }
    };

    class Puzzle1SolverSimple : public Day2Solver
    {
    public:
        Puzzle1SolverSimple() : Day2Solver(1) {}

        int computeSolution(std::vector<std::vector<unsigned int>> reports) override
        {
            return countSafety(reports, isSafeSimple);
        }
    };

    // class Puzzle2Solver : public Day2Solver
    // {
    //     public:
    //     Puzzle2Solver() : Day2Solver(2) {}

    //     int computeSolution(std::vector<std::vector<unsigned int>> reports) override 
    //     {
    //         return countSafety(reports, isSafeDampened)
    //     }
    // }
}