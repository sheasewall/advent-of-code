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
int puzzle1(std::string file_name) 
{
    std::vector<int> left_heap;
    std::vector<int> right_heap;
    readFileToHeaps(file_name, left_heap, right_heap);
    return getDistance(left_heap, right_heap);
}

// This function recurses until every element has been popped 
// from a heap. Thus it is up to 2nlg(n) or O(nlg(n)).
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

// readFileToHeaps is up to nlg(n) and calculateSimilarityScore
// is up to 2nlg(n), so this algorithm is 3nlg(n) or O(nlg(n)).
int puzzle2(std::string file_name) 
{
    std::vector<int> left_heap;
    std::vector<int> right_heap;
    readFileToHeaps(file_name, left_heap, right_heap);
    return calculateSimilarityScore(left_heap, right_heap);
}

// Since we are only doing vector pops, this is O(n). 
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

// this algorithm is dominated by the two nlg(n) sorts
// so it is O(nlg(n)).
int puzzle2sort(std::string file_name)
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

    // each sort is nlg(n)
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    // this should be O(n)
    return calculateSimilarityScoreSorted(left, right);
}

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
            puzzle1(file_name);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        p1_exec_times.push_back(duration.count() / NUMBER_TRIALS);
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
    for (int i = 0; i < NUMBER_REPEATS; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < NUMBER_TRIALS; j++) 
        {
            puzzle2(file_name);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        p2_exec_times.push_back(duration.count() / NUMBER_TRIALS);
    }
    int p2_solution = puzzle2(file_name);
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
            puzzle2sort(file_name);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        p2s_exec_times.push_back(duration.count() / NUMBER_TRIALS);
    }
    int p2s_solution = puzzle2sort(file_name);
    if (p2s_solution == P2_SOLUTION)
    {
        std::cout << "P2sorted2: " << *std::min_element(p2s_exec_times.begin(), p2s_exec_times.end()) << " microseconds" << std::endl;
    }
    else
    {
        std::cout << "P2sorted: incorrect" << std::endl;
    }
}
