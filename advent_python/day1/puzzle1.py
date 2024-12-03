import numpy as np

## Puzzle 1
# O(nlg(n))
def puzzle1_solver(file_name):
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