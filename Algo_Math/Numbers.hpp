#pragma once

#include <iostream>
#include <vector>
#include <set>

template<template<typename> class Container, typename T>
int	getPosition(const Container<T>& container, const T& value) {
	auto it = std::find(container.begin(), container.end(), value);
	if(it == container.end())
		return -1;
	return (std::distance(container.begin(), it));
}

