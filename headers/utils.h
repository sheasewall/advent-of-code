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
}

#endif