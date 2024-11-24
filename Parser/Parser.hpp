#pragma once

#include "../Printer/Printer.hpp"
#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <variant>
#include <any>

class Argument {
	public:
		Argument() {};
		virtual ~Argument() {};
		virtual void setValue(const std::string& value) = 0;
		virtual std::any getRawValue() const = 0;
		virtual std::string getStrValue() const = 0;
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
		void setValue(const std::string& value) override {
			arg = true;
		}
		std::any getRawValue() const override {
			return arg;
		}
		std::string getStrValue() const override {
			bool raw = std::any_cast<bool>(getRawValue());
			if(raw == true)
				return "true";
			return "false";
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
		void setValue(const std::string& value) override {
			arg = std::stoi(value);
		}
		std::any getRawValue() const override {
			return arg;
		}
		std::string getStrValue() const override {
			int raw = std::any_cast<int>(getRawValue());
			return std::to_string(raw);
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
		void setValue(const std::string& value) override {
			arg = value;
		}
		std::any getRawValue() const override {
			return arg;
		}
		std::string getStrValue() const override {
			return std::any_cast<std::string>(getRawValue());
		}
};

class Parser {
	private:
		std::map <std::string, int> to_parse;
		std::map <std::string, Argument*> args;
	public:
		static const int BOOLEAN = 0;
		static const int INT = 1;
		static const int STRING = 2;
 		Parser() {
			out("constructor called");
			args = {};
		};
		~Parser() {
			for (auto it = args.begin(); it != args.end(); it++) {
				delete it->second;
			}
		};
		void	printArgs() {
			for (auto it = args.begin(); it != args.end(); it++) {
				std::cout << "deleting " << it->first << std::endl;
				std::cout << "second: " << it->second->getStrValue() << std::endl;
			}
		}
		std::map <std::string, int> getToParse() const {
			return to_parse;
		}
		std::map <std::string, Argument*> getArgs() const {
			return args;
		}
		bool	isOption(std::string elem) const {
			if(elem.find("--") != std::string::npos)
				return true;
			if(elem.find("-") != std::string::npos)
				return true;
			return false;
		}
		void	addArgument(std::string name, int type) {
			if(type < BOOLEAN || type > STRING)
				throw (std::invalid_argument("Use the class's inherent static attributes such as Parser::BOOLEAN, Parser::INT, Parser::STRING"));
			to_parse[name] = type;
		};
		void updateItOption(std::map<std::string, int>::iterator& it, std::string key) {
			while(it != to_parse.end() && it->first != key)
				it++;
			if(it == to_parse.end())
				throw std::out_of_range(key + " is not a valid argument, verify the order of arguments");
			out("updateItOption: ", it->first);
		}
		void	parseArg(std::string name, std::string value) {
			args[name]->setValue(value);
		};
		std::string	parseOption(std::string option) {
			if(to_parse[option] == BOOLEAN) {
				args[option] = new Boolean(true);
				return "";
			}
			return option;
		}
		std::string	parseOption(std::string name, std::string value) {
			// this function should not be called in case option is boolean
			if(to_parse[name] == INT)
				args[name] = new Int(std::stoi(value));
			else if(to_parse[name] == STRING)
				args[name] = new String(value);
			return "";
		}
		void	parseArguments(char **av) {
			std::string temp_option;
			auto it = to_parse.begin();
			out("to_parse: ", to_parse);
			for (int i = 1; av[i]; i++) {
				std::string elem(av[i]);
				out("elem: ",elem);
				if(isOption(elem)) {
					updateItOption(it, elem);
					temp_option = parseOption(elem);
					continue;
				}
				if(temp_option != "") {
					updateItOption(it, temp_option);
					temp_option = parseOption(temp_option, elem);
				}
				else {
					parseArg(it->first, elem);
					it++;
				}
			}
		};
};

std::ostream& operator<<(std::ostream& os, const Parser& parser) {
	auto args = parser.getArgs();
	os << "Parser: ";
	os << "{";
	if(!args.empty()) {	
		auto last = --args.end();
		for(auto it = args.begin(); it != args.end(); it++) {
			os << "\"" << it->first << "\"" << ": " << it->second->getStrValue();
			if(it != last) {
				os << ",";
			}
		}
	}
	os << "}" << std::endl;
	return os;
}
