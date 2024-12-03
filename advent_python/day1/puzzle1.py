import numpy as np

import timeit
import sys

## Puzzle 1
# O(nlg(n))
def puzzle1(file_name):
    list1, list2 = parse_double_list_from_file(file_name)
    return get_distance(list1, list2)

# heapsort is O(nlg(n))
def get_distance(list1, list2):
    list1_sorted = np.sort(list1, kind='heapsort')
    list2_sorted = np.sort(list2, kind='heapsort')

    distance = 0
    for i in range(len(list1)):
        distance += np.abs(list1_sorted[i] - list2_sorted[i])

    return distance

# presumably this is O(n)
def parse_double_list_from_file(file_name):
    return np.loadtxt(file_name, dtype=int,unpack=True)

## Puzzle 2
# Since get_total_similarity_score is O(n^2),
# this algorithm is O(n^2). 
def puzzle2(file_name):
    list1, list2 = parse_double_list_from_file(file_name)
    return get_total_similarity_score(list1, list2)

# unique_counts sorts the list it is called on,
# so it is O(nlog(n)). get_similarity_value 
# is O(n), and gets called for every element
# in list1, so this function is O(n^2).  
def get_total_similarity_score(list1, list2):
    occurance_data = np.unique_counts(list2)

    similarity_score = 0
    for i in range(len(list1)):
        similarity_score += get_similarity_value(list1[i], occurance_data)

    return similarity_score

# Memoization only provides savings if there are many 
# repeat elements, so this could be O(n^2) with all
# unique elements.
def puzzle2memod(file_name):
    list1, list2 = parse_double_list_from_file(file_name)
    return get_total_similarity_score_memoized(list1, list2)

# unique_counts is O(nlg(n)), and get_similarity_value is O(n)
# and it is called once for every unique element in list1,
# so if there are no repeated elements then it is O(n^2).
def get_total_similarity_score_memoized(list1, list2):
    occurance_data = np.unique_counts(list2)

    similarity_score = 0
    similarity_table = {}
    for i in range(len(list1)):
        num = list1[i]
        if not num in similarity_table:
            similarity_value = get_similarity_value(num, occurance_data)
            similarity_table[num] = similarity_value
            similarity_score += similarity_value
        else:
            similarity_score += similarity_table[num]

    return similarity_score

# O(n)
def get_similarity_value(num, occurance_data):
    # We should find 0 or 1 indices, so we
    # can early exit if we find a single index
    # np.where will find all occurances so
    # it is currently O(n)
    indices = np.where(occurance_data[0] == num)[0]
    if not indices.size > 0:
        return 0
    
    idx = indices[0]
    occurances = occurance_data[1][idx]
    return num * occurances

def main(file_name):
    NUMBER_REPEATS = 5
    NUMBER_TRIALS = 10000
    TIME_ROUND = 2
    P1_SOLUTION = 1882714
    P2_SOLUTION = 19437052
    FILE_NAME = "p1_input1.txt"
    
    p1_time = min(timeit.repeat(lambda: puzzle1(FILE_NAME), number=NUMBER_TRIALS, repeat=NUMBER_REPEATS))
    p1_solution = puzzle1(FILE_NAME)

    p2_time = min(timeit.repeat(lambda: puzzle2(FILE_NAME), number=NUMBER_TRIALS, repeat=NUMBER_REPEATS))
    p2_solution = puzzle2(FILE_NAME)

    p2_time_memoized = min(timeit.repeat(lambda: puzzle2memod(FILE_NAME), number=NUMBER_TRIALS, repeat=NUMBER_REPEATS))
    p2_solution_memoized = puzzle2memod(FILE_NAME)

    if p1_solution == P1_SOLUTION:
        print("Puzzle 1:", round(p1_time / NUMBER_TRIALS * 1000000, TIME_ROUND), "microseconds")
    else:
        print("Puzzle 1: incorrect")
    if p2_solution == P2_SOLUTION:
        print("Puzzle 2:", round(p2_time / NUMBER_TRIALS * 1000000, TIME_ROUND), "microseconds")
    else:
        print("Puzzle 2: incorrect")
    if p2_solution_memoized == P2_SOLUTION:
        print("P2 memod:", round(p2_time_memoized / NUMBER_TRIALS * 1000000, TIME_ROUND), "microseconds")
    else:
        print("P2 memod: incorrect")

if __name__ == '__main__':
    main(sys.argv[1])