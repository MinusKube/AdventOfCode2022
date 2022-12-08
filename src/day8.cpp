#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "day.h"

typedef std::vector<std::vector<int>> Grid;

static bool is_tree_visible(const Grid& grid, int row, int column) {
	int height = grid[row][column];

	int left_row = row - 1;
	bool left_visible = true;
	while (left_row >= 0) {
		if (grid[left_row][column] >= height) {
			left_visible = false;
			break;
		}
		left_row -= 1;
	}
	
	size_t right_row = row + 1;
	bool right_visible = true;
	while (right_row < grid.size()) {
		if (grid[right_row][column] >= height) {
			right_visible = false;
			break;
		}
		right_row += 1;
	}

	int top_column = column - 1;
	bool top_visible = true;
	while (top_column >= 0) {
		if (grid[row][top_column] >= height) {
			top_visible = false;
			break;
		}
		top_column -= 1;
	}

	size_t bottom_column = column + 1;
	bool bottom_visible = true;
	while (bottom_column < grid[row].size()) {
		if (grid[row][bottom_column] >= height) {
			bottom_visible = false;
			break;
		}
		bottom_column += 1;
	}

	return left_visible || right_visible || top_visible || bottom_visible;
}

static int get_tree_scenic_score(const Grid& grid, int row, int column) {
	int height = grid[row][column];

	int left_row = row - 1;
	int left_visible = 0;
	while (left_row >= 0) {
		left_visible += 1;
		if (grid[left_row][column] >= height) {
			break;
		}
		left_row -= 1;
	}
	
	size_t right_row = row + 1;
	int right_visible = 0;
	while (right_row < grid.size()) {
		right_visible += 1;
		if (grid[right_row][column] >= height) {
			break;
		}
		right_row += 1;
	}

	int top_column = column - 1;
	int top_visible = 0;
	while (top_column >= 0) {
		top_visible += 1;
		if (grid[row][top_column] >= height) {
			break;
		}
		top_column -= 1;
	}

	size_t bottom_column = column + 1;
	int bottom_visible = 0;
	while (bottom_column < grid[row].size()) {
		bottom_visible += 1;
		if (grid[row][bottom_column] >= height) {
			break;
		}
		bottom_column += 1;
	}

	return left_visible * right_visible * top_visible * bottom_visible;
}

static void run(std::ifstream& file) {
	Grid grid;

	std::string line;
	while (std::getline(file, line)) {
		std::vector<int> row;

		for (char c : line) {
			int height = c - '0';

			row.push_back(height);
		}

		grid.push_back(row);
	}

	int visible_trees = 0;
	int highest_scenic_score = 0;

	for (size_t row = 0; row < grid.size(); row++) {
		for (size_t column = 0; column < grid[row].size(); column++) {
			if (is_tree_visible(grid, row, column)) {
				visible_trees += 1;
			}

			int scenic_score = get_tree_scenic_score(grid, row, column);
			if (scenic_score > highest_scenic_score) {
				highest_scenic_score = scenic_score;
			}
		}
	}

	print_p1_result(visible_trees);
	print_p2_result(highest_scenic_score);
}

static Day day(8, run);
