#pragma once

#include <fstream>
#include <unordered_map>

typedef void (*DayFunction)(std::ifstream& file);

std::unordered_map<int, DayFunction>& get_day_functions();

class Day {
public:
	Day(int day, DayFunction func);
};