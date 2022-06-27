#pragma once

#include "heap.hpp"
#include <exception>
#include <limits>
#include <cstdio>
#include <iostream>

template <typename S, typename Compare = std::greater<size_t>>
class Astar {
public:

	using State = S;

public:

	struct ScoredState {
		ScoredState() = default;
		ScoredState& operator=(const ScoredState&) = default;

		ScoredState(const ScoredState&) = default;
		ScoredState(ScoredState&& ss): state(std::move(ss.state)), score(ss.score), depth(ss.depth) {}
		ScoredState(State&& s, size_t score, size_t depth): state(s), score(score), depth(depth) {}

		State state;
		size_t score;
		size_t depth;
	};

private:

	struct ScoredStateCompare {
		bool operator()(const ScoredState& a, const ScoredState& b) {
			return Compare()(a.score, b.score);
		}
	};

public:

	Astar(State initial, State goal, size_t max_depth = std::numeric_limits<size_t>::max())
	: goal(goal), best(std::move(initial), 0, 0), max_depth(max_depth) {}

	virtual ~Astar() {}

	ScoredState solve() {
		best.score = heuristic(best.state);
		pq.emplace(best);
		while (!pq.empty()) {
			const ScoredState& top = pq.top();
			if (top.state == goal) {
				return top;
			}
			if (Compare()(best.score, top.score)) {
				best = top;
			}
			if (top.depth == max_depth) {
				pq.pop();
				continue;
			}
			size_t depth = top.depth;
			std::vector<State> states = expand(top.state);
			pq.pop();
			for (auto&& state: states) {
				if (can_add(state)) {
					size_t score = heuristic(state);
					ScoredState next { std::move(state), score, depth + 1 };
					pq.emplace(next);
				}
			}
			std::cout << pq.size() << std::endl;
		}
		return best;
	}

private:

	virtual size_t heuristic(const State& state) = 0;
	virtual std::vector<State> expand(const State& state) = 0;
	virtual bool can_add(const State& state) {
		return true;
	}

private:
	DSA::Heap<ScoredState, std::vector<ScoredState>, ScoredStateCompare> pq;
	State goal;
	ScoredState best;
	size_t max_depth;
};
