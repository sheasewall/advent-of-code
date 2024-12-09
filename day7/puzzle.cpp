#include "../headers/solver.h"
#include "../headers/utils.h"

#include <math.h>
#include <memory.h>

namespace MyEnum
{
    enum Operation
    {
        Addition,
        Multiplication,
        Concatenation
    };

    static const Operation all_ops[] = {Addition, Multiplication, Concatenation};
}

using namespace MyEnum;

struct Equation
{
    long target;
    std::vector<long> values;

    Equation() : target(-1), values() {}

    long calculate(std::shared_ptr<std::vector<Operation>> ops);
    bool canReachTarget(std::shared_ptr<std::vector<std::shared_ptr<std::vector<Operation>>>> operations);
};

long Equation::calculate(std::shared_ptr<std::vector<Operation>> operations)
{
    if (operations->size() != values.size() - 1)
    {
        std::throw_with_nested(std::invalid_argument("Invalid number of operations for this equation."));
    }
    long lhs = values[0];
    for (int i = 1; i < values.size(); i++)
    {
        const Operation &relevant_op = (*operations)[i - 1];
        switch (relevant_op)
        {
        case Operation::Addition:
            lhs = lhs + values[i];
            break;
        case Operation::Multiplication:
            lhs = lhs * values[i];
            break;
        case Operation::Concatenation:
            lhs = stol(std::to_string(lhs) + std::to_string(values[i]));
            break;
        }
    }
    return lhs;
}

bool Equation::canReachTarget(std::shared_ptr<std::vector<std::shared_ptr<std::vector<Operation>>>> operations)
{
    for (const auto &ops : *operations)
    {
        // Skip operation sequences that don't match our equation length
        if ((ops->size() == values.size() - 1) && (target == calculate(ops)))
        {
            return true;
        }
    }
    return false;
}

int max_depth(std::vector<Equation> equations)
{

    int max_depth = std::max_element(equations.begin(), equations.end(),
                                     [](const Equation &a, const Equation &b)
                                     {
                                         return a.values.size() < b.values.size();
                                     })
                        ->values.size();
    return max_depth - 1;
}

long sumReachableTargets(std::vector<Equation> equations, std::shared_ptr<std::vector<std::shared_ptr<std::vector<Operation>>>> operations)
{
    long sum = 0;
    for (Equation equation : equations)
    {
        if (equation.canReachTarget(operations))
        {
            sum += equation.target;
        }
    }
    return sum;
}

// No pointers
struct EquationNp
{
    long target;
    std::vector<long> values;

    EquationNp() : target(-1), values() {}

    long calculate(const std::vector<Operation> &ops) const;
    bool canReachTarget(const std::vector<std::vector<Operation>> &operations) const;
};

long EquationNp::calculate(const std::vector<Operation> &operations) const
{
    if (operations.size() != values.size() - 1)
    {
        throw std::invalid_argument("Invalid number of operations for this equation.");
    }
    long lhs = values[0];
    for (size_t i = 1; i < values.size(); i++)
    {
        const Operation &relevant_op = operations[i - 1];
        switch (relevant_op)
        {
        case Operation::Addition:
            lhs = lhs + values[i];
            break;
        case Operation::Multiplication:
            lhs = lhs * values[i];
            break;
        case Operation::Concatenation:
            lhs = stol(std::to_string(lhs) + std::to_string(values[i]));
            break;
        }
    }
    return lhs;
}

bool EquationNp::canReachTarget(const std::vector<std::vector<Operation>> &operations) const
{
    for (const auto &ops : operations)
    {
        if (ops.size() == values.size() - 1 && target == calculate(ops))
        {
            return true;
        }
    }
    return false;
}

long sumReachableTargets(const std::vector<EquationNp> &equations,
                         const std::vector<std::vector<Operation>> &operations)
{
    long sum = 0;
    for (const EquationNp &equation : equations)
    {
        if (equation.canReachTarget(operations))
        {
            sum += equation.target;
        }
    }
    return sum;
}

