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
		HttpResponse(const std::string& input) {};
		~HttpResponse() {};

		void parse(const std::string& input);
		void parseHeader(const std::string& input);

		void setVersion(const std::string& version) { this->version = version; };
		void setStatusCode(const std::string& status_code) { this->status_code = status_code; };
		void setStatusMessage(const std::string& status_message) { this->status_message = status_message; };
		void addHeaders(const std::vector<std::string>::const_iterator begin, const std::vector<std::string>::const_iterator end);
		void addHeader(const std::string& key, const std::string& value) { this->headers[key] = value; };

};

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
	addHeaders(lines.cbegin(), lines.cend() - 1);

}

void HttpResponse::addHeaders(const std::vector<std::string>::const_iterator begin, const std::vector<std::string>::const_iterator end) {
	while (begin != end)
	{
		std::string line = *begin;
		std::vector<std::string> elements = split<std::vector<std::string>>(*begin, " ");
		if(elements.size() != 2)
			throw (std::invalid_argument("Invalid HTTP response: " + line));
		addHeader(elements[0], elements[1]);	
	}
	
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
// 		std::string getContentType();
// 		std::string getContentLength();
// 		std::string getContentText();
// 		std::string getContentJson();
// };
