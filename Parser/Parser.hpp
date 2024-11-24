#pragma once

#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <variant>

// enum {
// 	BOOLEAN,
// 	// CHAR,
// 	INT,
// 	STRING
// };

class Argument {
	public:
		Argument() {};
		virtual ~Argument() {};
		virtual void setArg(std::string) = 0;
};

class Boolean : public Argument {
	private:
		bool arg;
	public:
		Boolean(){
			arg = false;
		};
		~Boolean(){};
		void setArg(std::string value) override {
			arg = true;
		}
};

class Int : public Argument {
	private:
		int arg;
	public:
		Int(){arg = 0;};
		~Int(){};
		void setArg(std::string value) override {
			arg = std::stoi(value);
		}
};

class String : public Argument {
	private:
		std::string arg;
	public:
		String(){};
		~String(){};
		void setArg(std::string value) override {
			arg = value;
		}
};

class Parser {
	private:
		// first string is the name of the option / argument, the int is its type
		std::map <std::string, int> to_parse;
		// first element is the name, second is the value 
		std::map <std::string, Argument*> args;
	public:
		static const int BOOLEAN = 0;
		static const int INT = 1;
		static const int STRING = 2;
		Parser() {
			args = {};
		};
		~Parser() {};
		void	addArgument(std::string name, int type) {
			if(type < BOOLEAN || type > STRING)
				throw (std::invalid_argument("Use the class's inherent static attributes such as Parser::BOOLEAN, Parser::INT, Parser::STRING"));

			std::pair<std::string, Argument*> pair;
			pair.first = name;
			switch (type)
			{
				case BOOLEAN:
					pair.second = new Boolean;
					break;
				case INT:
					pair.second = new Int;
					break;
				case STRING:
					pair.second = new String;
				default:
					break;
			}
		};
		void	parseArgument(std::string arg) {
			if(args.find(arg) == args.end())
				throw (std::invalid_argument("Argument not found"));
			args[arg]->setArg(arg);
		};
};
