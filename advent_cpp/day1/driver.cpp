#include <fstream>
#include <string>
#include <vector>

#include "puzzle2.cpp"

int main(int argc, char *argv[])
{
    const int NUMBER_REPEATS = 5;
    const int NUMBER_TRIALS = 500;
    const int P1_SOLUTION = 1882714;
    const int P2_SOLUTION = 19437052;
    const std::string file_name = argv[1];

    std::vector<long> p1_exec_times;
    for (int i = 0; i < NUMBER_REPEATS; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < NUMBER_TRIALS; j++) 
        {
            puzzle1Solver(file_name);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        p1_exec_times.push_back(duration.count() / NUMBER_TRIALS);
    }
    if (puzzle1Solver(file_name) == P1_SOLUTION)
    {
        std::cout << "Puzzle 1: " << *std::min_element(p1_exec_times.begin(), p1_exec_times.end()) << " microseconds" << std::endl;
    }
    else
    {
        std::cout << "Puzzle 1: incorrect" << std::endl;
    }

    std::vector<long> p2_exec_times;
    for (int i = 0; i < NUMBER_REPEATS; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < NUMBER_TRIALS; j++) 
        {
            puzzle2Solver(file_name);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        p2_exec_times.push_back(duration.count() / NUMBER_TRIALS);
    }
    int p2_solution = puzzle2Solver(file_name);
    if (p2_solution == P2_SOLUTION)
    {
        std::cout << "Puzzle 2: " << *std::min_element(p2_exec_times.begin(), p2_exec_times.end()) << " microseconds" << std::endl;
    }
    else
    {
        std::cout << "Puzzle 2: incorrect" << std::endl;
    }

    std::vector<long> p2s_exec_times;
    for (int i = 0; i < NUMBER_REPEATS; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < NUMBER_TRIALS; j++) 
        {
            puzzle2SortedSolver(file_name);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        p2s_exec_times.push_back(duration.count() / NUMBER_TRIALS);
    }
    int p2s_solution = puzzle2SortedSolver(file_name);
    if (p2s_solution == P2_SOLUTION)
    {
        std::cout << "P2sorted2: " << *std::min_element(p2s_exec_times.begin(), p2s_exec_times.end()) << " microseconds" << std::endl;
    }
    else
    {
        std::cout << "P2sorted: incorrect" << std::endl;
    }
}
