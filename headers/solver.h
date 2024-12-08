#ifndef SOLVER_H
#define SOLVER_H

#include <string>
#include <vector>
#include <array>

namespace solve
{
    template <typename K>
    struct VerificationResults
    {
        bool is_correct;
        K computed_solution;
        K correct_solution;

        VerificationResults(K computed_solution, K correct_solution)
        {
            this->is_correct = (computed_solution == correct_solution);
            this->computed_solution = computed_solution;
            this->correct_solution = correct_solution;
        }
    };

    struct TrialParameters
    {
        bool must_parse;
        int num_batches;
        int num_reps;
    };

    template <typename K>
    struct TrialResults
    {
        long best_avg;
        VerificationResults<K> verification;
    };

    template <typename S>
    class SolutionFileParser
    {
    public:
        virtual std::vector<S> parseSolutionFile(const std::string &file_name) = 0;
    };

    // Partial specialization for int return type
    template <>
    class SolutionFileParser<int>
    {
    public:
        virtual std::vector<int> parseSolutionFile(const std::string &file_name)
        {
            std::ifstream file(file_name);
            std::string str;
            std::vector<int> solutions;
            std::getline(file, str);
            solutions.push_back(std::stoi(str));
            std::getline(file, str);
            solutions.push_back(std::stoi(str));
            return solutions;
        }
    };

    // Partial specialization for long return type
    template <>
    class SolutionFileParser<long>
    {
    public:
        virtual std::vector<long> parseSolutionFile(const std::string &file_name)
        {
            std::ifstream file(file_name);
            std::string str;
            std::vector<long> solutions;
            std::getline(file, str);
            solutions.push_back(std::stol(str));
            std::getline(file, str);
            solutions.push_back(std::stol(str));
            return solutions;
        }
    };

    template <typename T, typename S>
    class Solver : public SolutionFileParser<S> 
    {
    private:
        std::string name;
        int day_index;
        int puzzle_index;

    public:
        Solver(std::string name, int day_index, int puzzle_index);

        virtual T parseInputFile(std::string file_name) = 0;
        virtual S computeSolution(T input_data) = 0;
        //virtual std::vector<S> parseSolutionFile(std::string file_name) = 0;

        S getCorrectSolution(std::string file_name);
        VerificationResults<S> verify(std::string input_file_name, std::string solution_file_name);
        TrialResults<S> trial(std::string input_file_name, std::string solution_file_name, TrialParameters params);

        void reportVerification(std::string input_file_name, std::string solution_file_name);
        void reportTrial(std::string input_file_name, std::string solution_file_name, TrialParameters params);

        void reportDefaultVerification();
        void reportDefaultTrials(std::array<TrialParameters, 2> params);

        std::string getInputFileName();
        std::string getSolutionFileName();
        std::string getName();
    };

    // template <typename T, typename S>
    // std::vector<S> Solver<T, S>::parseSolutionFile(std::string file_name)
    // {
    //     throw std::runtime_error("parseSolutionFile not implemented for this type");
    // }

    // template <typename T, typename S>
    // class Solver : public Solver<T, int>
    // {
    // public:
    //     using Solver<T, int>::Solver;

    //     std::vector<int> parseSolutionFile(std::string file_name) override
    //     {
    //         std::ifstream file(file_name);
    //         std::string str;
    //         std::vector<int> solutions;
    //         std::getline(file, str);
    //         solutions.push_back(std::stoi(str));
    //         std::getline(file, str);
    //         solutions.push_back(std::stoi(str));
    //         return solutions;
    //     }
    // };

    // template <typename T, typename S>
    // class Solver : public Solver<T, long>
    // {
    // public:
    //     using Solver<T, long>::Solver;

    //     std::vector<long> parseSolutionFile(std::string file_name) override
    //     {
    //         std::ifstream file(file_name);
    //         std::string str;
    //         std::vector<long> solutions;
    //         std::getline(file, str);
    //         solutions.push_back(std::stol(str));
    //         std::getline(file, str);
    //         solutions.push_back(std::stol(str));
    //         return solutions;
    //     }
    // };
}

#include "../source/solver.cpp"

#endif