#include "Strings.hpp"
#include "../Printer/Printer.hpp"

int main(void) {
	std::string str = "  \n\tHello \nWorld!    \n   \n \t";
	str = lstrip(str);
	Printer::print(str);
	str = rstrip(str);
	Printer::print(str, "\n");

	std::string str2 = "  \n\tHello \nWorld!    \n   \n \t";
	str2 = strip(str2);
	Printer::all("strip: ", str2);

	std::string str3 = "dogogdddgooddgogoodddddHello World! dogododdddogggodgo";
	str3 = strip(str3, "dog");
	Printer::all("strip 3: ", str3);

}