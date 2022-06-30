/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   manhattan.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/28 18:36:02 by abba          #+#    #+#                 */
/*   Updated: 2022/06/28 18:36:02 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANHATTAN_HPP
#define MANHATTAN_HPP

#include "state.hpp"

class Manhattan: public State
{
public:
	Manhattan(vector<vector<int> >& grid) : State(grid) {}
	int heuristic(int x, int y)
	{
//		cout << "reach " << x << " y " << y << endl;
//		cout << "reach1 " << _goalX << " y " << _goalY << endl;
		return abs(x - _goalX) + abs(y - _goalY);
	}

	int manhattan(int x, int y)
	{
		for (size_t i = 0; i < _goalState.size(); ++i)
		{
			for (size_t j = 0; j < _goalState[i].size(); ++j)
			{
				if (_initialState[x][y] == _goalState[i][j])
				{
//					cout << "reach " << _initialState[x][y] << endl;
					return heuristic(i, j);
				}
			}
		}
		return 0;
	}

	int	heuristic(const vector<vector<int> > grid)
	{
		int	h = 0;
		for (size_t i = 0; i < grid.size(); ++i)
		{
			for (size_t j = 0; j < grid[i].size(); ++j)
			{
				_goalX = i;
				_goalY = j;
				h += manhattan(i, j);
			}
		}
		return h;
	}
private:
	int		_goalX;
	int		_goalY;
};

#endif
