#ifndef EUCLIDEANDIAGONAL_HPP
# define EUCLIDEANDIAGONAL_HPP

#include "Euclidean.hpp"
#include <math.h>

class EuclideanDiagonal : public Euclidean {
public:
    EuclideanDiagonal(vector<vector<int> >& grid) : Euclidean(grid) {}

    void setDiagonal() {
        _diagonal = true;
    }
};

#endif 