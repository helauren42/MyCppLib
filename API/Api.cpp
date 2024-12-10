#include "Api.hpp"


std::string HttpResponse::getVersion() const { return this->version; };
std::string HttpResponse::getStatusCode() const { return this->status_code; };
std::string HttpResponse::getStatusMessage() const { return this->status_message; };
std::map<std::string, std::string> HttpResponse::getHeaders() const { return this->headers; };
std::string HttpResponse::getBody() const { return this->content_string; };
std::map<std::string, std::string> HttpResponse::getBodyJson() const { return this->content_json; };

void HttpResponse::setVersion(const std::string& version) { this->version = version; };
void HttpResponse::setStatusCode(const std::string& status_code) { this->status_code = status_code; };
void HttpResponse::setStatusMessage(const std::string& status_message) { this->status_message = status_message; };

void HttpResponse::addHeader(const std::string& key, const std::string& value) { this->headers[key] = value; };

void HttpResponse::addHeaders(std::vector<std::string>::const_iterator begin, const std::vector<std::string>::const_iterator end) {
	while (begin != end)
	{
		std::string line = strip(*begin);
		size_t sep = line.find_first_of(":");
		if(line != "") {
			std::string key = line.substr(0, sep);
			std::string value = line.substr(sep + 1);
			addHeader(key, value);
		}
		begin++;
	}
}

ElemPos nextElement(const std::string& s, size_t start) {
	ElemPos pos;
	pos.start = s.find('"', start);
	if(pos.start == std::string::npos)
		return pos;
	pos.end = s.find('"', pos.start + 1);
	return pos;
}

void HttpResponse::parseBody(const std::string& body) {
	if(body[0] != '{' || body.back() != '}')
		throw (std::invalid_argument("Invalid HTTP response: " + body));
	content_string = strip(body);

	std::cout << "should be like body: " << content_string << std::endl;
	if(content_string == "{}") // empty response
	{
		content_string = "";
		return;
	}
	ElemPos pos;
	ElemType type = KEY;
	std::string key;
	std::string value;
	while(true) {
		pos = nextElement(body, pos.start);
		if(pos.start == std::string::npos || pos.end == std::string::npos)
			break;
		std::cout << "start: " << pos.start << " end: " << pos.end << std::endl;
		const std::string& word = body.substr(pos.start, pos.end - pos.start);

		if(type == KEY)
			key = word;
		else {
			value = word;
			content_json[key] = value;
		}
		type = type == KEY ? VALUE : KEY;
		pos.start = pos.end + 1;
	}
	std::cout << "so are you like body: " << content_string << std::endl;
}

void HttpResponse::parseHeader(const std::string& input) {
	std::vector<std::string> elements = split<std::vector<std::string>>(input, " ");
	if(elements.size() < 3)
		throw (std::invalid_argument("Invalid HTTP response: " + input));
	setVersion(elements[0]);
	setStatusCode(elements[1]);
	setStatusMessage(elements[2]);
}

void HttpResponse::parse(const std::string& input) {
	std::vector<std::string> lines = split<std::vector<std::string>>(input);
	if(lines.size() < 4)
		throw (std::invalid_argument("Invalid HTTP response: " + input));
	parseHeader(lines[0]);
	addHeaders(lines.cbegin() +1, lines.cend() - 1);
	std::cout << "should be body: " << *(lines.end() -1) << std::endl;
	parseBody(*(lines.end() -1));
}

std::ostream& operator<<(std::ostream& os, const HttpResponse& response) {
	os << "Version: " << response.getVersion() << std::endl;
	os << "Status Code: " << response.getStatusCode() << std::endl;
	os << "Status Message: " << response.getStatusMessage() << std::endl;
	os << "Headers: " << std::endl;
	auto headers = response.getHeaders();
	for(auto it = headers.begin(); it != headers.end(); it++) {
		os << it->first << ": " << it->second << std::endl;
	}
	os << "Body: " << response.getBody() << std::endl;
	auto json = response.getBodyJson();
	os << "Body Json: " << std::endl;
	for (auto it = json.begin(); it != json.end(); it++) {
		os << "{" << it->first << ": " << it->second << "}" << std::endl;
	}
	return os;
}
