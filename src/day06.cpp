#include <algorithm>
#include <iostream>
#include <sstream>
#include <deque>
#include <stdexcept>
#include <string>
#include <unordered_set>

#include "day.h"

static int get_start_of_packet_index(const std::string& string, size_t sequence_size) {
	size_t string_size = string.size();
	for (size_t i = sequence_size - 1; i < string_size; i++) {
		std::unordered_set<char> last_chars;
		for (size_t j = 0; j < sequence_size; j++) {
			last_chars.insert(string[i - j]);
		}

		if (last_chars.size() == sequence_size) {
			return i;
		}
	}

	return -1;
}

static void run(std::ifstream& file) {
	std::string line;
	std::getline(file, line);

	print_p1_result(get_start_of_packet_index(line,  4) + 1);
	print_p2_result(get_start_of_packet_index(line, 14) + 1);
}

static Day day(6, run);
