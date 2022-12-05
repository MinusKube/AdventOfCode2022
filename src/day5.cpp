#include <algorithm>
#include <iostream>
#include <sstream>
#include <deque>
#include <stdexcept>
#include <string>

#include "day.h"

static void run(std::ifstream& file) {
	std::vector<std::deque<char>> stacks;

	std::vector<std::deque<char>> stacks_p1;
	std::vector<std::deque<char>> stacks_p2;

	bool stack_reading_ended = false;

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream stream(line);

		if (!stack_reading_ended) {
			unsigned int current_stack = 0;
			while (!stream.eof()) {
				if (stacks.size() < current_stack + 1) {
					stacks.resize(current_stack + 1);
				}

				stream.get(); // [

				int c = stream.get();

				if (c >= 'A' && c <= 'Z') {
					std::cout << current_stack << " / " << (char) c << std::endl;
					stacks[current_stack].push_front(c);
				}
				else if (c >= '0' && c <= '9') {
					stack_reading_ended = true;

					stacks_p1 = stacks;
					stacks_p2 = stacks;

					// Ignore next empty line
					std::getline(file, line);
					break;
				}

				stream.get(); // ]
				stream.get(); // <space>

				current_stack += 1;
			}	
		}
		else {
			std::string ignore;

			int move_count;
			int from;
			int to;

			stream >> ignore; // move
			stream >> move_count;
			stream >> ignore; // from
			stream >> from;
			stream >> ignore; // to
			stream >> to;

			// Part One
			for (int i = 0; i < move_count; i++) {
				char top = stacks_p1[from - 1].back();
				stacks_p1[to - 1].push_back(top);
				stacks_p1[from - 1].pop_back();
			}

			// Part Two
			for (int i = 0; i < move_count; i++) {
				size_t from_size = stacks_p2[from - 1].size();
				char moved = stacks_p2[from - 1][from_size - move_count + i];

				stacks_p2[to - 1].push_back(moved);
			}

			size_t from_size = stacks_p2[from - 1].size();
			stacks_p2[from - 1].resize(from_size - move_count);
		}
	}

	std::string result_p1;
	for (const std::deque<char>& stack : stacks_p1) {
		if (stack.empty()) {
			continue;
		}

		result_p1 += stack.back();
	}

	std::string result_p2;
	for (const std::deque<char>& stack : stacks_p2) {
		if (stack.empty()) {
			continue;
		}

		result_p2 += stack.back();
	}

	print_p1_result(result_p1);
	print_p2_result(result_p2);
}

static Day day(5, run);
