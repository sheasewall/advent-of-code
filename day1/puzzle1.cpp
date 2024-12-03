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

int puzzle1Solver(std::string file_name) 
{
    std::vector<int> left_heap;
    std::vector<int> right_heap;
    readFileToHeaps(file_name, left_heap, right_heap);
    return getDistance(left_heap, right_heap);
}