#pragma once

#include <iostream>
#include <string>
#include <map>

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
		virtual void setArg() = 0;
};

class Boolean : public Argument {
	private:
		bool arg;
	public:
		Boolean(){};
		Boolean(bool value) 
		{
			arg = value;
		};
		~Boolean(){};
		void setArg(bool value) {
			arg = value;
		}
};

class Int : public Argument {
	private:
		int arg;
	public:
		Int(){};
		Int(int num)
		{
			arg = num;
		};
		~Int(){};
		void setArg(int num) {
			arg = num;
		}
};

class String : public Argument {
	private:
		std::string arg;
	public:
		String(){};
		String(std::string str)
		{};
		~String(){};
		void setArg(std::string str) {
			arg = str;
		}
};

class Parser {
	private:
		// first string is the name of the option / argument, the int is its type
		std::map <std::string, int> to_parse;
		std::map <std::string, Argument*> args;
	public:
		static int BOOLEAN;
		static int INT;
		static int STRING;
		Parser() {
			args = {};
		};
		~Parser() {};
		void	makeArgument(std::string name, int type);
		std::string parseArgument(std::string arg);
};
