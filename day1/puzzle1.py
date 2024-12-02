import numpy as np

import timeit
import sys

## Puzzle 1

def get_distance(list1, list2):
    list1_sorted = np.sort(list1)
    list2_sorted = np.sort(list2)

    distance = 0
    for i in range(len(list1)):
        distance += np.abs(list1_sorted[i] - list2_sorted[i])

    return distance

def parse_double_list_from_file(file_name):
    return np.loadtxt(file_name, dtype=int,unpack=True)

## Puzzle 2

def get_similarity_value(num, occurance_data):
    indices = np.where(occurance_data[0] == num)[0]
    if not indices.size > 0:
        return 0
    
    idx = indices[0]
    occurances = occurance_data[1][idx]
    return num * occurances

def get_total_similarity_score(list1, list2):
    occurance_data = np.unique_counts(list2)

    similarity_score = 0
    for i in range(len(list1)):
        similarity_score += get_similarity_value(list1[i], occurance_data)

    return similarity_score

def main(file_name):
    REPEAT_COUNT = 100
    TIME_ROUND = 10
    list1, list2 = parse_double_list_from_file(file_name)
    
    p1_time = min(timeit.repeat(lambda: get_distance(list1, list2), repeat=REPEAT_COUNT, number=1))
    p1_solution = get_distance(list1, list2)

    p2_time = min(timeit.repeat(lambda: get_total_similarity_score(list1, list2), repeat=REPEAT_COUNT, number=1))
    p2_solution = get_total_similarity_score(list1, list2)

    print("Puzzle 1:", p1_solution, "in", round(p1_time, TIME_ROUND))
    print("Puzzle 2:", p2_solution, "in", round(p2_time, TIME_ROUND))

if __name__ == '__main__':
    main(sys.argv[1])