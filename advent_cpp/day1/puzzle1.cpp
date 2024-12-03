#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

// The push_heap operation is up to lg(list.size()). list.size() is at most n, the number of elements
// to be read in total. Thus push_heap is at most lg(n). We do exactly one push for every element that 
// is read, so the time complexity from heap pushes is at most nlg(n). vector pushes are generally
// constant, and getline is generally linear on the number of characters read, so this function is
// dominated by nlg(n) meaning it is O(nlg(n)).
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

// pop_heap is up to 2lg(n) and happens exactly once for every element 
// that was read in. front() and vector pop_back() are both constant.
// The function is dominated by n * 2lg(n) and thus is O(nlg(n)).
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

// Every element is pushed and eventually popped from a heap
// so this algorithm is O(nlg(n)) or more specifically
// up to 3nlg(n). 
int puzzle1Solver(std::string file_name) 
{
    std::vector<int> left_heap;
    std::vector<int> right_heap;
    readFileToHeaps(file_name, left_heap, right_heap);
    return getDistance(left_heap, right_heap);
}