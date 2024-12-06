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

// int countIncoming(int rule_table[100][100], int node, std::vector<int> &to_check)
// {
//     int incoming = 0;
//     for (int neighbor : to_check)
//     {
//         if (rule_table[node][neighbor])
//         {
//             incoming++;
//         }
//     }
//     return incoming;
// }

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

int exploreUpdate(int rule_table[100][100], Update &update)
{
    // stack whoever has no incoming arrows (because its a DAG, one exists)
    // after you remove someone, you have to see again who
    // has no incoming arrows, and stack them. etc.
    // at every step, someone has 0 incoming arrows and
    // they should be stacked.

    // There is a deterministic solution, so this is not general
    // topological sort. For one of the elements, there is a complete chain

    // int order[100] = {-1};
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
    return exploreUpdate(rule_table, update);
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

        int computeSolution(Manifest manifest) override
        {
            return solveProblem(manifest, scoreUpdate);
        }
    };

    class Puzzle2Solver : public Day5Solver
    {
    public:
        Puzzle2Solver() : Day5Solver("", 2) {}

        int computeSolution(Manifest manifest) override
        {
            return solveProblem(manifest, scoreIncorrectUpdate);
        }
    };
}

// 41,26,42,96,64,19,29 invalid?
// 68,33,82,65,23,48,67,17,87

// technically only indices 11-99 not including multiples of ten
// we could speed up parsing potentially, by just indexing
// into where the chars are.

// Rule A|B means A < B or A !> B.
// So, reading rule A|B means to
// mark T[B][A] = -1 to indicate
// that B < A is invalid. We don't
// have to worry about equality.

// So for series A, B, C, D,
// we are valid only if there is
// NOT a rule forbidding A < B,
// A < C, A < D, B < C, B < D,
// C < D. if there was a rule
// forbidding, say B < D, then
// that would mean the rule is
// D < B, which would mean that
// T[B][D] = -1. Thus we simply
// index into the array.

// A correct solution could be 4 disconnected
// nodes in any order. It could be 4 connected
// one after another and thats it.
// It could be 4 nodes connected in a square?

// A correct solution could be 2 disconnected nodes
// in one of two arrangements.
// It could be 2 nodes connected by one edge.
// It could not be 2 nodes connected to each
// other there are not bidirectional connections.
// It could be 3 disconnected in 6 ways
// It could be one connected, for each of which
// possibilities, there are two arrangements,
// so also 6 ways but some are the same order.
// It could be two edges, sequential or
// bifurcated, both are valid.