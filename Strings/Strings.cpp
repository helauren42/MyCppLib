#include "Strings.hpp"

bool	isWhiteSpace(const char& c) {
	const std::string white_spaces = WHITE_SPACES;

	if(white_spaces.find(c) != std::string::npos)
		return true;
	return false;
}

bool hasDelim(const std::string& str, const char& delimiter) {
    return str.find(delimiter) != std::string::npos;
}

bool hasDelim(const std::string& str, const std::string& delimiter) {
    return str.find_first_of(delimiter) != std::string::npos;
}


template<typename Container>
std::string joinStrings(const Container& container, const std::string& sep = " ") {
	std::string ret;
	for (auto it : container) {
		ret += it;
		ret += sep;
	}
	ret = ret.substr(0, ret.length() - sep.length());
	return ret;
}


std::string joinStrings(std::queue<std::string>& container, const std::string& sep = " ") {
	std::string ret;
	while (!container.empty()) {
		ret += container.front();
		container.pop();
	}
	ret = ret.substr(0, ret.length() - sep.length());
	return ret;
}


std::string joinStrings(std::stack<std::string>& container, const std::string& sep = " ") {
	std::string ret;
	while (!container.empty()) {
		ret += container.top();
		container.pop();
	}
	ret = ret.substr(0, ret.length() - sep.length());
	return ret;
}


template <typename Container> 
Container split(const std::string& str, const std::string& delimiter = "\n") {
	std::vector<std::string> container;

	size_t start = 0;
	size_t end = 0;

	while(true) {
		if((start = str.find_first_not_of(delimiter, start)) == std::string::npos)
			break;
		end = str.find_first_of(delimiter, start);
		if(end == std::string::npos)
			end = str.length();
		container.push_back(str.substr(start, end - start));
		start = end+1;
	}
	return(container);
}


template<typename Container>
Container splitKeep(const std::string& str, const std::string& delimiter = "\n") {
	std::vector<std::string> container;

	size_t	start = 0;
	size_t	end = 0;
	bool	isDelimiter = delimiter.find(str[0]) != std::string::npos;

	while(true) {
		
		if(isDelimiter) {
			end = str.find_first_not_of(delimiter, start);
		}
		else if (!isDelimiter) {
			end = str.find_first_of(delimiter, start);
		}
		if(end == std::string::npos)
			end = str.length();

		container.push_back(str.substr(start, end - start));
		if(!str[end+1])
			break;
		isDelimiter = delimiter.find(str[end]) != std::string::npos;
		start = end;
		if(start >= str.length())
			break;
	}

	std::vector<std::string> cont2;
	std::string temp;
	for(auto it = container.begin(); it != container.end(); it++) {
		if(hasDelim(*it, delimiter)) {
		}
		else {
			temp = "";
		}
	}
	if(temp != "")
		cont2.push_back(temp);
	return cont2;
}


std::string toLowerCase(const std::string& str) {
	std::string result = str;
	std::string upper_case = UPPER_CASE;
	for (char& c : result) {
		if(upper_case.find(c) != std::string::npos)
			c = std::tolower(c);
	}
	return result;
}


std::string toUpperCase(const std::string& str) {
	std::string result = str;
	std::string lower_case = LOWER_CASE;
	
	for (char& c : result) {
		if(lower_case.find(c) != std::string::npos)
			c = std::toupper(c);
	}
	return result;
}

std::string	toCamelCase(const std::string& str, const int& mode = spaceSeparated) {
	std::string ret;
	if(mode == camelCase)
		return(ret = str, ret);

	ret = toLowerCase(str);
	std::string delimiter = [mode]() -> std::string {
		if (mode == kebabCase) return "-";
		if (mode == snakeCase) return "_";
		return WHITE_SPACES;
	}();

	std::vector<std::string> vec = split<std::vector<std::string>>(ret, delimiter);

	for(auto it = vec.begin(); it != vec.end(); it++) {
		if((*it)[0])
			(*it)[0] = std::toupper((*it)[0]);
	}
	ret = joinStrings(vec, "");
	ret[0] = std::tolower(ret[0]);
	return ret;
}

std::string	toSnakeCase(const std::string& str, const int& mode = spaceSeparated) {
	std::string ret;
	if(mode == snakeCase)
		return(ret = str, ret);

	ret = str;
	std::string delimiter = [mode]() -> std::string {
		if (mode == camelCase) return UPPER_CASE;
		if (mode == kebabCase) return "-";
		return WHITE_SPACES;
	}();

	std::vector<std::string> vec;
	if(mode == camelCase)
		vec = splitKeep<std::vector<std::string>>(ret, delimiter);
	else
		vec = split<std::vector<std::string>>(ret, delimiter);

	ret = joinStrings(vec, "_");
	ret = toLowerCase(ret);
	return ret;
}

std::string	toKebabCase(const std::string& str, const int& mode = spaceSeparated) {
	std::string ret;
	if(mode == kebabCase)
		return(ret = str, ret);

	ret = str;
	std::string delimiter = [mode]() -> std::string {
		if (mode == camelCase) return UPPER_CASE;
		if (mode == snakeCase) return "_";
		return WHITE_SPACES;
	}();

	std::vector<std::string> vec;
	if(mode == camelCase)
		vec = splitKeep<std::vector<std::string>>(ret, delimiter);
	else
		vec = split<std::vector<std::string>>(ret, delimiter);

	ret = joinStrings(vec, "-");
	ret = toLowerCase(ret);
	return ret;
}


std::string lstrip(const std::string& str, const std::string& remove = WHITE_SPACES) {
	size_t i = 0;

	while(i < str.length()) {

		size_t found = remove.find(str[i]);
		if(found ==  std::string::npos) {
			break;
		}
		i++;
	}

	std::string ret = str.substr(i, str.length() - i);
	return ret;
}


std::string rstrip(const std::string& str, const std::string& remove = WHITE_SPACES) {
	int i = str.length() - 1;

	while(i >= 0) {
		if(remove.find(str[i]) == std::string::npos)
			break;
		i--;
	}

	std::string ret = str.substr(0, i +1);
	return ret;
}


std::string strip(const std::string& str, const std::string& remove = WHITE_SPACES) {
	std::string ret = lstrip(str, remove);
	ret = rstrip(ret, remove);
	return ret;
}


void	replaceAll(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;

	while (true) {
		start_pos = str.find(from, start_pos);
		if (start_pos == std::string::npos)
			break;
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}


void	removeAll(std::string& str, const std::string& remove) {
	replaceAll(str, remove, "");
}

bool	stringCompareIgnoreCase(const std::string& s1, const std::string& s2) {
	std::string lower_s1 = toLowerCase(s1);
	std::string lower_s2 = toLowerCase(s2);

	return lower_s1 == lower_s2;
}

