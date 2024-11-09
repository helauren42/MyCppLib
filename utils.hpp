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

class TypeChecker {
public:
    template<typename T>
    static std::true_type isContainer(const std::vector<T>*) { return std::true_type{}; }

    template<typename T>
    static std::true_type isContainer(const std::list<T>*) { return std::true_type{}; }

    template<typename T>
    static std::true_type isContainer(const std::forward_list<T>*) { return std::true_type{}; }

    template<typename T>
    static std::true_type isContainer(const std::set<T>*) { return std::true_type{}; }

    template<typename K, typename V>
    static std::true_type isContainer(const std::map<K, V>*) { return std::true_type{}; }

    template<typename T>
    static std::true_type isContainer(const std::deque<T>*) { return std::true_type{}; }

    template<typename T>
    static std::true_type isContainer(const std::stack<T>*) { return std::true_type{}; }

    template<typename T>
    static std::true_type isContainer(const std::queue<T>*) { return std::true_type{}; }

    template<typename T>
    static std::false_type isContainer(const T*) { return std::false_type{}; }
};
