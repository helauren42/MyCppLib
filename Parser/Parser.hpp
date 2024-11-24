#pragma once

#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <variant>
#include <any>

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
		virtual void setValue(std::string) = 0;
		virtual std::any getRawValue() const = 0;

		template<typename T>
		T getValue(){
			return std::any_cast<T>(getRawValue());
		};
};

class Boolean : public Argument {
	private:
		bool arg;
	public:
		Boolean(){
			arg = false;
		};
		Boolean(const bool& value){
			arg = value;
		};
		~Boolean(){};
		void setValue(std::string value) override {
			arg = true;
		}
		std::any getRawValue() const override {
			return arg;
		}
};

class Int : public Argument {
	private:
		int arg;
	public:
		Int(){arg = 0;};
		Int(const int& value)
		{arg = value;};
		~Int(){};
		void setValue(std::string value) override {
			arg = std::stoi(value);
		}
		std::any getRawValue() const override {
			return arg;
		}
};

class String : public Argument {
	private:
		std::string arg;
	public:
		String(){};
		String(const std::string& value) {
			arg = value;
		};
		~String(){};
		void setValue(std::string value) override {
			arg = value;
		}
		std::any getRawValue() const override {
			return arg;
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
		~Parser() {
			for (auto it = args.begin(); it != args.end(); it++)
				delete it->second;
		};
		bool	isOption(std::string elem) {
			if(elem.starts_with("-") || elem.starts_with("--"))
				return true;
			return false;
		}
		void	addArgument(std::string name, int type) {
			if(type < BOOLEAN || type > STRING)
				throw (std::invalid_argument("Use the class's inherent static attributes such as Parser::BOOLEAN, Parser::INT, Parser::STRING"));
			to_parse[name] = type;
		};
		auto updateIt(std::map<std::string, int>::iterator it, std::string key) {
			while(it != to_parse.end() && it->first != key)
				it++;
			if(it == to_parse.end())
				throw std::out_of_range(key + " is not a valid argument");
		}
		void	parseArgument(std::string name, std::string value) {
			if(args.find(name) == args.end())
				throw (std::invalid_argument("Argument not found"));
			args[name]->setValue(value);
		};
		std::string	parseOption(std::string option) {
			if(to_parse[option] == BOOLEAN) {
				args[option] = new Boolean;
				args[option]->setValue("true");
			}
			return option;
		}
		template<typename T>
		std::string	parseOption(std::string name, T value) {
			// this function should not be called in case option is boolean
			if(to_parse[option] == INT)
				args[option] = new Int(value);
			else(to_parse[option] == STRING)
				args[option] = new String(value);
		}
		void	parseArguments(char **av) {
			std::string temp_option;
			auto it = to_parse.begin();
			for (int i = 1; av[i]; i++) {
				std::string elem(av[i]);
				if(isOption(elem))
					updateIt(it, elem); temp_option = parseOption(elem);	continue;
				if(temp_option != "")
					parseOption(elem);
				temp_option = "";
			}
		};
};
