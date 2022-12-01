#include <iostream>
#include <string>

#include "day.h"

int main() {
	std::unordered_map<int, DayFunction>& day_functions = get_day_functions();
	int day_count = day_functions.size();

	std::cout << "Welcome to Advent of Code 2022 by MinusKube!" << std::endl;
	std::cout << "Which day to you want to execute? (1-" << day_count << ")" << std::endl;

	int day;
	std::cin >> day;

	while (day < 1 || day > day_count) {
		std::cout << "Invalid day! (1-" << day_count << ")" << std::endl;
		std::cin >> day;
	}

	int example_char = std::cin.peek();
	bool example = (example_char == '?');

	std::string file_name;
	file_name += "../data/day";
	file_name += std::to_string(day);
	file_name += (example ? "_example.txt" : ".txt");

	std::ifstream file(file_name);
	day_functions[day](file);

	std::cin.ignore(1000, '\n');
	std::cin.get();

	return 0;
}
