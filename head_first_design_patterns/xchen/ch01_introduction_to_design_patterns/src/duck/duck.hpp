#pragma once
#include <string>

/*********************************/
/**				fly				**/
/*********************************/
class FlyBehavior {
	public:
		virtual void	fly() = 0;
		virtual ~FlyBehavior() {};
};

class FlyWithWings : public FlyBehavior {
	public:
		void	fly();
};

class FlyNoWay : public FlyBehavior {
	public:
		void	fly();
};

/*********************************/
/**				quack			**/
/*********************************/
class QuackBehavior {
	public:
		virtual void	quack() = 0;
		virtual ~QuackBehavior() {};
};

class Quack : public QuackBehavior {
	public:
		void	quack();
};

class Squeak : public QuackBehavior {
	public:
		void	quack();
};

class MuteQuack : public QuackBehavior {
	public:
		void	quack();
};

/*********************************/
/**				duck			**/
/*********************************/
class Duck {
	public:
		Duck(const std::string& name);
		virtual ~Duck() {};
		void	swim();
		void	display();
		void	performFly();
		void	performQuack();
	protected:
		FlyBehavior*	flyBehavior;
		QuackBehavior*	quackBehavior;
		std::string type;
};

class MallardDuck : public Duck {
	public:
		MallardDuck();
		~MallardDuck();
};

class RubberdDuck : public Duck {
	public:
		RubberdDuck();
		~RubberdDuck();
};
