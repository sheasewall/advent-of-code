#ifndef UTILS_H
#define UTILS_H

#include <vector>

namespace utils
{
    std::vector<std::string> split(const std::string &s, char delim);

    template <typename MyEnum>
    void generatePermutations(std::shared_ptr<std::vector<std::shared_ptr<std::vector<MyEnum>>>> to_fill, int depth, std::vector<MyEnum> all_enums)
    {
        if (depth == 1)
        {
            for (MyEnum my_enum : all_enums)
            {
                std::vector<MyEnum> single = {my_enum};
                std::shared_ptr<std::vector<MyEnum>> p_single = std::make_shared<std::vector<MyEnum>>(single);
                to_fill->push_back(p_single);
            }
            return;
        }

        generatePermutations(to_fill, depth - 1, all_enums);

        std::shared_ptr<std::vector<std::shared_ptr<std::vector<MyEnum>>>> new_permutations = std::make_shared<std::vector<std::shared_ptr<std::vector<MyEnum>>>>();
        for (std::shared_ptr<std::vector<MyEnum>> perm : *to_fill)
        {
            for (MyEnum my_enum : all_enums)
            {
                std::shared_ptr<std::vector<MyEnum>> p_copy_perm = std::make_shared<std::vector<MyEnum>>(*perm);
                p_copy_perm->push_back(my_enum);
                new_permutations->push_back(p_copy_perm);
            }
        }

        to_fill->insert(to_fill->end(), new_permutations->begin(), new_permutations->end());
    }

    template <typename MyEnum>
    void generatePermutations(std::vector<std::vector<MyEnum>> &to_fill, int depth, const std::vector<MyEnum> &all_enums)
    {
        if (depth == 1)
        {
            for (MyEnum my_enum : all_enums)
            {
                to_fill.push_back(std::vector<MyEnum>({my_enum}));
            }
            return;
        }

        generatePermutations(to_fill, depth - 1, all_enums);

        std::vector<std::vector<MyEnum>> new_permutations;
        for (std::vector<MyEnum> &perm : to_fill)
        {
            for (MyEnum my_enum : all_enums)
            {
                std::vector<MyEnum> copy = perm;
                copy.push_back(my_enum);
                new_permutations.push_back(copy);
            }
        }

        to_fill.insert(to_fill.end(), new_permutations.begin(), new_permutations.end());
    }

    template <typename T, std::size_t N>
    std::ostream &operator<<(std::ostream &os, const std::array<T, N> &arr)
    {
        os << "[";
        for (std::size_t i = 0; i < N; ++i)
        {
            os << arr[i];
            if (i < N - 1)
            {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }
}

#endif