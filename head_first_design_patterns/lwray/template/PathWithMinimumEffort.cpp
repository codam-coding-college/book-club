#include "PathWithMinimumEffort.hpp" 

PathWithMinimumEffort::PathWithMinimumEffort(vector<vector<int> >& grid) 
    : _grid(grid), _diagonal(false) {};

void    PathWithMinimumEffort::solve() {  //** template method **
    init();
    setDiagonal(); // hook

    int steps = 0;
    while(true) {
        steps++;
        node smallest = _openSet.top();
        if(smallest.coord == _endGoal.coord){
            std::cout   << "Reached destination, minimum required effort is: "
                        << smallest.g_cost
                        << ".\nResult found in " << steps << " step calculations.\n\n";
            return;
        }
        _openSet.pop();
        updateNeighbours(smallest);
        _closedSet.insert(smallest.coord);
    }   
}

void    PathWithMinimumEffort::init() {
    node start;
    start.coord = std::make_pair(0,0); 
    start.g_cost = 0;
    start.h_cost = heuristic(start.coord);
    start.f_cost = start.g_cost + start.h_cost;
    _openSet.push(start);
    _endGoal.coord = std::make_pair(_grid[0].size() - 1, _grid.size() - 1); 
}

void PathWithMinimumEffort::updateNeighbours(node current) {
    if(_closedSet.count(current.coord)) //catches duplicates in openSet
        return;
    updateNode(current.coord.first, current.coord.second - 1, current);      //North
    updateNode(current.coord.first + 1 , current.coord.second, current);     //East
    updateNode(current.coord.first, current.coord.second + 1, current);      //South
    updateNode(current.coord.first - 1, current.coord.second, current);      //West
    if (_diagonal) {
        updateNode(current.coord.first + 1, current.coord.second - 1, current);  //NE
        updateNode(current.coord.first + 1 , current.coord.second + 1, current); //SE
        updateNode(current.coord.first - 1, current.coord.second + 1, current);  //SW
        updateNode(current.coord.first - 1, current.coord.second - 1, current);  //NW
    }
}

void PathWithMinimumEffort::updateNode(int x, int y, node current) {
    node neighbour;
    neighbour.coord = std::make_pair(x, y);
    if(_closedSet.count(neighbour.coord))
        return;
    if(y >= 0 && y < _grid.size() && x >= 0 && x < _grid[0].size()) {
        neighbour.g_cost = current.g_cost + calculateSteepness(x, y, current);
        neighbour.h_cost = heuristic(neighbour.coord);
        neighbour.f_cost = neighbour.g_cost + neighbour.h_cost;
        _openSet.push(neighbour);
    }   
}

int PathWithMinimumEffort::calculateSteepness(int x, int y, node current){
    return abs(_grid[y][x] - _grid[current.coord.second][current.coord.first]) + 1;
}

void PathWithMinimumEffort::setDiagonal() {}
