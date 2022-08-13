#pragma once

#include "astar.hpp"
#include <array>
#include <set>
#include <memory>

namespace EP {
struct State {
	size_t cost;
	std::pair<int, int> empty;
	std::array<int, 9> grid;

	void find_empty();
	State move(std::pair<int, int> other) const;
};

bool operator==(const State& lhs, const State& rhs);
bool operator<(const State& lhs, const State& rhs);

class EightPuzzle: public Astar<State> {
public:
	EightPuzzle();

private:
	size_t heuristic(const State& state);
	std::vector<State> expand(const State& state);
	bool can_add(const State& state);
	std::set<State> visited;
};

}

std::ostream& operator<<(std::ostream& out, const EP::State& rhs);
std::ostream& operator<<(std::ostream& out, const typename Astar<EP::State>::ScoredState& rhs);
