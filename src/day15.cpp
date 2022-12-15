#include <algorithm>
#include <iostream>
#include <limits>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "day.h"

struct Position {
	int x;
	int y;
};

int manhattan_distance(Position a, Position b) {
	return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

static void run(std::ifstream& file) {
	const int target_y = 2000000;
	std::unordered_set<int> impossible_x_positions;

	std::vector<std::pair<Position, int>> sensor_distances;
	std::vector<Position> beacon_positions;

	std::string line;
	while (std::getline(file, line)) {
		std::regex regex("Sensor at x=(-?\\d+), y=(-?\\d+): closest beacon is at x=(-?\\d+), y=(-?\\d+)");
		std::smatch results;
		std::regex_match(line, results, regex);

		Position sensor_pos;
		sensor_pos.x = std::stoi(results[1]);
		sensor_pos.y = std::stoi(results[2]);
		Position beacon_pos;
		beacon_pos.x = std::stoi(results[3]);
		beacon_pos.y = std::stoi(results[4]);

		int dist = manhattan_distance(sensor_pos, beacon_pos);
		int dist_with_target_y = std::abs(sensor_pos.y - target_y);

		sensor_distances.push_back({ sensor_pos, dist });
		beacon_positions.push_back(beacon_pos);

		if ((dist - dist_with_target_y) <= 0) {
			continue;
		}

		for (int x = sensor_pos.x - (dist - dist_with_target_y);
			 x <= sensor_pos.x + (dist - dist_with_target_y);
			 x++) {

			impossible_x_positions.insert(x);
		}
	}

	for (Position beacon_pos : beacon_positions) {
		if (beacon_pos.y == target_y) {
			impossible_x_positions.erase(beacon_pos.x);
		}
	}

	print_p1_result(impossible_x_positions.size());

	for (int y = 0; y <= 4000000; y++) {
		int x = 0;
		while (x <= 4000000) {
			bool found = false;
			for (const std::pair<Position, int>& pair : sensor_distances) {
				int dist_with_pos = manhattan_distance({ x, y }, pair.first);
				int dist_with_beacon = pair.second;
				int dist_with_target_y = std::abs(pair.first.y - y);

				if (dist_with_pos > dist_with_beacon) {
					continue;
				}

				x = pair.first.x + dist_with_beacon - dist_with_target_y + 1;
				found = true;
				break;
			}

			if (!found) {
				print_p2_result(x * 4000000ULL + y);
				return;
			}
		}
	}
}

static Day day(15, run);