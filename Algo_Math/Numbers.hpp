#pragma once

#include <iostream>
#include <vector>
#include <set>

template<typename T>
int	getPosition(const std::vector<T>& container, T value) {
	auto it = std::find(container.begin(), container.end(), value);
	if(it == container.end())
		return -1;
	return *(std::distance(container.begin(), it));
}
































class ThreeSum {
private:
	int target;
	std::vector<int> nums;
	std::set<std::vector<int>> solutions;

public:
	ThreeSum(std::vector<int> _vec, int _target)
	: target(_target), nums(_vec)
	{
		threeSum();
	};
	~ThreeSum(){};

	std::set<std::vector<int>> getSolutions() {
		return solutions;
	}

    void threeSum() {
		std::sort(nums.begin(), nums.end());
	
		for(int i = 0; i < nums.size() -2; i++) {
			int j = i +1;
			int k = nums.size() -1;
			while (j < k)
			{
				if(nums[i] + nums[j] + nums[k] == 0) {
					solutions.emplace(std::vector<int>{nums[i], nums[j], nums[k]});
					j++;
					k--;
				}
				else if(nums[i] + nums[j] + nums[k] < 0) {
					j++;
				}
				else
					k--;
			}
		}
	}
};

std::set<std::vector<int>> threeSum(std::vector<int> vec, int target) {
	ThreeSum obj(vec, target);
	return obj.getSolutions();
}

