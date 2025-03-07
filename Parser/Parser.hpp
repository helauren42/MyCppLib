#pragma once

#include "../Printer/Printer.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <variant>
#include <any>
#include <cstring>

class Argument {
	public:
		Argument() {};
		virtual ~Argument() {};
		virtual void setValue(const std::string& value) = 0;
		virtual std::any getRawValue() const = 0;
		virtual std::string getStrValue() const = 0;
};

std::ostream& operator<<(std::ostream& os, const Argument* arg) {
	os << arg->getStrValue();
	return os;
}

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
		Boolean(const bool&& value){
			arg = value;
		};
		Boolean(const std::string& value){
			setValue(value);
		};
		~Boolean(){};
		void setValue(const std::string& value) override {
			if(value == "false" || value == "0")
				arg = false;
			else
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
		Int(const std::string& value){
			setValue(value);
		};
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

class Double : public Argument {
	private:
		double arg;
	public:
		Double(){arg = 0;};
		Double(const double& value)
		{
			arg = value;
		};
		Double(const std::string& value){
			setValue(value);
		};
		~Double(){};
		void setValue(const std::string& value) override {
			arg = std::stod(value);
		}
		std::any getRawValue() const override {
			return arg;
		}
		std::string getStrValue() const override {
			double raw = std::any_cast<double>(getRawValue());
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
		std::map<std::string, Argument*> default_values;
		std::map<std::string, int> to_parse;
		std::map<std::string, int> to_parse_positional;
		std::map<std::string, int>::iterator to_parse_positional_it;
		std::map<std::string, Argument*> option_args;
		std::map<std::string, Argument*> positional_args;

		std::map<std::string, int> getToParse() const {
			return to_parse;
		}
		bool	isOption(std::string elem) const {
			if(elem.find("--") != std::string::npos)
				return true;
			if(elem.find("-") != std::string::npos)
				return true;
			return false;
		}

	/// @brief Check if the given type is valid
	///
	/// @details Throw a std::invalid_argument if the type is not valid.
	/// The type must be one of Parser::BOOLEAN, Parser::INT, Parser::STRING.
		void	checkType(int type) const {
			if(type < BOOLEAN || type > STRING)
				throw (std::invalid_argument("Use the class's inherent static attributes such as Parser::BOOLEAN, Parser::INT, Parser::STRING"));
		}
		void	parseArg(std::string value) {
			if(to_parse_positional_it == to_parse_positional.end())
				throw (std::invalid_argument("Invalid argument: " + value));
			if(default_values.find(to_parse_positional_it->first) != default_values.end())
					delete default_values[to_parse_positional_it->first];
			positional_args[to_parse_positional_it->first] = new String(value);
			to_parse_positional_it++;
		};
		std::string	parseOption(std::string option) {
			std::vector<std::string> options;

			if(option_args.find(option) != option_args.end())
				throw (std::invalid_argument("Duplicate option: " + option));
			if(to_parse[option] == BOOLEAN) {
				if(option_args.find(option) != option_args.end())
					delete option_args[option];
				option_args[option] = new Boolean(true);
				return "";
			}
			return option;
		}
		// this function should not be called in case option is boolean
		std::string	parseOption(std::string name, std::string value) {
			if(option_args.find(name) != option_args.end())
				throw (std::invalid_argument("Duplicate option: " + name));
		
			if(option_args.find(name) != option_args.end())
					delete option_args[name];
			
			if(to_parse[name] == INT) {
				option_args[name] = new Int(std::stoi(value));
			}
			if(to_parse[name] == DOUBLE) {
				option_args[name] = new Double(std::stod(value));
			}
			else if(to_parse[name] == STRING) {
				option_args[name] = new String(value);
			}
			
			return "";
		}
		void	addDefaultValues() {
			std::map<std::string, Argument*> merged;
			merged.insert(option_args.begin(), option_args.end());
			merged.insert(positional_args.begin(), positional_args.end());
			for(auto it = default_values.begin(); it != default_values.end(); it++) {
				if(merged.find(it->first) == merged.end()) {
					auto& arg = isOption(it->first) ? option_args : positional_args;
					arg[it->first] = it->second;
				}
			}
		}
		std::vector<std::string> splitArguments(char **av) {
			std::vector<std::string> ret;
			std::string dash = "-";
			for (int i = 1; av[i]; i++) {
				if (strlen(av[i]) > 2 && av[i][0] == '-' && av[i][1] != '-') {
					for(int j = 1; av[i][j]; j++) {
						char temp = av[i][j];
						ret.push_back(dash + temp);
					}
				}
				else
					ret.push_back(av[i]);
			}
			return ret;
		}

		void	checkPositional() {
			for(auto it = to_parse_positional.begin(); it != to_parse_positional.end(); it++) {
				if(positional_args.find(it->first) == positional_args.end())
					throw std::runtime_error("Positional argument not found: " + it->first);
			}
		}

	public:
		static const int BOOLEAN = 0;
		static const int INT = 1;
		static const int DOUBLE = 2;
		static const int STRING = 3;
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

		template <typename T>
		auto getArg(const std::string& _name) {
			std::string name = _name;
			std::map<std::string, Argument*> args = isOption(name) ? option_args : positional_args;
			if(args.find(name) == args.end())
				args = default_values;
			for (const auto& it : args) {
				if (it.first == name) {
					return std::any_cast<T>(it.second->getRawValue());
				}
			}
			throw std::runtime_error("Argument not found: " + name);
		}

		template <typename T>
		auto getArg(const char* _name) {
			std::string name = _name;
			std::map<std::string, Argument*> args = isOption(name) ? option_args : positional_args;
			for (const auto& it : args) {
				if (it.first == name) {
					return std::any_cast<T>(it.second->getRawValue());
				}
			}
			throw std::runtime_error("Argument not found: " + name);
		}

		std::map <std::string, std::variant<bool, int, double, std::string>> getArgs() const {
			std::map<std::string, Argument*> merged;
			merged.insert(option_args.begin(), option_args.end());
			merged.insert(positional_args.begin(), positional_args.end());
			std::map<std::string, std::variant<bool, int, double, std::string>> ret;
			for(auto it = merged.begin(); it != merged.end(); it++) {
				if(dynamic_cast<Boolean*>(it->second))
					ret[it->first] =  std::any_cast<bool>(it->second->getRawValue());
				else if(dynamic_cast<Int*>(it->second))
					ret[it->first] =  std::any_cast<int>(it->second->getRawValue());
				else if(dynamic_cast<Int*>(it->second))
					ret[it->first] =  std::any_cast<double>(it->second->getRawValue());
				else if(dynamic_cast<String*>(it->second))
					ret[it->first] = it->second->getStrValue();
			}
			return ret;
		}

		std::map <std::string, std::string> getArgsStr() const {
			std::map<std::string, Argument*> merged;
			merged.insert(option_args.begin(), option_args.end());
			merged.insert(positional_args.begin(), positional_args.end());
			std::map<std::string, std::string> ret;
			for(auto it = merged.begin(); it != merged.end(); it++) {
				ret[it->first] = it->second->getStrValue();
			}
			return ret;
		}

		void	addArgument(std::string name, int type) {
			checkType(type);
			to_parse[name] = type;
			if(default_values.find(name) != default_values.end())
				delete default_values[name];
			if(isOption(name) && type == BOOLEAN) {
				default_values[name] = new Boolean(false);
			}
			if(!isOption(name))
				to_parse_positional[name] = type;
		};

		template <typename T>
		void	addArgument(std::string name, int type, T _default_value) {
			checkType(type);
			std::string default_value;
			if constexpr (std::is_same<T, std::string>::value || std::is_same<T, const char *>::value
			|| std::is_same<T, char *>::value || std::is_same<T, const std::string>::value)
				default_value = _default_value;
			else
				default_value = std::to_string(_default_value);
			to_parse[name] = type;
			
			auto& args =  isOption(name) ? option_args : positional_args;
			if(!isOption(name))
				to_parse_positional[name] = type;

			if(args.find(name) != args.end())
				delete args[name];
			if(type == BOOLEAN) {
				args[name] = new Boolean(default_value);
			}
			else if(type == INT) {
				args[name] = new Int(default_value);
			}
			else if(type == DOUBLE) {
				args[name] = new Double(default_value);
			}
			else if(type == STRING) {
				args[name] = new String(default_value);
			}
		};

		void	parseArguments(char **av) {
			std::string temp_option = "";
			to_parse_positional_it = to_parse_positional.begin();
			std::vector<std::string> args = splitArguments(av);
			for (auto& elem : args) {;
				if(temp_option != "") {
					temp_option = parseOption(temp_option, elem);
				}
				else if(isOption(elem)) {
					temp_option = parseOption(elem);
					continue;
				}
				else {
					parseArg(elem);
				}
			}
			// addDefaultValues();
			checkPositional();
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
				os << ", ";
			}
		}
	}
	os << "}" << std::endl;
	return os;
}
