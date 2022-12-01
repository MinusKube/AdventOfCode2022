#include "day.h"

std::unordered_map<int, DayFunction>& get_day_functions() {
	static std::unordered_map<int, DayFunction> day_functions;
	return day_functions;
}

Day::Day(int day, DayFunction func) {
	get_day_functions()[day] = func;
};
