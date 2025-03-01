#include "WPrinter.hpp"
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>

using namespace WPrinter;

void basic()
{
    // Test scalar types
    stdOut(42);
    stdOut(3.14);
    stdOut(true);
    stdOut("Hello, World!");
    stdOut(std::string("C++ is fun!"));

    // Test containers
    std::vector<int> vec = {1, 2, 3, 4, 5};
    stdOut(vec);

    std::list<double> lst = {1.1, 2.2, 3.3};
    stdOut(lst);

    std::map<std::string, int> mp = {{"one", 1}, {"two", 2}, {"three", 3}};
    stdOut(mp);

    std::set<std::string> st = {"apple", "banana", "cherry"};
    stdOut(st);

    std::queue<int> q;
    q.push(10);
    q.push(20);
    q.push(30);
    stdOut(q);

    std::stack<int> s;
    s.push(100);
    s.push(200);
    s.push(300);
    stdOut(s);
}