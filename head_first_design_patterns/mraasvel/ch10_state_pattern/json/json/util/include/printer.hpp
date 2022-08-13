#pragma once

namespace util {

class Printer {
	public:
		Printer();
		Printer(const Printer&);
		Printer(Printer&&);
		Printer& operator=(const Printer&);
		Printer& operator=(Printer&&);
		~Printer();
};

}
