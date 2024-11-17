#pragma once

#include <type_traits>
#include <vector>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <deque>
#include <stack>
#include <queue>
#include <string>

// std::string executeCommand(const std::string& command) {
//     std::string result;
//     FILE* pipe = popen(command.c_str(), "r");
//     if (!pipe) {
//         throw std::runtime_error("popen() failed!");
//     }
//     try {
//         char buffer[128];
//         while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
//             result += buffer;
//         }
//     } catch (...) {
//         pclose(pipe);
//         throw;
//     }
//     pclose(pipe);
//     return result;
// }

// int main() {
//     try {
//         std::string output = executeCommand("lscpu");
//         std::cout << "Command Output:\n" << output << std::endl;
//     } catch (const std::exception& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }
//     return 0;
// }
