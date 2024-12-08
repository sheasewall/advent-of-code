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

    long calculate(std::vector<Operation> operations);
    std::vector<std::vector<Operation>> generateAddMulOps();
    std::vector<std::vector<Operation>> generateAddMulConOps();
    bool canReachTarget(std::vector<std::vector<Operation>> operations);
};

long Equation::calculate(std::vector<Operation> operations)
{
    if (operations.size() != values.size() - 1)
    {
        std::throw_with_nested(std::invalid_argument("Invalid number of operations for this equation."));
    }
    long lhs = values[0];
    for (int i = 1; i < values.size(); i++)
    {
        Operation &relevant_op = operations[i - 1];
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

std::vector<std::vector<Operation>> Equation::generateAddMulOps()
{
    std::shared_ptr<std::vector<std::vector<Operation>>> operations = std::make_shared<std::vector<std::vector<Operation>>>();
    utils::generatePermutations(operations, values.size() - 1, {Operation::Addition, Operation::Multiplication});
    return *operations;
}

std::vector<std::vector<Operation>> Equation::generateAddMulConOps()
{
    std::shared_ptr<std::vector<std::vector<Operation>>> operations = std::make_shared<std::vector<std::vector<Operation>>>();
    utils::generatePermutations(operations, values.size() - 1, {Operation::Addition, Operation::Multiplication, Operation::Concatenation});
    return *operations;
}

bool Equation::canReachTarget(std::vector<std::vector<Operation>> operations)
{
    while (operations.back().size() == values.size() - 1)
    {
        std::vector<Operation> ops = operations.back();
        if (target == calculate(ops))
        {
            return true;
        }
        operations.pop_back();
    }
    return false;
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
        Puzzle1Solver() : Day7Solver("puzzle 1", 1) {}

        long computeSolution(std::vector<Equation> equations) override
        {
            int max_size = 0;
            for (Equation equation : equations)
            {
                if (equation.values.size() - 1 > max_size)
                {
                    max_size = equation.values.size() - 1;
                }
            }

            std::shared_ptr<std::vector<std::vector<Operation>>> operations = std::make_shared<std::vector<std::vector<Operation>>>();
            utils::generatePermutations(operations, max_size, {Operation::Addition, Operation::Multiplication});

            long sum = 0;
            for (Equation equation : equations)
            {
                if (equation.canReachTarget(equation.generateAddMulOps()))
                {
                    sum += equation.target;
                }
            }
            return sum;
        }
    };

    class Puzzle2Solver : public Day7Solver
    {
    public:
        Puzzle2Solver() : Day7Solver("puzzle 2", 2) {}

        long computeSolution(std::vector<Equation> equations) override
        {
            long sum = 0;
            for (Equation equation : equations)
            {
                if (equation.canReachTarget(equation.generateAddMulConOps()))
                {
                    sum += equation.target;
                }
            }
            return sum;
        }
    };
}