#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "day.h"

using namespace std::string_literals;

enum class Shape {
	Rock,
	Paper,
	Scissors
};

static Shape charToShape(char c) {
	switch (c) {
		case 'A':
		case 'X':
			return Shape::Rock;
		case 'B':
		case 'Y':
			return Shape::Paper;
		case 'C':
		case 'Z':
			return Shape::Scissors;
	}

	throw std::invalid_argument("Character '"s + c + "' does not match any shape."s);
}

static Shape getWinningShape(Shape shape) {
	switch (shape) {
		case Shape::Rock: return Shape::Paper;
		case Shape::Paper: return Shape::Scissors;
		case Shape::Scissors: return Shape::Rock;
	}
}

static Shape getLosingShape(Shape shape) {
	switch (shape) {
		case Shape::Rock: return Shape::Scissors;
		case Shape::Paper: return Shape::Rock;
		case Shape::Scissors: return Shape::Paper;
	}
}

static int getShapeScore(Shape shape) {
	switch (shape) {
		case Shape::Rock:     return 1;
		case Shape::Paper:    return 2;
		case Shape::Scissors: return 3;
	}
}

static void run(std::ifstream& file) {
	int score_p1 = 0;
	int score_p2 = 0;

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream stream(line);

		char first_char;
		stream >> first_char;
		Shape opponent_shape = charToShape(first_char);

		char second_char;
		stream >> second_char;

		// Part One
		{
			Shape my_shape = charToShape(second_char);

			if (my_shape == opponent_shape) {
				score_p1 += 3;
			}
			else if (getWinningShape(opponent_shape) == my_shape) {
				score_p1 += 6;
			}

			score_p1 += getShapeScore(my_shape);
		}

		// Part Two
		{
			// We lose
			if (second_char == 'X') {
				Shape my_shape = getLosingShape(opponent_shape);

				score_p2 += getShapeScore(my_shape);
			}
			// We draw
			else if (second_char == 'Y') {
				score_p2 += 3;
				score_p2 += getShapeScore(opponent_shape);
			}
			// We win
			else if (second_char == 'Z') {
				Shape my_shape = getWinningShape(opponent_shape);

				score_p2 += 6;
				score_p2 += getShapeScore(my_shape);
			}
			else {
				throw std::invalid_argument("Character "s + second_char + " is not a valid instruction."s);
			}
		}
	}

	print_p1_result(score_p1);
	print_p2_result(score_p2);
}

static Day day(2, run);
