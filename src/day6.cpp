#include <algorithm>
#include <iostream>
#include <sstream>
#include <deque>
#include <stdexcept>
#include <string>
#include <unordered_set>

#include "day.h"
static void run(std::ifstream& file) {
	int result_p1 = 0;
	int result_p2 = 0;

	std::string line;
	while (std::getline(file, line)) {
		size_t line_size = line.size();
		for (size_t i = 3; i < line_size; i++) {
			std::unordered_set<char> chars;
			chars.insert(line[i - 0]);
			chars.insert(line[i - 1]);
			chars.insert(line[i - 2]);
			chars.insert(line[i - 3]);

			if (chars.size() == 4) {
				result_p1 = (i + 1);
				break;
			}
		}
		for (size_t i = 13; i < line_size; i++) {
			std::unordered_set<char> chars;
			for (int j = 0; j < 14; j++) {
				chars.insert(line[i - j]);
			}

			if (chars.size() == 14) {
				result_p2 = (i + 1);
				break;
			}
		}
	}

	print_p1_result(result_p1);
	print_p2_result(result_p2);
}

static Day day(6, run);
