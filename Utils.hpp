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
    template <typename T>
    static constexpr bool isContainer(const T& value) {
        return is_specialization<T, std::vector>::value ||
               is_specialization<T, std::list>::value ||
               is_specialization<T, std::forward_list>::value ||
               is_specialization<T, std::set>::value ||
               is_specialization<T, std::map>::value ||
               is_specialization<T, std::deque>::value ||
               is_specialization<T, std::stack>::value ||
               is_specialization<T, std::queue>::value;
    }

private:
    template <typename T, template <typename...> class Template>
    struct is_specialization : std::false_type {};

    template <template <typename...> class Template, typename... Args>
    struct is_specialization<Template<Args...>, Template> : std::true_type {};
};

// class TypeChecker {
// public:
//     template<typename T>
//     static std::true_type isContainer(const std::vector<T>*) { return std::true_type{}; }

//     template<typename T>
//     static std::true_type isContainer(const std::list<T>*) { return std::true_type{}; }

//     template<typename T>
//     static std::true_type isContainer(const std::forward_list<T>*) { return std::true_type{}; }

//     template<typename T>
//     static std::true_type isContainer(const std::set<T>*) { return std::true_type{}; }

//     template<typename K, typename V>
//     static std::true_type isContainer(const std::map<K, V>*) { return std::true_type{}; }

//     template<typename T>
//     static std::true_type isContainer(const std::deque<T>*) { return std::true_type{}; }

//     template<typename T>
//     static std::true_type isContainer(const std::stack<T>*) { return std::true_type{}; }

//     template<typename T>
//     static std::true_type isContainer(const std::queue<T>*) { return std::true_type{}; }

//     template<typename T>
//     static std::false_type isContainer(const T*) { return std::false_type{}; }
// };
