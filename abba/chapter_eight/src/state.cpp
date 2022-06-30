/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   state.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: abba <abba@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/27 15:43:26 by abba          #+#    #+#                 */
/*   Updated: 2022/06/27 15:43:26 by abba          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/state.hpp"
#include "../include/manhattan.hpp"

State::State() {
	std::cout << "constructor called\n";
}

State::~State() {
	std::cout << "deconstruct called\n";
}

void State::printGrid(vector< vector<int> > state) const
{
	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < state[i].size(); ++j)
			cout << state[i][j] << ' ';
		cout << endl;
	}
	cout << endl;
}

vector<vector<int>> State::getGrid(string input)
{
	vector<int> row;
	std::string line;
	vector< vector<int> > grid;

	std::ifstream file(input);
	if (!file)
	{
		cout << "invalid file\n";
		exit(1);
	}
	while (getline(file, line))
	{
		remove(line.begin(), line.end(), ' ');
		for (int i = 0; i < 3; ++i)
		{
			row.push_back((int)line[i] - '0');
		}
		grid.push_back(row);
		row.clear();
	}
	return grid;
}

vector<vector<int> > State::getInitialState(string input)
{
	return getGrid(input);
}

void State::getGoalState(string input)
{
	_goalState = getGrid(input);
}

void State::misplacedTiles(vector<vector<int> > grid)
{
	_hScore = 0;
	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < grid[i].size(); ++j)
		{
			if (_goalState[i][j] != grid[i][j])
				_hScore++;
		}
	}
}

void	State::findEmptyIndex()
{
	for (size_t i = 0; i < _initialState.size(); ++i)
	{
		for (size_t j = 0; j < _initialState[i].size(); ++j)
		{
			if (_initialState[i][j] == 0)
			{
				_x = i;
				_y = j;
			}
		}
	}
}

void State::initH2()
{
	_upScore = 52346124;
	_downScore = 52346124;
	_leftScore = 52346124;
	_rightScore = 52346124;
}

int State::getMin()
{
	int	min;

	if (_upScore < _downScore)
		min = _upScore;
	else
		min = _downScore;
	if (min > _leftScore)
		min = _leftScore;
	if (min > _rightScore)
		min = _rightScore;
	return min;
}

void State::setInitialState(int min)
{
	if (min == _upScore)
		_initialState = _up;
	else if (min == _downScore)
		_initialState = _down;
	else if (min == _leftScore)
		_initialState = _left;
	else if (min == _rightScore)
		_initialState = _right;
}

void	State::test()
{
	static int a = 0;
	findEmptyIndex();
	initH2();
	printGrid(_initialState);
	if (_x > 0)
	{
		_up = _initialState;
		swap(_up[_x][_y], _up[_x - 1][_y]);
		misplacedTiles(_up);
		_upScore = heuristic(_up) + _hScore;
		cout << "_upScore " << _upScore << endl;
		printGrid(_up);
	}
	if (_x < 2)
	{
		_down = _initialState;
		swap(_down[_x][_y], _down[_x + 1][_y]);
		misplacedTiles(_down);
		_downScore = heuristic(_down) + _hScore;
		cout << "_downScore " << _downScore << endl;
		printGrid(_down);
	}
	if (_y > 0)
	{
		_left = _initialState;
		swap(_left[_x][_y], _left[_x][_y - 1]);
		misplacedTiles(_left);
		_leftScore = heuristic(_left) + _hScore;
		cout << "_leftScore " << _leftScore << endl;
		printGrid(_left);
	}
	if (_y < 2)
	{
		_right = _initialState;
		swap(_right[_x][_y], _right[_x][_y + 1]);
		misplacedTiles(_right);
		_rightScore = heuristic(_right) + _hScore;
		cout << "_rightScore " << _rightScore << endl;
		printGrid(_right);
	}
	int min = getMin();
	cout << "GRID NUMBER " << min << endl;
	setInitialState(min);
	a++;
	printGrid(_initialState);
	misplacedTiles(_initialState);
	if (!_hScore)
		exit(0);
	if (a == 3)
		exit(0);
}

vector<vector<int>> getGrid1(string input)
{
	vector<int> row;
	std::string line;
	vector< vector<int> > grid;

	std::ifstream file(input);
	if (!file)
	{
		cout << "invalid file\n";
		exit(1);
	}
	while (getline(file, line))
	{
		remove(line.begin(), line.end(), ' ');
		for (int i = 0; i < 3; ++i)
		{
			row.push_back((int)line[i] - '0');
		}
		grid.push_back(row);
		row.clear();
	}
	return grid;
}

void State::solve()
{
	getGoalState("goal_map1");
	while (1)
	{
		misplacedTiles(_initialState);
		if (!_hScore)
			break;
		test();
	}
}

int main(int argc, char **argv)
{
	vector<vector<int> > grid;

	if (argc != 2)
	{
		cout << "invalid argument\n";
		return 1;
	}
	grid = getGrid1(argv[1]);
	Manhattan	man(grid);
	man.solve();
}