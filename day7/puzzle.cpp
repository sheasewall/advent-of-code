#include "../headers/solver.h"
#include "../headers/utils.h"

#include <math.h>
#include <memory.h>

namespace MyEnum
{
    enum Operation
    {
        Addition,
        Multiplication
    };

    static const Operation all_ops[] = {Addition, Multiplication};
}

using namespace MyEnum;

struct Equation
{
    long target;
    std::vector<long> values;

    Equation() : target(-1), values() {}

    long calculate(std::vector<Operation> operations);
    std::vector<std::vector<Operation>> generateOperations();
    bool canReachTarget();
};

long Equation::calculate(std::vector<Operation> operations)
{
    long sum = values[0];
    for (int i = 1; i < values.size(); i++)
    {
        Operation &relevant_op = operations[i - 1];
        switch (relevant_op)
        {
        case Operation::Addition:
            sum = sum + values[i];
            break;
        case Operation::Multiplication:
            sum = sum * values[i];
            break;
        }
    }
    return sum;
}

std::vector<std::vector<Operation>> Equation::generateOperations()
{
    std::shared_ptr<std::vector<std::vector<Operation>>> operations = std::make_shared<std::vector<std::vector<Operation>>>();
    utils::generatePermutations(operations, values.size() - 1, {Operation::Addition, Operation::Multiplication});
    return *operations;
}

bool Equation::canReachTarget()
{
    std::vector<std::vector<Operation>> operations = generateOperations();
    for (std::vector<Operation> ops : operations)
    {
        if (target == calculate(ops))
        {
            return true;
        }
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
            // int sum = std::count_if(equations.begin(), equations.end(), [](Equation equation)
            //                         { return equation.canReachTarget(); });
            long sum = 0;
            for (Equation equation : equations)
            {
                if (equation.canReachTarget())
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

        long computeSolution(std::vector<Equation> data) override
        {
            return int();
        }
    };
}