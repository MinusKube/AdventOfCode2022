#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "day.h"

struct Position {
	int row;
	int column;

    bool operator== (const Position& other) const {
        return row == other.row && column == other.column;
    }
};

namespace std {
    template <>
    struct hash<Position> {
        std::size_t operator()(const Position& pos) const {
            return std::hash<int>()(pos.row) ^ std::hash<int>()(pos.column);
        }
    };
}

static int compute_path(std::vector<std::string>& rows, Position start_pos) {
	std::unordered_set<Position> open_set;
	open_set.insert(start_pos);

	std::unordered_map<Position, int> scores;
	scores[start_pos] = 0;

	while (!open_set.empty()) {
		Position pos = *open_set.begin();
		open_set.erase(open_set.begin());

		char value = rows[pos.row][pos.column];
		int new_score = scores[pos] + 1;

		Position target_positions[] = {
			{ pos.row - 1, pos.column },
			{ pos.row + 1, pos.column },
			{ pos.row, pos.column - 1 },
			{ pos.row, pos.column + 1 }
		};

		for (Position target_pos : target_positions) { 
			if (target_pos.row < 0 || target_pos.row >= rows.size() ||
				target_pos.column < 0 || target_pos.column >= rows[target_pos.row].size()) {

				continue;
			}

			char target_value = rows[target_pos.row][target_pos.column];

			if (value == 'z' && target_value == 'E') {
				return new_score;
			}

			if (value == 'S' || target_value - value <= 1) {
				if (scores.find(target_pos) == scores.end() ||
				    new_score < scores[target_pos]) {

					scores[target_pos] = new_score;
					open_set.insert(target_pos);
				}
			}
		}
	}

	return -1;
}

static void run(std::ifstream& file) {
	std::vector<std::string> rows;

	Position start_pos;
	std::vector<Position> lowest_positions;

	std::string line;
	while (std::getline(file, line)) {
		rows.push_back(line);

		size_t start_index = line.find('S');

		if (start_index != std::string::npos) {
			start_pos.row = rows.size() - 1;
			start_pos.column = start_index;
		}

		for (size_t i = 0; i < line.size(); i++) {
			if (line[i] == 'S' || line[i] == 'a') {
				Position pos;
				pos.row = rows.size() - 1;
				pos.column = i;

				lowest_positions.push_back(pos);
			}
		}
	}

	print_p1_result(compute_path(rows, start_pos));

	int min_steps = std::numeric_limits<int>::max();
	for (Position pos : lowest_positions) {
		int steps = compute_path(rows, pos);

		if (steps != -1 && steps < min_steps) {
			min_steps = steps;
		}
	}

	print_p2_result(min_steps);
}

static Day day(12, run);