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

std::ostream& operator<<(std::ostream& os, const Argument& arg) {
	os << arg.getStrValue();
	return os;
}

class Parser {
	private:
		std::map <std::string, int> to_parse;
		std::map <std::string, int> to_parse_positional;
		std::map <std::string, int>::iterator to_parse_positional_it;
		std::map <std::string, Argument*> option_args;
		std::map <std::string, Argument*> positional_args;

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
			if(to_parse_positional_it == to_parse_positional.end())
				throw (std::invalid_argument("Too many positional arguments"));
			positional_args[to_parse_positional_it->first] = new String(value);
			std::cout << positional_args[to_parse_positional_it->first] << std::endl;
			to_parse_positional_it++;
		};
		std::string	parseOption(std::string option) {
			if(option_args.find(option) != option_args.end())
				throw (std::invalid_argument("Duplicate option: " + option));
			if(to_parse[option] == BOOLEAN) {
				option_args[option] = new Boolean(true);
				std::cout << option_args[option] << std::endl;
				return "";
			}
			return option;
		}
		std::string	parseOption(std::string name, std::string value) {
			if(option_args.find(name) != option_args.end())
				throw (std::invalid_argument("Duplicate option: " + name));
			// this function should not be called in case option is boolean
			if(to_parse[name] == INT) {
				option_args[name] = new Int(std::stoi(value));
				std::cout << option_args[name] << std::endl;
			}
			else if(to_parse[name] == STRING) {
				option_args[name] = new String(value);
				std::cout << option_args[name] << std::endl;	
			}
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
		auto	getArg(const std::string& name) const {
			auto args = isOption(name) ? option_args : positional_args;
			for(auto it : args) {
				if(it.first == name)
					return it.second->getRawValue();
			}
			throw ("Argument not found: " + name);
		}
		std::map <std::string, std::variant<int, bool, std::string>> getArgs() const {
			std::map<std::string, Argument*> merged;
			merged.insert(option_args.begin(), option_args.end());
			merged.insert(positional_args.begin(), positional_args.end());
			std::map<std::string, std::variant<int, bool, std::string>> ret;
			for(auto it = merged.begin(); it != merged.end(); it++) {
				if(dynamic_cast<Boolean*>(it->second))
					ret[it->first] =  std::any_cast<bool>(it->second->getRawValue());
				else if(dynamic_cast<Int*>(it->second))
					ret[it->first] =  std::any_cast<int>(it->second->getRawValue());
				else if(dynamic_cast<String*>(it->second))
					ret[it->first] = it->second->getStrValue();
			}
			return ret;
		}
		std::map <std::string, std::string> getArgsStr() const {
			std::map<std::string, Argument*> merged;
			merged.insert(option_args.begin(), option_args.end());
			merged.insert(positional_args.begin(), positional_args.end());
			out("merged: ", merged);
			out("positional args: ", positional_args);
			std::map<std::string, std::string> ret;
			for(auto it = merged.begin(); it != merged.end(); it++) {
				ret[it->first] = it->second->getStrValue();
			}
			return ret;
		}

		void	addArgument(std::string name, int type) {
			if(type < BOOLEAN || type > STRING)
				throw (std::invalid_argument("Use the class's inherent static attributes such as Parser::BOOLEAN, Parser::INT, Parser::STRING"));
			to_parse[name] = type;
			if(!isOption(name))
				to_parse_positional[name] = type;
			
			// if it has default value add here
		};

		void	parseArguments(char **av) {
			std::string temp_option;
			to_parse_positional_it = to_parse_positional.begin();
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
	auto args = parser.getArgsStr();
	os << "Parser: ";
	os << "{";
	if(!args.empty()) {	
		auto last = --args.end();
		for(auto it = args.begin(); it != args.end(); it++) {
			os << "\"" << it->first << "\"" << ": " << it->second;
			if(it != last) {
				os << ",";
			}
		}
	}
	os << "}" << std::endl;
	return os;
}
