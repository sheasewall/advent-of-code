#include <vector>
#include <sstream>

#include "../headers/utils.h"

using namespace utils;

std::vector<std::string> utils::split(const std::string &s, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

// std::vector<Node &> utils::Graph::getIncoming(Node &node)
// {
//     return std::vector<Node &>();
// }

// void utils::Graph::deleteEdge(Edge &dge)
// {
//     return;
// }