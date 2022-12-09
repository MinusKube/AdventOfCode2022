#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

#include "day.h"

struct Position {
	int x;
	int y;

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

namespace std {
    template <>
    struct hash<Position> {
        std::size_t operator()(const Position& pos) const {
            return std::hash<int>()(pos.x) ^ std::hash<int>()(pos.y);
        }
    };
}

struct Direction {
	int dx;
	int dy;
};

static void run(std::ifstream& file) {
	Position head_pos{ 0, 0 };
	Position tail_pos{ 0, 0 };
	std::array<Position, 9> tail_positions;
	tail_positions.fill({ 0, 0 });

	std::unordered_set<Position> tail_visited_positions;
	tail_visited_positions.insert(tail_pos);

	std::unordered_set<Position> p2_tail_visited_positions;
	p2_tail_visited_positions.insert(tail_positions.back());

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream stream(line);

		char direction_char;
		stream >> direction_char;

		int amount;
		stream >> amount;

		Direction direction;
		switch (direction_char) {
			case 'U':
				direction = {  0, -1 };
				break;
			case 'D':
				direction = {  0,  1 };
				break;
			case 'L':
				direction = { -1,  0 };
				break;
			case 'R':
				direction = {  1,  0 };
				break;
		}

		for (int i = 0; i < amount; i++) {
			head_pos.x += direction.dx;
			head_pos.y += direction.dy;

			{
				if (std::abs(head_pos.x - tail_pos.x) > 1 &&
					std::abs(head_pos.y - tail_pos.y) > 0) {

					tail_pos.x += (head_pos.x > tail_pos.x) ? 1 : -1;
					tail_pos.y += (head_pos.y > tail_pos.y) ? 1 : -1;
				}

				if (std::abs(head_pos.y - tail_pos.y) > 1 &&
					std::abs(head_pos.x - tail_pos.x) > 0) {

					tail_pos.x += (head_pos.x > tail_pos.x) ? 1 : -1;
					tail_pos.y += (head_pos.y > tail_pos.y) ? 1 : -1;
				}

				if (std::abs(head_pos.x - tail_pos.x) > 1) {
					tail_pos.x += (head_pos.x > tail_pos.x) ? 1 : -1;
				}

				if (std::abs(head_pos.y - tail_pos.y) > 1) {
					tail_pos.y += (head_pos.y > tail_pos.y) ? 1 : -1;
				}

				tail_visited_positions.insert(tail_pos);
			}

			for (size_t i = 0; i < tail_positions.size(); i++) {
				Position& this_pos = tail_positions[i];
				Position prev_pos = (i == 0 ? head_pos : tail_positions[i - 1]);

				if (std::abs(prev_pos.x - this_pos.x) > 1 &&
					std::abs(prev_pos.y - this_pos.y) > 0) {

					this_pos.x += (prev_pos.x > this_pos.x) ? 1 : -1;
					this_pos.y += (prev_pos.y > this_pos.y) ? 1 : -1;
				}

				if (std::abs(prev_pos.y - this_pos.y) > 1 &&
					std::abs(prev_pos.x - this_pos.x) > 0) {

					this_pos.x += (prev_pos.x > this_pos.x) ? 1 : -1;
					this_pos.y += (prev_pos.y > this_pos.y) ? 1 : -1;
				}

				if (std::abs(prev_pos.x - this_pos.x) > 1) {
					this_pos.x += (prev_pos.x > this_pos.x) ? 1 : -1;
				}

				if (std::abs(prev_pos.y - this_pos.y) > 1) {
					this_pos.y += (prev_pos.y > this_pos.y) ? 1 : -1;
				}
			}

			p2_tail_visited_positions.insert(tail_positions.back());
		}
	}

	print_p1_result(tail_visited_positions.size());
	print_p2_result(p2_tail_visited_positions.size());
}

static Day day(9, run);
