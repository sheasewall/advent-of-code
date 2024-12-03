import numpy as np

from day1.puzzle1 import parse_double_list_from_file

## Puzzle 2
# Since get_total_similarity_score is O(n^2),
# this algorithm is O(n^2). 
def puzzle2_solver(file_name):
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
def puzzle2_memod_solver(file_name):
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