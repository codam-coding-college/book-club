#ifndef STATE_PARSER_HPP
#define STATE_PARSER_HPP

#include <string>

using namespace std;

// An abstract class template that defines the state parsing algorithm
// as a template method, complete with hooks and abstract methods to be
// implemented by the subclasses.
// `State` template parameter refers to type of states, e.g. an enum.
// The state parsing algorithm itself is made for parsing strings byte-by-byte.
template <typename State>
class StateParser {
	public:
		// template method
		void	ParseString(string const& input_string) {
			size_t pos = 0;

			input = input_string;
			CheckPreParse();
			cur_state = SetStartState();
			while (NotDone(pos)) {
				cur_state = GetNextState(pos);
				CheckStateInvalid();
				if (CheckStateDone())
					break;
				UpdateBuffer(pos);
				IncrementCounter(pos);
			}
			CheckAfterParse(pos);
		}

	protected:
		State	cur_state;
		string	buffer; // for keeping track of parsed input
		string	input; // saving original input

		// Abstract methods that must be implemented by subclass.
		virtual State	SetStartState() const = 0;
		virtual State	GetNextState(size_t pos) = 0;
		virtual void	CheckStateInvalid() const = 0;
		virtual bool	CheckStateDone() = 0;

		// Concrete methods that can be overridden if custom looping behaviour is needed.
		virtual void	UpdateBuffer(size_t pos) {
			buffer += input[pos];
		}
		virtual bool	NotDone(size_t pos) const {
			return (pos <= input.size()); // note that this reads until the last \0 character
		}
		virtual void	IncrementCounter(size_t& pos) {
			pos += 1;
		}

		// Hooks. Optional extensions points where subclasses can add actions.
		// They can be overriden by subclasses, but it's not mandatory since
		// the hooks already have default (but empty) implementation.
		// This is for checks before entering parsing loop, e.g. if input string exceeds max allowed size.
		virtual void	CheckPreParse() {};
		// This is for checks after parsing, e.g. if there are characters after end state has been reached.
		virtual void	CheckAfterParse(size_t pos) { (void)pos; };
};

#endif // STATE_PARSER_HPP
