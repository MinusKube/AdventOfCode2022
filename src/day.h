#pragma once

#include <fstream>
#include <iostream>
#include <unordered_map>

typedef void (*DayFunction)(std::ifstream& file);

class Day {
public:
	Day(int day, DayFunction func);

	static std::unordered_map<int, DayFunction>& get_day_functions();
};

template<class T>
void print_p1_result(T result) {
	std::cout << "Part One Result: " << result << std::endl;
}

template<class T>
void print_p2_result(T result) {
	std::cout << "Part Two Result: " << result << std::endl;
}