#ifndef MANHATTAN_HPP
# define MANHATTAN_HPP

#include "../PathWithMinimumEffort.hpp"

// The Manhattan distance is not an admissible heuristic for A* when diagonal movement is allowed.

class Manhattan : public PathWithMinimumEffort {
public:
    Manhattan(vector<vector<int> >& grid) : PathWithMinimumEffort(grid) {}
    
    int  heuristic(std::pair<int,int> coord){
        return abs(coord.first - _endGoal.coord.first) +
                abs(coord.second - _endGoal.coord.second);
    };
};

#endif