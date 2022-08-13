#ifndef PATHWITHMINIMUMEFFORT_HPP
# define PATHWITHMINIMUMEFFORT_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <stack>

using std::vector;
using std::priority_queue;
using std::set;

/* Inspired by Leetcode exercise: https://leetcode.com/problems/path-with-minimum-effort/
    You are a hiker preparing for an upcoming hike. You are given heights, a 2D array of size rows x columns, 
    where heights[row][col] represents the height of cell (row, col). You are situated in the top-left cell, (0, 0), 
    and you hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed). 
    You can move up, down, left, or right, and you wish to find a route that requires the minimum effort.
    A route's effort is the sum of every step and the absolute difference in heights between two consecutive cells.
    Return the minimum effort required to travel from the top-left cell to the bottom-right cell.
*/

typedef struct node {
    int g_cost;
    int h_cost;
    int f_cost;
    std::pair<int,int> coord;
} node;

class PathWithMinimumEffort {
protected:
    vector<vector<int> >&        _grid;
    node                        _endGoal;
    set<std::pair<int,int> >    _closedSet;
    priority_queue<node, vector<node>, std::greater<node> > _openSet;
    bool                        _diagonal;

public:
    PathWithMinimumEffort(vector<vector<int> >&);
    virtual ~PathWithMinimumEffort() {}
    void        solve();

private:
    void        init();
    void        updateNeighbours(node);
    void        updateNode(int x, int y, node);
    int         calculateSteepness(int x, int y, node);
    void        run(bool withDiagonal);

protected:
    virtual int     heuristic(std::pair<int,int>) = 0;
    virtual void    setDiagonal();
};

bool operator>(const node& lhs, const node& rhs) {
    return (lhs.f_cost > rhs.f_cost) ||
        (lhs.f_cost == rhs.f_cost && lhs.h_cost > rhs.h_cost);
}

#endif