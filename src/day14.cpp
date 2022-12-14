#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "day.h"

struct Position {
	int x;
	int y;

	bool operator==(const Position& other) const {
		return x == other.x && y == other.y;
	}
};

struct Rectangle {
	Position min_pos;
	Position max_pos;

	Rectangle(Position a, Position b) {
		min_pos.x = std::min(a.x, b.x);
		min_pos.y = std::min(a.y, b.y);
		max_pos.x = std::max(a.x, b.x);
		max_pos.y = std::max(a.y, b.y);
	}

	bool contains(Position pos) const {
		return pos.x >= min_pos.x && pos.y >= min_pos.y &&
			   pos.x <= max_pos.x && pos.y <= max_pos.y;
	}
};

static bool check_collision(std::vector<Rectangle>& rectangles, Position pos) {
	for (const Rectangle& rectangle : rectangles) {
		if (rectangle.contains(pos)) {
			return true;
		}
	}

	return false;
}

static Position step(std::vector<Rectangle>& rectangles, Position sand_pos) {
	Position possible_positions[] = {
		{ sand_pos.x, sand_pos.y + 1 },
		{ sand_pos.x - 1, sand_pos.y + 1 },
		{ sand_pos.x + 1, sand_pos.y + 1 }
	};

	for (Position pos : possible_positions) {
		if (!check_collision(rectangles, pos)) {
			return pos;
		}
	}

	return sand_pos;
}

static bool has_anything_below(std::vector<Rectangle>& rectangles, Position sand_pos) {
	for (const Rectangle& rectangle : rectangles) {
		if (rectangle.max_pos.y < sand_pos.y) {
			continue;
		}

		if (rectangle.min_pos.x <= sand_pos.x &&
			rectangle.max_pos.x >= sand_pos.x) {

			return true;
		}
	}

	return false;
}

static void run(std::ifstream& file) {
	std::vector<Rectangle> rectangles_p1;
	std::vector<Rectangle> rectangles_p2;

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream stream(line);

		std::string ignore;

		Position last_pos;
		stream >> last_pos.x;
		stream.get(); // ,
		stream >> last_pos.y;

		stream >> ignore; // ->

		while (!stream.eof()) {
			Position cur_pos;
			stream >> cur_pos.x;
			stream.get(); // ,
			stream >> cur_pos.y;

			stream >> ignore; // ->

			rectangles_p1.emplace_back(cur_pos, last_pos);
			rectangles_p2.emplace_back(cur_pos, last_pos);
			last_pos = cur_pos;
		}
	}

	// Part One
	{
		Position sand_pos{ 500, 0 };
		int sand_count = 1;
		while (has_anything_below(rectangles_p1, sand_pos)) {
			Position new_sand_pos = step(rectangles_p1, sand_pos);

			if (new_sand_pos == sand_pos) {
				rectangles_p1.emplace_back(new_sand_pos, new_sand_pos);
				sand_pos = { 500, 0 };
				sand_count += 1;
			}
			else {
				sand_pos = new_sand_pos;
			}
		}

		print_p1_result(sand_count - 1);
	}

	// Part Two
	{
		int highest_y = 0;
		for (const Rectangle& rectangle : rectangles_p2) {
			if (rectangle.max_pos.y > highest_y) {
				highest_y = rectangle.max_pos.y;
			}
		}

		rectangles_p2.emplace_back(
			Position { std::numeric_limits<int>::min(), highest_y + 2},
			Position { std::numeric_limits<int>::max(), highest_y + 2}
		);

		Position sand_pos{ 500, 0 };
		int sand_count = 1;
		while (true) {
			Position new_sand_pos = step(rectangles_p2, sand_pos);

			if (new_sand_pos == sand_pos) {
				if (sand_pos.x == 500 && sand_pos.y == 0) {
					break;
				}

				rectangles_p2.emplace_back(new_sand_pos, new_sand_pos);
				sand_pos = { 500, 0 };
				sand_count += 1;
			}
			else {
				sand_pos = new_sand_pos;
			}
		}

		print_p2_result(sand_count);
	}
}

static Day day(14, run);