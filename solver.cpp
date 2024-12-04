#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <iostream>

class Solver
{
public:
    int (*pSolver)(std::string file_name);
    int day_index;
    int puzzle_index;

    Solver(int day_index, int puzzle_index, int (*pSolver)(std::string file_name));

    std::string getInputFileName();
    std::string getSolutionFileName();

    int computeSolution();
    int getCorrectSolution();
    long timeSolver(int num_reps, int num_batches);
    bool verifySolver();

    static void timeDay(int day_index, std::vector<int> puzzle_indices, std::vector<int (*)(std::string file_name)> pSolvers, std::vector<std::array<int, 2>> timing_info);
};

Solver::Solver(int day_index, int puzzle_index, int (*pSolver)(std::string file_name)) {
    this->day_index = day_index;
    this->puzzle_index = puzzle_index;
    this->pSolver = pSolver;
}

std::string Solver::getInputFileName() 
{
    std::string input_file_name = "day";
    input_file_name += std::to_string(day_index);
    input_file_name += "/input.txt";
    return input_file_name;
}

std::string Solver::getSolutionFileName() 
{
    std::string solution_file_name = "day";
    solution_file_name += std::to_string(day_index);
    solution_file_name += "/solutions.txt";
    return solution_file_name;
}

int Solver::computeSolution() 
{
    return pSolver(getInputFileName());
}

int Solver::getCorrectSolution() 
{
    std::ifstream file(getSolutionFileName());
    std::string str;
    int solutions[2];
    std::getline(file, str);
    solutions[0] = stoi(str);
    std::getline(file, str);
    solutions[1] = stoi(str);

    return solutions[puzzle_index - 1];
}

long Solver::timeSolver(int num_batches, int num_reps)
{
    std::vector<long> exec_times;
    for (int i = 0; i < num_batches; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < num_reps; j++) 
        {
            pSolver(getInputFileName());
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        exec_times.push_back(duration.count());
    }
    return *std::min_element(exec_times.begin(), exec_times.end()) / num_reps;
}

bool Solver::verifySolver() {
    int computed_solution = computeSolution();
    int solution = getCorrectSolution();
    return computed_solution == solution;
}

void Solver::timeDay(int day_index, std::vector<int> puzzle_indices, std::vector<int (*)(std::string file_name)> pSolvers, std::vector<std::array<int, 2>> timing_info) {
    for (int i = 0; i < pSolvers.size(); i++) {
        Solver solver = Solver(day_index, puzzle_indices[i], pSolvers[i]);
        long best_avg = solver.timeSolver(timing_info[i][0], timing_info[i][1]);
        bool is_correct = solver.verifySolver();
        std::cout << "Solver " << std::to_string(i) << " computed a " 
            << (is_correct ? "True" : "False") << " answer in " << std::to_string(best_avg) 
            << " microseconds" << std::endl;
    }    
}