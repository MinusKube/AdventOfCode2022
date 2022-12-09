#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_set>

#include "day.h"

struct Vector {
	int x;
	int y;

    bool operator== (const Vector& other) const {
        return x == other.x && y == other.y;
    }

    Vector& operator+= (const Vector& other) {
    	x += other.x;
    	y += other.y;
    	return *this;
    }
};

namespace std {
    template <>
    struct hash<Vector> {
        std::size_t operator()(const Vector& pos) const {
            return std::hash<int>()(pos.x) ^ std::hash<int>()(pos.y);
        }
    };
}

template<size_t N>
static void advance(std::array<Vector, N>& positions, Vector direction) {
	positions[0] += direction;

	for (size_t i = 1; i < N; i++) {
		Vector& this_pos = positions[i];
		Vector prev_pos = positions[i - 1];

		int diff_x = std::abs(prev_pos.x - this_pos.x);
		int diff_y = std::abs(prev_pos.y - this_pos.y);

		if ((diff_x > 1 && diff_y > 0) ||
			(diff_x > 0 && diff_y > 1)) {

			this_pos.x += (prev_pos.x > this_pos.x) ? 1 : -1;
			this_pos.y += (prev_pos.y > this_pos.y) ? 1 : -1;
		}
		else if (diff_x > 1) {
			this_pos.x += (prev_pos.x > this_pos.x) ? 1 : -1;
		}
		else if (diff_y > 1) {
			this_pos.y += (prev_pos.y > this_pos.y) ? 1 : -1;
		}
	}
}

static void run(std::ifstream& file) {
	std::array<Vector, 2> positions_p1;
	positions_p1.fill({ 0, 0 });
	
	std::unordered_set<Vector> tail_visited_positions_p1;
	tail_visited_positions_p1.insert({ 0, 0 });

	std::array<Vector, 10> positions_p2;
	positions_p2.fill({ 0, 0 });

	std::unordered_set<Vector> tail_visited_positions_p2;
	tail_visited_positions_p2.insert({ 0, 0 });

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream stream(line);

		char direction_char;
		stream >> direction_char;

		int amount;
		stream >> amount;

		Vector direction;
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
			advance(positions_p1, direction);
			advance(positions_p2, direction);

			tail_visited_positions_p1.insert(positions_p1.back());
			tail_visited_positions_p2.insert(positions_p2.back());
		}
	}

	print_p1_result(tail_visited_positions_p1.size());
	print_p2_result(tail_visited_positions_p2.size());
}

static Day day(9, run);
