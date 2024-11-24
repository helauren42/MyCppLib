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
		std::map <std::string, Argument*> option_args;
		std::map <std::string, Argument*> positional_args;
		std::map <std::string, Argument*>::iterator positional_args_it;

		void	printArgs() {
			for (auto it = option_args.begin(); it != option_args.end(); it++) {
				std::cout << "deleting " << it->first << std::endl;
				std::cout << "second: " << it->second->getStrValue() << std::endl;
			}
			for (auto it = positional_args.begin(); it != positional_args.end(); it++) {
				std::cout << "deleting " << it->first << std::endl;
				std::cout << "second: " << it->second->getStrValue() << std::endl;
			}
		}
		std::map <std::string, int> getToParse() const {
			return to_parse;
		}
		bool	isOption(std::string elem) const {
			if(elem.find("--") != std::string::npos)
				return true;
			if(elem.find("-") != std::string::npos)
				return true;
			return false;
		}
		void	parseArg(std::string value) {
			if(positional_args_it == positional_args.end())
				throw (std::invalid_argument("Positional argument not added to parse " + value));
			positional_args[positional_args_it->first] = new String(value);
			positional_args_it++;
		};
		std::string	parseOption(std::string option) {
			if(option_args.find(option) != option_args.end())
				throw (std::invalid_argument("Duplicate option: " + option));
			if(to_parse[option] == BOOLEAN) {
				option_args[option] = new Boolean(true);
				return "";
			}
			return option;
		}
		std::string	parseOption(std::string name, std::string value) {
			if(option_args.find(name) != option_args.end())
				throw (std::invalid_argument("Duplicate option: " + name));
			// this function should not be called in case option is boolean
			if(to_parse[name] == INT)
				option_args[name] = new Int(std::stoi(value));
			else if(to_parse[name] == STRING)
				option_args[name] = new String(value);
			return "";
		}
	public:
		static const int BOOLEAN = 0;
		static const int INT = 1;
		static const int STRING = 2;
 		Parser() {
			to_parse = {};
			option_args = {};
			positional_args = {};
		};
		~Parser() {
			for (auto it = option_args.begin(); it != option_args.end(); it++) {
				delete it->second;
			}
			for (auto it = positional_args.begin(); it != positional_args.end(); it++) {
				delete it->second;
			}
		};
		std::map <std::string, Argument*> getArgs() const {
			std::map<std::string, Argument*> merged;
			merged.insert(option_args.begin(), option_args.end());
			merged.insert(positional_args.begin(), positional_args.end());
			return merged;
		}
		void	addArgument(std::string name, int type) {
			if(type < BOOLEAN || type > STRING)
				throw (std::invalid_argument("Use the class's inherent static attributes such as Parser::BOOLEAN, Parser::INT, Parser::STRING"));
			to_parse[name] = type;
			if(!isOption(name))
				positional_args[name] = nullptr;
		};
		void	parseArguments(char **av) {
			std::string temp_option;
			positional_args_it = positional_args.begin();
			out("to_parse: ", to_parse);
			for (int i = 1; av[i]; i++) {
				std::string elem(av[i]);
				out("elem: ", elem);
				if(isOption(elem)) {
					temp_option = parseOption(elem);
					continue;
				}
				if(temp_option != "") {
					temp_option = parseOption(temp_option, elem);
				}
				else {
					parseArg(elem);
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