int max_depth(std::vector<EquationNp> equations)
{

    int max_depth = std::max_element(equations.begin(), equations.end(),
                                     [](const EquationNp &a, const EquationNp &b)
                                     {
                                         return a.values.size() < b.values.size();
                                     })
                        ->values.size();
    return max_depth - 1;
}

namespace day7
{
    class Day7Solver : public solve::Solver<std::vector<Equation>, long>
    {
    public:
        Day7Solver(std::string name, int puzzle_index) : Solver(name, 7, puzzle_index) {}

        std::vector<Equation> parseInputFile(std::string file_name) override
        {
            std::ifstream file(file_name);
            std::string line;

            std::vector<Equation> equations;
            while (std::getline(file, line))
            {
                Equation equation;
                std::vector<std::string> splits = utils::split(line, ':');
                equation.target = stol(splits[0]);
                splits = utils::split(splits[1], ' ');
                for (std::string value : splits)
                {
                    if (value != "")
                    {
                        equation.values.push_back(stol(value));
                    }
                }
                equations.push_back(equation);
            }
            return equations;
        }
    };

    class Puzzle1Solver : public Day7Solver
    {
    public:
        Puzzle1Solver() : Day7Solver("puzzle 1 shared ptr", 1) {}

        long computeSolution(std::vector<Equation> equations) override
        {
            std::shared_ptr<std::vector<std::shared_ptr<std::vector<Operation>>>> ops = std::make_shared<std::vector<std::shared_ptr<std::vector<Operation>>>>();
            utils::generatePermutations(ops, max_depth(equations), {Operation::Addition, Operation::Multiplication});

            return sumReachableTargets(equations, ops);
        }
    };

    class Puzzle2Solver : public Day7Solver
    {
    public:
        Puzzle2Solver() : Day7Solver("puzzle 2 shared ptr", 2) {}

        long computeSolution(std::vector<Equation> equations) override
        {
            std::shared_ptr<std::vector<std::shared_ptr<std::vector<Operation>>>> ops = std::make_shared<std::vector<std::shared_ptr<std::vector<Operation>>>>();
            utils::generatePermutations(ops, max_depth(equations), {Operation::Addition, Operation::Multiplication, Operation::Concatenation});

            return sumReachableTargets(equations, ops);
        }
    };

    // No pointers
    class Day7SolverNp : public solve::Solver<const std::vector<EquationNp>, long>
    {
    public:
        Day7SolverNp(std::string name, int puzzle_index) : Solver(name, 7, puzzle_index) {}

        const std::vector<EquationNp> parseInputFile(std::string file_name) override
        {
            std::ifstream file(file_name);
            std::string line;

            std::vector<EquationNp> equations;
            while (std::getline(file, line))
            {
                EquationNp equation;
                std::vector<std::string> splits = utils::split(line, ':');
                equation.target = stol(splits[0]);
                splits = utils::split(splits[1], ' ');
                for (std::string value : splits)
                {
                    if (value != "")
                    {
                        equation.values.push_back(stol(value));
                    }
                }
                equations.push_back(equation);
            }
            return equations;
        }
    };

    class Puzzle1SolverNp : public Day7SolverNp
    {
    public:
        Puzzle1SolverNp() : Day7SolverNp("puzzle 1 no pointers", 1) {}

        long computeSolution(const std::vector<EquationNp> equations) override
        {
            std::vector<std::vector<Operation>> ops;
            utils::generatePermutations(ops, max_depth(equations), {Operation::Addition, Operation::Multiplication});
            return sumReachableTargets(equations, ops);
        }
    };

    class Puzzle2SolverNp : public Day7SolverNp
    {
    public:
        Puzzle2SolverNp() : Day7SolverNp("puzzle 2 no pointers", 2) {}

        long computeSolution(const std::vector<EquationNp> equations) override
        {
            std::vector<std::vector<Operation>> ops;
            utils::generatePermutations(ops, max_depth(equations), {Operation::Addition, Operation::Multiplication, Operation::Concatenation});
            return sumReachableTargets(equations, ops);
        }
    };
}