/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   state.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 15:38:59 by abba          #+#    #+#                 */
/*   Updated: 2022/06/27 15:38:59 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_HPP
#define STATE_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

class State
{
public:
	State();
	State(vector<vector<int> >& grid) : _initialState(grid) {}
	virtual ~State();

	void					printGrid(vector< vector<int> > state) const;
	vector< vector<int> >	getInitialState(string input);
	void					getGoalState(string input);
	vector< vector<int> >	getGrid(string input);
	void					misplacedTiles(vector<vector<int> > grid);
	void					findEmptyIndex();
	void					test();
	vector< State>			move() const;
	void					initVector();
	void 					solve();
	void 					initH2();
	int 					getMin();
	void					setInitialState(int min);
	vector<vector<int> >	deepCpy(const vector<vector<int> > grid)
	{
		new vector<vector<int> >(grid);
//		cout << "im here";
//		vector<vector<int> > out;
//		for (size_t i = 0; i < grid.size(); ++i)
//		{
//			out.push_back(grid.at(i));
//		}
		return vector<vector<int> >(grid);
	}

	virtual int	heuristic(const vector<vector<int> > grid) = 0;

protected:
	int _hScore;
	int _x;
	int _y;
	vector< vector<int> > _initialState;
	vector< vector<int> > _goalState;
	vector< vector<int> > _up;
	vector< vector<int> > _down;
	vector< vector<int> > _left;
	vector< vector<int> > _right;

	int	_upScore;
	int	_downScore;
	int	_leftScore;
	int	_rightScore;
};

vector< vector<int> >	getGrid1(string input);;

#endif