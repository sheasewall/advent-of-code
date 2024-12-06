#include <sstream>
#include <regex>

#include "../headers/solver.h"

int solve_puzzle_1(std::string str)
{
    std::regex mults_regex("(mul\\([0-9]{1,3},[0-9]{1,3}\\))");
    

// get_mults_pattern = re.compile("")
// get_digits_pattern = re.compile("[0-9]{1,3}")
}

namespace day3
{
    class Day3Solver : Solver<std::string, int>
    {
    public:
        Day3Solver(std::string name, int puzzle_index) : Solver(name, 3, puzzle_index) {}

        std::string parseInputFile(std::string file_name) override
        {
            std::ifstream file;
            file.open(file_name);

            std::stringstream sstream;
            sstream << file.rdbuf();
            std::string str = sstream.str();
            return str;
        }
    };

    class Puzzle1Solver : Day3Solver
    {
    public:
        Puzzle1Solver() : Day3Solver("regex", 1) {}

        int computeSolution(std::string data) override
        {
            return 0;
        }
    };
}

