#ifndef DIJKSTRADIAGONAL_HPP
# define DIJKSTRADIAGONAL_HPP

#include "Dijkstra.hpp"

class DijkstraDiagonal : public Dijkstra {
public:
    DijkstraDiagonal(vector<vector<int> >& grid) : Dijkstra(grid) {}

    void setDiagonal() {
        _diagonal = true;
    }
};

#endif 