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

bool isSafeSimple(std::vector<unsigned int> report)
{
    return (isSafeDecreasing(report) || isSafeIncreasing(report));
}

bool isSafeIncreasingRecursive(std::vector<unsigned int> report)
{
    if (report.size() <= 1)
    {
        return true;
    }
    if (report[0] >= report[1] || report[0] + 3 < report[1])
    {
        return false;
    }
    report.erase(report.begin());
    return isSafeIncreasingRecursive(report);
}

bool isSafeDecreasingRecursive(std::vector<unsigned int> report)
{
    if (report.size() <= 1)
    {
        return true;
    }
    if (report[0] <= report[1] || report[0] > report[1] + 3)
    {
        return false;
    }
    report.erase(report.begin());
    return isSafeDecreasingRecursive(report);
}

bool isSafeRecursive(std::vector<unsigned int> report)
{
    return (isSafeIncreasingRecursive(report) || isSafeDecreasingRecursive(report));
}

bool isSafeDampenedIncreasingRecursiveK(std::vector<unsigned int> report, int index, bool lowHP, bool justBeenHit)
{
    if (index == report.size() - 1)
    {
        return true;
    }
    if (report[index] >= report[index + 1] || report[index] + 3 < report[index + 1])
    {
        if (lowHP)
        {
            if (justBeenHit)
            {
                std::vector<unsigned int> copy = report;
                copy.erase(copy.begin() + index);
                return isSafeDampenedIncreasingRecursiveK(copy, index - 1, true, false);
            }
            return false;
        }

        return isSafeDampenedIncreasingRecursiveK(report, index + 1, true, true);
    }
    return isSafeDampenedIncreasingRecursiveK(report, index + 1, lowHP, false);
}

bool isSafeDampenedDecreasingRecursiveK(std::vector<unsigned int> report, int index, bool lowHP, bool justBeenHit)
{
    if (index == report.size() - 1)
    {
        return true;
    }
    if (report[index] <= report[index + 1] || report[index] > report[index + 1] + 3)
    {
        if (lowHP)
        {
            if (justBeenHit)
            {
                std::vector<unsigned int> copy = report;
                copy.erase(copy.begin() + index);
                return isSafeDampenedDecreasingRecursiveK(copy, index - 1, true, false);
            }
            return false;
        }

        return isSafeDampenedDecreasingRecursiveK(report, index + 1, true, true);
    }
    return isSafeDampenedDecreasingRecursiveK(report, index + 1, lowHP, false);
}

bool isSafeDampenedRecursiveK(std::vector<unsigned int> report)
{
    return (isSafeDampenedIncreasingRecursiveK(report, 0, false, false) || isSafeDampenedDecreasingRecursiveK(report, 0, false, false));
}

bool isSafeDampenedIncreasingRecursive(std::vector<unsigned int> report, int index, bool canTolerate)
{
    if (index == report.size() - 1)
    {
        return true;
    }
    if (report[index] >= report[index + 1] || report[index] + 3 < report[index + 1])
    {
        if (canTolerate)
        {
            std::vector<unsigned int> remove_left = report;
            std::vector<unsigned int> remove_right = report;
            remove_left.erase(remove_left.begin() + index);
            remove_right.erase(remove_right.begin() + index + 1);
            // index - 1 does NOT give correct answers
            return isSafeDampenedIncreasingRecursive(remove_left, 0, false) || isSafeDampenedIncreasingRecursive(remove_right, 0, false);
        }
        return false;
    }
    return isSafeDampenedIncreasingRecursive(report, index + 1, canTolerate);
}

bool isSafeDampenedDecreasingRecursive(std::vector<unsigned int> report, int index, bool canTolerate)
{
    if (index == report.size() - 1)
    {
        return true;
    }
    if (report[index] <= report[index + 1] || report[index] > report[index + 1] + 3)
    {
        if (canTolerate)
        {
            std::vector<unsigned int> remove_left = report;
            std::vector<unsigned int> remove_right = report;
            remove_left.erase(remove_left.begin() + index);
            remove_right.erase(remove_right.begin() + index + 1);
            return isSafeDampenedDecreasingRecursive(remove_left, 0, false) || isSafeDampenedDecreasingRecursive(remove_right, 0, false);
        }
        return false;
    }
    return isSafeDampenedDecreasingRecursive(report, index + 1, canTolerate);
}

bool isSafeDampenedRecursive(std::vector<unsigned int> report)
{
    return (isSafeDampenedDecreasingRecursive(report, 0, true) || isSafeDampenedIncreasingRecursive(report, 0, true));
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

void compareSafetyFunctions()
{
    std::vector<std::vector<unsigned int>> reports;
    std::ifstream file("day2/input.txt");
    std::string buf;
    while (getline(file, buf, '\n'))
    {
        reports.push_back(parseReport(buf));
    }
            
    for (size_t i = 0; i < reports.size(); ++i)
    {
        bool resultDampened = isSafeDampenedRecursive(reports[i]);
        bool resultDampenedK = isSafeDampenedRecursiveK(reports[i]);

        if (resultDampened != resultDampenedK)
        {
            std::cout << "Disagreement on test case " << i << ":\n";
            std::cout << "Report: ";
            for (unsigned int value : reports[i])
            {
                std::cout << value << " ";
            }
            std::cout << "\nisSafeDampened: " << resultDampened << "\n";
            std::cout << "isSafeDampenedK: " << resultDampenedK << "\n\n";
        }
    }
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

    class Puzzle1SolverRecursive : public Day2Solver
    {
    public:
        Puzzle1SolverRecursive() : Day2Solver(1) {}

        int computeSolution(std::vector<std::vector<unsigned int>> reports) override
        {
            return countSafety(reports, isSafeRecursive);
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

    class Puzzle2SolverRecursive : public Day2Solver
    {
    public:
        Puzzle2SolverRecursive() : Day2Solver(2) {}

        int computeSolution(std::vector<std::vector<unsigned int>> reports) override
        {
            return countSafety(reports, isSafeDampenedRecursive);
        }
    };

    class Puzzle2SolverRecursiveK : public Day2Solver
    {
    public:
        Puzzle2SolverRecursiveK() : Day2Solver(2) {}

        int computeSolution(std::vector<std::vector<unsigned int>> reports) override
        {
            return countSafety(reports, isSafeDampenedRecursiveK);
        }
    };
}