#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "../Strings/Strings.hpp"

struct ElemPos
{
	size_t start = 0;
	size_t end = 0;
};

enum ElemType {
	KEY,
	VALUE
};

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

		std::string getVersion() const;
		std::string getStatusCode() const;
		std::string getStatusMessage() const;
		std::map<std::string, std::string> getHeaders() const;
		std::string getBody() const;
		std::map<std::string, std::string> getBodyJson() const;

		void setVersion(const std::string& version);
		void setStatusCode(const std::string& status_code);
		void setStatusMessage(const std::string& status_message);
		void addHeaders(const std::vector<std::string>::const_iterator begin, const std::vector<std::string>::const_iterator end);
		void addHeader(const std::string& key, const std::string& value);
};

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
