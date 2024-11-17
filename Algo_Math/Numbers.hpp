#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

template<typename Container, typename T>
int	getIndex(const Container& container, const T& value) {
	auto it = std::find(container.begin(), container.end(), value);
	if(it == container.end())
		return -1;
	return (std::distance(container.begin(), it));
}

template <typename Container>
auto findSpan(const Container& container) -> typename Container::value_type {
    if (container.empty())
        throw std::invalid_argument("Container is empty");

    const auto min = *std::min_element(container.begin(), container.end());
    const auto max = *std::max_element(container.begin(), container.end());

    return max - min;
}
