#include <sstream>
#include <regex>

#include "../headers/solver.h"
#include "../headers/utils.h"

struct Rule
{
    int first;
    int second;
};

struct Update
{
    std::vector<int> pages;
};

struct Manifest
{
    std::vector<Rule> rules;
    std::vector<Update> updates;
};

Rule parseRule(std::string &str)
{
    std::vector<std::string> results = utils::split(str, '|');
    return {stoi(results[0]), stoi(results[1])};
}

Update parseUpdate(std::string &str)
{
    std::vector<std::string> results = utils::split(str, ',');
    std::vector<int> updates;
    for (std::string u : results)
    {
        updates.push_back(stoi(u));
    }
    return {updates};
}

namespace day5
{
    class Day5Solver : public solve::Solver<Manifest, int>
    {
    public:
        Day5Solver(std::string name, int puzzle_index) : Solver(name, 5, puzzle_index) {}

        Manifest parseInputFile(std::string file_name) override
        {
            std::vector<Rule> rules;
            std::ifstream file(file_name);
            std::string buf;
            while (getline(file, buf, '\n') && buf != "")
            {
                rules.push_back(parseRule(buf));
            }
            std::vector<Update> updates;
            while (getline(file, buf, '\n'))
            {
                updates.push_back(parseUpdate(buf));
            }
            return {rules, updates};
        }
    };

    class Puzzle1Solver : public Day5Solver
    {
    public:
        Puzzle1Solver() : Day5Solver("printing", 1) {}

        int computeSolution(Manifest data) override
        {
            return 0;
        }
    };
}
