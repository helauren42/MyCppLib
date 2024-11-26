#include "../Printer.hpp"
#include <iostream>
#include <string>
#include <map>

class SimpleBase {
	protected:
		int num;
	public:
		SimpleBase() {}
		virtual ~SimpleBase() {}
		int getNum() const {return num;}
};

class Simple1 : public SimpleBase {
	public:
		Simple1() {num = 30;};
};

class Simple2 : public SimpleBase {
	public:
		Simple2() {num = 50;};
};

std::ostream& operator<<(std::ostream& os, const SimpleBase* arg) {
	os << arg->getNum();
	return os;
}

int main() {
	std::map<std::string, SimpleBase*> args;
	args["1"] = new Simple1();
	args["222"] = new Simple2();
	out("\n\nargs: ", args, "\n\n");
	for (auto& pair : args)
	    delete pair.second;
	return 0;
}
