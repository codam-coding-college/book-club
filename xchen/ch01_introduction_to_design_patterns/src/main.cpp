#include "./duck/duck.hpp"
#include <iostream>

int main() {
	MallardDuck	mallard;
	RubberdDuck rubber;

	mallard.performFly();
	mallard.performQuack();

	rubber.performFly();
	rubber.performQuack();

}
