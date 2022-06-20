#include "duck.hpp"
#include "../utility/color.hpp"
#include <iostream>

/*********************************/
/**				fly				**/
/*********************************/
void	printAction(const std::string& action) {
	std::cout << BLUE_BOLD << action << RESET_COLOR << '\n';
}

void	FlyWithWings::fly() { printAction(" is FLYing"); }
void	FlyNoWay::fly() { printAction(" cannot fly"); }

/*********************************/
/**				quack			**/
/*********************************/
void	Quack::quack() { printAction(" is QUACKking"); }
void	Squeak::quack() { printAction(" is SQUEACKing"); }
void	MuteQuack::quack() { printAction(" is silient"); }

/*********************************/
/**				duck			**/
/*********************************/
Duck::Duck(const std::string& name): flyBehavior(NULL), quackBehavior(NULL), type(name) {}
void	Duck::display() { std::cout << MAGENTA_BOLD << type << RESET_COLOR; }
void	Duck::performFly() { display(); flyBehavior->fly(); }
void	Duck::performQuack() { display(); quackBehavior->quack(); }

MallardDuck::MallardDuck(): Duck("Mallard Duck") {
	flyBehavior = new FlyWithWings();
	quackBehavior = new Quack();
}
MallardDuck::~MallardDuck() {
	delete flyBehavior;
	delete quackBehavior;
}

RubberdDuck::RubberdDuck(): Duck("Rubber Duck") {
	flyBehavior = new FlyNoWay();
	quackBehavior = new MuteQuack();
}
RubberdDuck::~RubberdDuck() {
	delete flyBehavior;
	delete quackBehavior;
}
