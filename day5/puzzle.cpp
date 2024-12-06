#include <sstream>
#include <regex>
#include <stack>

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

void markRule(int rule_table[100][100], Rule rule)
{
    rule_table[rule.second][rule.first] = 1;
}

void fillRuleTable(int rule_table[100][100], std::vector<Rule> rules)
{
    for (Rule rule : rules)
    {
        markRule(rule_table, rule);
    }
}

bool isValidUpdate(int rule_table[100][100], Update &update)
{
    for (int i = 0; i < update.pages.size(); i++)
    {
        for (int j = i + 1; j < update.pages.size(); j++)
        {
            if (rule_table[update.pages[i]][update.pages[j]])
            {
                return false;
            }
        }
    }

    return true;
}

int scoreUpdate(int rule_table[100][100], Update &update)
{
    if (!isValidUpdate(rule_table, update))
    {
        return 0;
    }
    return update.pages[update.pages.size() / 2];
}

int solveProblem(Manifest manifest, int (*scorer)(int rule_table[100][100], Update &update))
{
    int rule_table[100][100] = {0};
    fillRuleTable(rule_table, manifest.rules);

    int score = 0;
    for (Update update : manifest.updates)
    {
        score += scorer(rule_table, update);
    }
    return score;
}

int countUpdateIncomingRules(int rule_table[100][100], int node, Update &update)
{
    int sum = 0;
    for (int page : update.pages)
    {
        // We can assume rule_table[i][i] == 0
        sum += rule_table[node][page];
    }
    return sum;
}

int findCorrectedMiddleElement(int rule_table[100][100], Update &update)
{
    for (int page : update.pages)
    {
        if (countUpdateIncomingRules(rule_table, page, update) == update.pages.size() / 2)
        {
            return page;
        }
    }
    return -1;
}

int scoreIncorrectUpdate(int rule_table[100][100], Update &update)
{
    if (scoreUpdate(rule_table, update) > 0)
    {
        return 0;
    }
    return findCorrectedMiddleElement(rule_table, update);
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
        Puzzle1Solver() : Day5Solver("uses 100x100 rule table", 1) {}

        int computeSolution(Manifest manifest) override
        {
            return solveProblem(manifest, scoreUpdate);
        }
    };

    class Puzzle2Solver : public Day5Solver
    {
    public:
        Puzzle2Solver() : Day5Solver("calcs # of incoming rules", 2) {}

        int computeSolution(Manifest manifest) override
        {
            return solveProblem(manifest, scoreIncorrectUpdate);
        }
    };
}