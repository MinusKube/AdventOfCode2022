#include "day.h"

Day::Day(int day, DayFunction func) {
	get_day_functions()[day] = func;
};

std::unordered_map<int, DayFunction>& Day::get_day_functions() {
	static std::unordered_map<int, DayFunction> day_functions;
	return day_functions;
}