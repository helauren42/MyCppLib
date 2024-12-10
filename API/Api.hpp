#include "../Printer/Printer.hpp"
#include "../Strings/Strings.hpp"
#include <map>

class HttpResponse {
private:
    std::string version;      
    std::string status_code;   
    std::string status_message;

    // Headers
    std::map<std::string, std::string> headers;   // Key-value pairs for headers
    std::string content_type;       // Content-Type (e.g., "application/json")
    std::string content_length;     // Content-Length (length of body)
    std::string connection;         // Connection header (e.g., "close" or "keep-alive")

    // Body Content
    std::string content_string;               // Raw body content (text or binary)
    std::map<std::string, std::string> content_json; // Parsed JSON content if applicable


	public:
		HttpResponse() {};
		HttpResponse(const std::string& input) {parse(input);};
		~HttpResponse() {};

		void parse(const std::string& input);
		void parseHeader(const std::string& input);
		void parseBody(const std::string& body);

		void setVersion(const std::string& version) { this->version = version; };
		void setStatusCode(const std::string& status_code) { this->status_code = status_code; };
		void setStatusMessage(const std::string& status_message) { this->status_message = status_message; };
		void addHeaders(const std::vector<std::string>::const_iterator begin, const std::vector<std::string>::const_iterator end);
		void addHeader(const std::string& key, const std::string& value) { this->headers[key] = value; };

		std::string getVersion() const { return this->version; };
		std::string getStatusCode() const { return this->status_code; };
		std::string getStatusMessage() const { return this->status_message; };
		std::map<std::string, std::string> getHeaders() const { return this->headers; };
		// std::string getHeader(const std::string key) const { return this->headers[key]; };
		std::string getBody() const { return this->content_string; };
		std::map<std::string, std::string> getBodyJson() const { return this->content_json; };
};

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

struct ElemPos
{
	size_t start = 0;
	size_t end = 0;
};

enum ElemType {
	KEY,
	VALUE
};

ElemPos nextElement(const std::string& s, size_t start) {
	ElemPos pos;
	pos.start = s.find('"', start);
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
	while(pos.start != std::string::npos && pos.end != std::string::npos) {
		pos = nextElement(body, pos.start);
		const std::string& word = body.substr(pos.start, pos.end - pos.start);

		if(type == KEY)
			key = word;
		else {
			value = word;
			content_json[key] = value;
		}
		type = type == KEY ? VALUE : KEY;
		if(pos.start != std::string::npos)
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
	for (auto it = json.begin(); it != json.end(); it++) {
		os << it->first << ": " << it->second << std::endl;
	}
	return os;
}

// class Api {
// 	private:
// 		std::string url;
// 		std::string method;
// 		std::string content_type;
// 		std::string content_length;
// 		std::string content_text;
// 		std::string content_json;
// 	public:
// 		Api();
// 		void setUrl(std::string url);
// 		void setMethod(std::string method);
// 		void setContentType(std::string content_type);
// 		void setContentLength(std::string content_length);
// 		void setContentText(std::string content_text);
// 		void setContentJson(std::string content_json);
// 		std::string getUrl();
// 		std::string getMethod();
// 		std::string getBodyType();
// 		std::string getBodyLength();
// 		std::string getBodyText();
// 		std::string getBodyJson();
// };
