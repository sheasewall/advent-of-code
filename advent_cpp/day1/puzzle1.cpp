#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

void readFileToHeaps(std::string file_name, std::vector<int> &left_list, std::vector<int> &right_list)
{
    std::ifstream file(file_name);
    std::string str;
    int parsed;
    while (std::getline(file, str, ' '))
    {
        parsed = stoi(str);
        left_list.push_back(parsed);
        std::push_heap(left_list.begin(), left_list.end());
        std::getline(file, str);
        parsed = stoi(str);
        right_list.push_back(parsed);
        std::push_heap(right_list.begin(), right_list.end());
    }
}

int getDistance(std::vector<int> left_heap, std::vector<int> right_heap)
{
    int distance = 0;
    while (!left_heap.empty())
    {
        distance += abs(left_heap.front() - right_heap.front());
        std::pop_heap(left_heap.begin(), left_heap.end());
        std::pop_heap(right_heap.begin(), right_heap.end());
        left_heap.pop_back();
        right_heap.pop_back();
    }
    return distance;
}

int puzzle1(std::string file_name) 
{
    std::vector<int> left_heap;
    std::vector<int> right_heap;
    readFileToHeaps(file_name, left_heap, right_heap);
    return getDistance(left_heap, right_heap);
}

int calculateSimilarityScore(std::vector<int> left_heap, std::vector<int> right_heap)
{
    if (left_heap.size() == 0 || right_heap.size() == 0) 
    {
        return 0;
    }
    int left_head = left_heap.front();
    int right_head = right_heap.front();
    if (left_head < right_head)
    {
        std::pop_heap(right_heap.begin(), right_heap.end());
        right_heap.pop_back();
        return calculateSimilarityScore(left_heap, right_heap); 
    }
    if (left_head > right_head) 
    {
        std::pop_heap(left_heap.begin(), left_heap.end());
        left_heap.pop_back();
        return calculateSimilarityScore(left_heap, right_heap);
    }
    // left_head == right_head
    std::pop_heap(right_heap.begin(), right_heap.end());
    right_heap.pop_back();
    return left_head + calculateSimilarityScore(left_heap, right_heap);
}

int puzzle2(std::string file_name) 
{
    std::vector<int> left_heap;
    std::vector<int> right_heap;
    readFileToHeaps(file_name, left_heap, right_heap);
    return calculateSimilarityScore(left_heap, right_heap);
}

int main(int argc, char *argv[])
{
    const int NUMBER_TRIALS = 10000;
    const int P1_SOLUTION = 1882714;
    const int P2_SOLUTION = 19437052;
    const std::string file_name = argv[1];

    std::vector<long> p1_exec_times;
    for (int i = 0; i < NUMBER_TRIALS; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        puzzle1(file_name);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        p1_exec_times.push_back(duration.count());
    }
    if (puzzle1(file_name) == P1_SOLUTION)
    {
        std::cout << "Puzzle 1: " << *std::min_element(p1_exec_times.begin(), p1_exec_times.end()) << " microseconds" << std::endl;
    }
    else
    {
        std::cout << "Puzzle 1: incorrect" << std::endl;
    }

    std::vector<long> p2_exec_times;
    for (int i = 0; i < NUMBER_TRIALS; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        puzzle2(file_name);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        p2_exec_times.push_back(duration.count());
    }
    if (puzzle2(file_name) == P2_SOLUTION)
    {
        std::cout << "Puzzle 2: " << *std::min_element(p2_exec_times.begin(), p2_exec_times.end()) << " microseconds" << std::endl;
    }
    else
    {
        std::cout << "Puzzle 2: incorrect" << std::endl;
    }
}
