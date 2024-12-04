#include <string>
#include <fstream>
#include <vector>
#include <sstream>

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

bool isSafeIncreasing2Comps(std::vector<unsigned int> report)
{
    for (int i = 0; i < report.size() - 1; i++) 
    {
        if (report[i] >= report[i+1])
        {
            return false;
        }
        if (report[i] + 3 < report[i+1])
        {
            return false;
        }
    }

    return true;
}

bool isSafeDecreasing2Comps(std::vector<unsigned int> report)
{
    for (int i = 0; i < report.size() - 1; i++) 
    {
        if (report[i] <= report[i+1])
        {
            return false;
        }
        if (report[i] > report[i+1] + 3)
        {
            return false;
        }
    }

    return true;
}

bool isSafe2Comps(std::vector<unsigned int> report) 
{
    unsigned int first_element = report[0];
    unsigned int second_element = report[1];

    if (first_element > second_element)
    {
        return isSafeDecreasing2Comps(report);
    }

    if (first_element < second_element)
    {
        return isSafeIncreasing2Comps(report);
    }

    return false;
}

bool isSafeIncreasing(std::vector<unsigned int> report) 
{
    for (int i = 0; i < report.size() - 1; i++) 
    {
        unsigned int diff = report[i+1] - report[i] - 1;
        if (diff >= 3) {
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
        unsigned int diff = (-(report[i+1] - report[i])) - 1;
        if (diff >= 3) {
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

namespace day2
{
    std::vector<std::vector<unsigned int>> parseFile(std::string file_name)
    {
        std::vector<std::vector<unsigned int>> reports;
        std::ifstream file(file_name);
        std::string buf;
        while (getline(file, buf, '\n'))
        {
            reports.push_back(parseReport(buf));
        }
        return reports;
    }

    int puzzle1Solver(std::string file_name)
    {
        std::vector<std::vector<unsigned int>> reports = parseFile(file_name);
        int safety_score = 0;
        for (int i = 0; i < reports.size(); i++) {
            if (isSafe(reports[i]))
            {
                safety_score++;
            }
        }
        return safety_score;
    }

    int puzzle1Solver2Comps(std::string file_name)
    {
        std::vector<std::vector<unsigned int>> reports = parseFile(file_name);
        int safety_score = 0;
        for (int i = 0; i < reports.size(); i++) {
            if (isSafe2Comps(reports[i]))
            {
                safety_score++;
            }
        }
        return safety_score;
    }
}