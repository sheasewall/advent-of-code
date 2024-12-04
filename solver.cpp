#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <iostream>

template <typename T, typename S>
class Solver
{
public:
    int day_index;
    int puzzle_index;

    Solver(int day_index, int puzzle_index);

    virtual T parseFile() = 0;
    virtual S computeSolution(T input_data) = 0;
    virtual S getCorrectSolution() = 0;
    S computeSolution() { return computeSolution(parseFile()); };
    long timeSolver(int num_batches, int num_reps);
    long timeSolver(int num_batches, int num_reps, T input_data);
    bool verifySolver();
    void reportCalculation();
    void reportTrial(int num_batches, int num_reps);
    void reportTrial(int num_batches, int num_reps, T input_data);

protected:
    std::string getInputFileName();
    std::string getSolutionFileName();
};

template <typename T, typename S>
Solver<T, S>::Solver(int day_index, int puzzle_index)
{
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
long Solver<T, S>::timeSolver(int num_batches, int num_reps)
{
    std::vector<long> exec_times;
    for (int i = 0; i < num_batches; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < num_reps; j++)
        {
            computeSolution();
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        exec_times.push_back(duration.count());
    }
    return *std::min_element(exec_times.begin(), exec_times.end()) / num_reps;
}

template <typename T, typename S>
long Solver<T, S>::timeSolver(int num_batches, int num_reps, T input_data)
{
    std::vector<long> exec_times;
    for (int i = 0; i < num_batches; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < num_reps; j++)
        {
            computeSolution(input_data);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        exec_times.push_back(duration.count());
    }
    return *std::min_element(exec_times.begin(), exec_times.end()) / num_reps;
}

template <typename T, typename S>
bool Solver<T, S>::verifySolver()
{
    S computed_solution = computeSolution();
    S solution = getCorrectSolution();
    return computed_solution == solution;
}

template <typename T, typename S>
void Solver<T, S>::reportCalculation() 
{
    S computed_solution = computeSolution();
    S solution = getCorrectSolution();
    std::cout << "Solver got answer: " << computed_solution 
        << " and the correct answer is " << solution << std::endl;
}

template <typename T, typename S>
void Solver<T, S>::reportTrial(int num_batches, int num_reps)
{
    bool is_correct = verifySolver();
    long best_avg = timeSolver(num_batches, num_reps);
    std::cout << "Solver parsed file and computed a "
              << (is_correct ? "True" : "False") << " answer in "
              << std::to_string(best_avg) << " microseconds" << std::endl;
}

template <typename T, typename S>
void Solver<T, S>::reportTrial(int num_batches, int num_reps, T input_data)
{
    bool is_correct = verifySolver();
    long best_avg = timeSolver(num_batches, num_reps, input_data);
    std::cout << "Solver computed a "
              << (is_correct ? "True" : "False") << " answer in "
              << std::to_string(best_avg) << " microseconds" << std::endl;
}