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

struct TreeData {
	bool visible;
	int scenic_score;
};

struct GridDirection {
	int row;
	int column;
};

static TreeData compute_tree_data(const Grid& grid, int row, int column) {
	int tree_height = grid[row][column];

	int row_count = grid.size();
	int column_count = grid[0].size();

	GridDirection directions[] = {
		{ -1,  0 },
		{  1,  0 },
		{  0, -1 },
		{  0,  1 }
	};

	TreeData data;
	data.visible = false;
	data.scenic_score = 1;

	for (GridDirection direction : directions) {
		bool visible = true;
		int view_distance = 0;

		int current_row = row + direction.row;
		int current_column = column + direction.column;

		while (current_row >= 0 && current_row < row_count &&
			   current_column >= 0 && current_column < column_count) {

			view_distance += 1;

			if (grid[current_row][current_column] >= tree_height) {
				visible = false;
				break;
			}

			current_row += direction.row;
			current_column += direction.column;
		}

		data.visible = data.visible || visible;
		data.scenic_score *= view_distance;
	}

	return data;
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
			TreeData data = compute_tree_data(grid, row, column);

			if (data.visible) {
				visible_trees += 1;
			}

			if (data.scenic_score > highest_scenic_score) {
				highest_scenic_score = data.scenic_score;
			}
		}
	}

	print_p1_result(visible_trees);
	print_p2_result(highest_scenic_score);
}

static Day day(8, run);
