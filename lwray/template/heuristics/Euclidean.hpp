#ifndef EUCLIDEAN_HPP
# define EUCLIDEAN_HPP

#include "../PathWithMinimumEffort.hpp"
#include <math.h>

class Euclidean : public PathWithMinimumEffort {
public:
    Euclidean(vector<vector<int> >& grid) : PathWithMinimumEffort(grid) {}
    virtual ~Euclidean() {}
    
    int  heuristic(std::pair<int,int> coord){
        return sqrt(pow(coord.first - _endGoal.coord.first, 2) +
                pow(coord.second - _endGoal.coord.second, 2));
    };
};

#endif 