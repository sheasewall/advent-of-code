#ifndef UTILS_H
#define UTILS_H

#include <vector>

namespace utils
{
    // struct Node
    // {
    //     int label;
    //     int incoming;
    // };

    // struct Edge
    // {
    //     Node &u;
    //     Node &v;

    //     void decrement()
    //     {
    //         u.incoming--;
    //         v.incoming--;
    //     }
    // };

    // struct Graph
    // {
    //     std::vector<Node &> nodes;
    //     std::vector<Edge &> edges;

    //     std::vector<Node &> getIncoming(Node &node);

    //     void deleteEdge(Edge &dge);
    // };

    std::vector<std::string> split(const std::string &s, char delim);

    template <typename MyEnum>
    void generatePermutations(std::shared_ptr<std::vector<std::vector<MyEnum>>> to_fill, int depth, std::vector<MyEnum> all_enums)
    {
        if (depth == 1)
        {
            for (MyEnum my_enum : all_enums)
            {
                std::vector<MyEnum> single = {my_enum};
                to_fill->push_back(single);
            }
            return;
        }
        
        generatePermutations(to_fill, depth-1, all_enums);

        std::vector<std::vector<MyEnum>> new_permutations;
        for (std::vector<MyEnum> &permutation : *to_fill)
        {
            for (MyEnum my_enum : all_enums)
            {
                std::vector<MyEnum> copy = permutation;
                copy.push_back(my_enum);
                new_permutations.push_back(copy);
            }
        }
        to_fill->insert(to_fill->end(), new_permutations.begin(), new_permutations.end());
    }
}

#endif