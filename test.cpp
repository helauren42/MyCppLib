#include <iostream>
#include <string>

class Printer {
public:
    // Static method with an optional separator
    static void print(const std::string &a, const std::string& sep = "\n") {
        std::cout << a << sep;
    }
};

int main() {
    Printer::print("Hello, World!");  // Uses default separator "\n"
    Printer::print("Hello, World!", ", ");  // Uses custom separator ", "
    return 0;
}
