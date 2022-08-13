#include <string>

class English {
	public:
		English(std::string name): name(name) {};
		virtual ~English() {};
		virtual void hello();
		std::string	getName() const;
		
	private:
		std::string	name;
};

class French {
	public:
		French(std::string name): name(name) {};
		French(const French& src): name(src.name) {};
		void bonjour();
		std::string	getName() const;

	private:
		std::string	name;
};

class FrenchAdapter: public English {
	public:
		FrenchAdapter(French french): English(french.getName()), french(french) {};
		void hello();

	private:
		French french;
};
