#pragma once

#include <queue>
#include <exception>
#include <limits>

template <typename S>
class Astar {
public:

	using State = S;

public:

	struct ScoredState {
		ScoredState(ScoredState&& ss): state(std::move(ss.state)), score(ss.score), depth(ss.depth) {}
		ScoredState(State&& s, size_t score, size_t depth): state(s), score(score), depth(depth) {}
		State state;
		size_t score;
		size_t depth;
	};

private:

	struct ScoredStateCompare {
		bool operator()(const ScoredState& a, const ScoredState& b) {
			return a.score < b.score;
		}
	};

public:

	Astar(State initial, State goal): goal(std::move(goal)) {
		best.score = std::numeric_limits<size_t>::max();
		pq.emplace(std::move(initial), 0, 0);
	}

	ScoredState solve(State initial, State goal, size_t max_depth = std::numeric_limits<size_t>::max()) {
		while (!pq.empty()) {
			const ScoredState& top = pq.top();
			if (top.state == goal) {
				return top;
			}
			if (top.depth == max_depth) {
				pq.pop();
				continue;
			}
			size_t depth = top.depth;
			std::vector<State> states = expand(top);
			pq.pop();
			for (State&& state: states) {
				if (can_add(state)) {
					size_t score = heuristic(state);
					ScoredState next { state, score, depth + 1 };
					if (next.score < best.score) {
						best = next;
					}
					pq.emplace(next);
				}
			}
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
	std::priority_queue<ScoredState, ScoredStateCompare> pq;
	State goal;
	ScoredState best;
};
