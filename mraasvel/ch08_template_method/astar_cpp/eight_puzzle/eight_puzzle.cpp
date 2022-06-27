#include "eight_puzzle.hpp"
#include <algorithm>
#include <random>
#include <chrono>

namespace EP {

bool operator==(const State& lhs, const State& rhs) {
	return lhs.grid == rhs.grid;
}

bool operator<(const State& lhs, const State& rhs) {
	return lhs.grid < rhs.grid;
}

void State::find_empty() {
	for (int y = 0; y < 3; ++y) {
		for (int x = 0; x < 3; ++x) {
			if (grid[y * 3 + x] == 0) {
				empty = std::make_pair(x, y);
				return;
			}
		}
	}
	throw std::runtime_error("expected empty square");
}

State State::move(std::pair<int, int> other) const {
	State next = *this;
	next.grid = grid;
	next.empty = other;
	next.cost = cost + 1;
	std::swap(next.grid[empty.second * 3 + empty.first], next.grid[other.second * 3 + other.first]);
	return next;
}

State random_state() {
	State state {};
	for (size_t i = 0; i < state.grid.size(); i++) {
		state.grid[i] = i;
	}
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(state.grid.begin(), state.grid.end(), std::default_random_engine(seed));
	state.find_empty();
	return state;
}

State goal_state() {
	State state {};
	for (size_t i = 0; i < state.grid.size(); i++) {
		state.grid[i] = i;
	}
	state.find_empty();
	return state;
}

EightPuzzle::EightPuzzle()
: Astar(random_state(), goal_state()) {}

size_t EightPuzzle::heuristic(const State& state) {
	size_t score = 0;
	for (int i = 0; i < (int)state.grid.size(); i++) {
		auto val = state.grid[i];
		if (val == 0) {
			continue;
		}
		auto result = abs((i % 3) - (val % 3)) + abs((i/3 - val/3));
		score += result;
	}
	return score + state.cost;
}

std::vector<State> EightPuzzle::expand(const State& state) {
	std::vector<State> result;
	auto x = state.empty.first;
	auto y = state.empty.second;
	visited.insert(state);
	if (y > 0) {
		// up
		result.push_back(state.move(std::make_pair(x, y - 1)));
	}
	if (y < 2) {
		// down
		result.push_back(state.move(std::make_pair(x, y + 1)));
	}
	if (x > 0) {
		// left
		result.push_back(state.move(std::make_pair(x - 1, y)));
	}
	if (x < 2) {
		// right
		result.push_back(state.move(std::make_pair(x + 1, y)));
	}
	return result;
}

bool EightPuzzle::can_add(const State& state) {
	return visited.count(state) == 0;
}

}

std::ostream& operator<<(std::ostream& out, const EP::State& rhs) {
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			std::cout << rhs.grid[y * 3 + x] << ' ';
		}
		std::cout << std::endl;
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, const typename Astar<EP::State>::ScoredState& rhs) {
	out << "{" << std::endl;
	out << "\tScore: " << rhs.score << std::endl;
	out << "\tDepth: " << rhs.depth << std::endl;
	out << rhs.state << std::endl;
	out << "}" << std::endl;
	return out;
}
