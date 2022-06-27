#ifndef DIJKSTRA_HPP
# define DIJKSTRA_HPP

#include "../PathWithMinimumEffort.hpp"

class Dijkstra : public PathWithMinimumEffort {
public:
    Dijkstra(vector<vector<int> >& grid) : PathWithMinimumEffort(grid) {}
    virtual ~Dijkstra() {}

    int  heuristic(std::pair<int,int> coord){
        return 0;
    };
};

#endif