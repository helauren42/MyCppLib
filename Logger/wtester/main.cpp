#include "../Logger.hpp"
#include <iostream>
using namespace std;

// Forward declarations of test functions
void testBasicLogging();
void testNestedLogging();
void testLogLevels();

int main() {
    cout << "starting" << endl;
    Logger::setLogger("log.txt", Logger::DEBUG, true);
    Logger::setExtraSpacing(true);

    testBasicLogging();
    testNestedLogging();
    testLogLevels();

    std::cout << "All tests completed. Check log.txt for output." << std::endl;
    return 0;
}
