#include <fstream>
#include <vector>
#include <string>

#include "puzzle1.cpp"

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

namespace day1
{
    int puzzle2Solver(std::string file_name)
    {
        std::vector<int> left_heap;
        std::vector<int> right_heap;
        readFileToHeaps(file_name, left_heap, right_heap);
        return calculateSimilarityScore(left_heap, right_heap);
    }
}

int calculateSimilarityScoreSorted(std::vector<int> left_list, std::vector<int> right_list)
{
    if (left_list.size() == 0 || right_list.size() == 0)
    {
        return 0;
    }
    int left_head = left_list.back();
    int right_head = right_list.back();
    if (left_head < right_head)
    {
        right_list.pop_back();
        return calculateSimilarityScoreSorted(left_list, right_list);
    }
    if (left_head > right_head)
    {
        left_list.pop_back();
        return calculateSimilarityScoreSorted(left_list, right_list);
    }
    // left_head == right_head
    right_list.pop_back();
    return left_head + calculateSimilarityScoreSorted(left_list, right_list);
}

int puzzle2SortedSolver(std::string file_name)
{
    std::vector<int> left;
    std::vector<int> right;

    std::ifstream file(file_name);
    std::string str;
    int parsed;
    while (std::getline(file, str, ' '))
    {
        parsed = stoi(str);
        left.push_back(parsed);
        std::getline(file, str);
        parsed = stoi(str);
        right.push_back(parsed);
    }

    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    return calculateSimilarityScoreSorted(left, right);
}