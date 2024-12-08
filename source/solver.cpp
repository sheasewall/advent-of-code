#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <iostream>

#include "../headers/solver.h"

using namespace solve;

// // Specialization for int type
// template <typename S>
// std::vector<int> defaultParseSolutionFile(std::string file_name)
// {
//     std::ifstream file(file_name);
//     std::string str;
//     std::vector<int> solutions;
//     std::getline(file, str);
//     solutions.push_back(std::stoi(str));
//     std::getline(file, str);
//     solutions.push_back(std::stoi(str));
//     return solutions;
// }

// template <typename S>
// std::vector<long> defaultParseSolutionFile(std::string file_name)
// {
//     std::ifstream file(file_name);
//     std::string str;
//     std::vector<long> solutions;
//     std::getline(file, str);
//     solutions.push_back(std::stol(str));
//     std::getline(file, str);
//     solutions.push_back(std::stol(str));
//     return solutions;
// }

// template <typename T, typename S>
// std::vector<S> Solver<T, S>::parseSolutionFile(std::string file_name)
// {
//     return defaultParseSolutionFile<S>(file_name);
// }



template <typename T, typename S>
S Solver<T, S>::getCorrectSolution(std::string file_name)
{
    return SolutionFileParser<S>::parseSolutionFile(file_name)[puzzle_index - 1];
}

template <typename T, typename S>
Solver<T, S>::Solver(std::string name, int day_index, int puzzle_index)
{
    this->name = name;
    this->day_index = day_index;
    this->puzzle_index = puzzle_index;
}

template <typename T, typename S>
std::string Solver<T, S>::getInputFileName()
{
    std::string input_file_name = "day";
    input_file_name += std::to_string(day_index);
    input_file_name += "/input.txt";
    return input_file_name;
}

template <typename T, typename S>
std::string Solver<T, S>::getSolutionFileName()
{
    std::string solution_file_name = "day";
    solution_file_name += std::to_string(day_index);
    solution_file_name += "/solutions.txt";
    return solution_file_name;
}

template <typename T, typename S>
std::string Solver<T, S>::getName()
{
    std::string shorthand_name = "D";
    shorthand_name += std::to_string(day_index);
    shorthand_name += "P";
    shorthand_name += std::to_string(puzzle_index);
    shorthand_name += " \"";
    shorthand_name += name;
    shorthand_name += "\"";
    return shorthand_name;
}

template <typename T, typename S>
VerificationResults<S> Solver<T, S>::verify(std::string input_file_name, std::string solution_file_name)
{
    T data = parseInputFile(input_file_name);
    S computed_solution = computeSolution(data);
    S correct_solution = getCorrectSolution(solution_file_name);

    return VerificationResults<S>(computed_solution, correct_solution);
}

template <typename T, typename S>
TrialResults<S> Solver<T, S>::trial(std::string input_file_name, std::string solution_file_name, TrialParameters params)
{
    T data = parseInputFile(input_file_name);
    std::vector<long> exec_times;
    for (int i = 0; i < params.num_batches; i++)
    {
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < params.num_reps; j++)
        {
            if (params.must_parse)
            {
                computeSolution(parseInputFile(input_file_name));
            }
            else
            {
                computeSolution(data);
            }
        }
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        exec_times.push_back(duration.count());
    }
    long best_avg = *std::min_element(exec_times.begin(), exec_times.end()) / params.num_reps;
    VerificationResults<S> verification = verify(input_file_name, solution_file_name);
    return {best_avg, verification};
}

template <typename T, typename S>
void Solver<T, S>::reportVerification(std::string input_file_name, std::string solution_file_name)
{
    VerificationResults<S> results = verify(input_file_name, solution_file_name);
    if (results.is_correct)
    {
        std::cout << "✓✓✓ " << getName() << " got correct solution: "
                  << results.computed_solution << std::endl;
        return;
    }

    std::cout << "xxx " << getName() << " got incorrect solution: "
              << results.computed_solution << ". Correct solution is: "
              << results.correct_solution << std::endl;
}

template <typename T, typename S>
void Solver<T, S>::reportTrial(std::string input_file_name, std::string solution_file_name, TrialParameters params)
{
    TrialResults<S> results = trial(input_file_name, solution_file_name, params);
    bool is_correct = results.verification.is_correct;
    std::cout << (is_correct ? "✓✓✓ " : "xxx ")
              << getName() << " got " << (is_correct ? "correct" : "incorrect")
              << " solution in " << results.best_avg << " μs "
              << (params.must_parse ? "with" : "without") << " parsing" << std::endl;
}

template <typename T, typename S>
void Solver<T, S>::reportDefaultVerification()
{
    reportVerification(getInputFileName(), getSolutionFileName());
}

template <typename T, typename S>
void Solver<T, S>::reportDefaultTrials(std::array<TrialParameters, 2> params)
{
    if (params[0].must_parse == params[1].must_parse)
    {
        throw std::invalid_argument("There should be one parsing params and one non-parsing params.");
    }
    reportTrial(getInputFileName(), getSolutionFileName(), params[0]);
    reportTrial(getInputFileName(), getSolutionFileName(), params[1]);
}
