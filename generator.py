#!/usr/bin/env python3

import os
import argparse
from string import Template

def create_folder(path):
    """Create directory if it doesn't exist"""
    os.makedirs(path, exist_ok=True)

def create_file(path, content):
    """Create file with given content"""
    with open(path, 'w') as f:
        f.write(content)

def create_cpp(base_path, content):
    """Create C++ source file"""
    create_file(f"{base_path}.cpp", content)

def create_py(base_path, content):
    """Create Python source file"""
    create_file(f"{base_path}.py", content)

def create_txt(base_path, content):
    """Create text file"""
    create_file(f"{base_path}.txt", content)

def main():
    parser = argparse.ArgumentParser(description='Generate puzzle solution template files')
    parser.add_argument('day', type=str, help='Day number')
    parser.add_argument('input_type', type=str, help='Input type for C++ template')
    parser.add_argument('solution_type', type=str, help='Solution type for C++ template')
    parser.add_argument('test_sol', type=str, help='Test solution value')
    
    args = parser.parse_args()

    # Template definitions (same as in your original code)
    new_cpp = Template('''#include "../headers/solver.h"
#include "../headers/utils.h"

namespace day${day}
{
    class Day${day}Solver : public solve::Solver<${input_type}, ${solution_type}>
    {
    public:
        Day${day}Solver(std::string name, int puzzle_index) : Solver(name, ${day}, puzzle_index) {}

        ${input_type} parseInputFile(std::string file_name) override
        {
            return ${input_type}();
        }
    };

    class Puzzle1Solver : public Day${day}Solver
    {
    public:
        Puzzle1Solver() : Day${day}Solver("puzzle 1", 1) {}

        ${solution_type} computeSolution(${input_type} data) override
        {
            return ${solution_type}();
        }
    };

    class Puzzle2Solver : public Day${day}Solver
    {
    public:
        Puzzle2Solver() : Day${day}Solver("puzzle 2", 2) {}

        ${solution_type} computeSolution(${input_type} data) override
        {
            return ${solution_type}();
        }
    };
}''')

    new_py = Template('''import solver

## Puzzle 1
def read_input(file_name):
    # TODO: Implement input reader
    return

def solve_puzzle1(data):
    # TODO: Implement puzzle1 solver
    return

puzzle1_solver = solver.Solver("puzzle 1", ${day}, 1, read_input, solve_puzzle1)

## Puzzle 2
def solve_puzzle2(data):
    return

puzzle2_solver = solver.Solver("puzzle 2", ${day}, 2, read_input, solve_puzzle2)''')

    input_txt = ""
    solutions_txt = Template('''-1
-1
''')
    test_txt = ""
    test_sols_txt = Template('''${test_sol}
-1
''')

    # Create files
    day_folder = f"day{args.day}"
    create_folder(day_folder)
    
    cpp_data = {'day': args.day, 'input_type': args.input_type, 'solution_type': args.solution_type}
    py_data = {'day': args.day}
    test_sol_data = {'test_sol': args.test_sol}

    create_cpp(f"{day_folder}/puzzle", new_cpp.substitute(cpp_data))
    create_py(f"{day_folder}/puzzle", new_py.substitute(py_data))
    create_txt(f"{day_folder}/input", input_txt)
    create_txt(f"{day_folder}/solutions", solutions_txt.substitute())
    create_txt(f"{day_folder}/test", test_txt)
    create_txt(f"{day_folder}/test sols", test_sols_txt.substitute(test_sol_data))

if __name__ == '__main__':
    main()