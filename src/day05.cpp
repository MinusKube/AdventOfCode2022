#include <algorithm>
#include <iostream>
#include <sstream>
#include <deque>
#include <stdexcept>
#include <string>

#include "day.h"

class Stack {
	std::deque<char> m_deque;

public:
	void push_bottom(char c) {
		m_deque.push_front(c);
	}

	void push_top(char c) {
		m_deque.push_back(c);
	}

	char pop_top() {
		char c = m_deque.back();
		m_deque.pop_back();
		return c;
	}

	char top() const {
		if (m_deque.empty()) {
			return ' ';
		}

		return m_deque.back();
	}

	char at(int indexFromTop) const {
		size_t size = m_deque.size();
		return m_deque[size - indexFromTop - 1];
	}

	void remove_top(int amount) {
		size_t size = m_deque.size();
		m_deque.resize(size - amount);
	}
};

struct Instruction {
	int move_count;
	int from;
	int to;

	void run_p1(std::vector<Stack>& stacks) {
		for (int i = 0; i < move_count; i++) {
			char top = stacks[from - 1].pop_top();
			stacks[to - 1].push_top(top);
		}
	}

	void run_p2(std::vector<Stack>& stacks) {
		for (int i = 0; i < move_count; i++) {
			char moved = stacks[from - 1].at(move_count - i - 1);
			stacks[to - 1].push_top(moved);
		}

		stacks[from - 1].remove_top(move_count);
	}
};

static void read_stacks(std::istringstream& stream, std::vector<Stack>& stacks) {
	unsigned int current_stack = 0;
	while (!stream.eof()) {
		if (stacks.size() < current_stack + 1) {
			stacks.resize(current_stack + 1);
		}

		stream.get(); // [

		int c = stream.get();

		if (c >= 'A' && c <= 'Z') {
			stacks[current_stack].push_bottom(c);
		}

		stream.get(); // ]
		stream.get(); // <space>

		current_stack += 1;
	}	
}

static Instruction read_instruction(std::istringstream& stream) {
	Instruction instruction;
	std::string ignore;

	stream >> ignore; // move
	stream >> instruction.move_count;
	stream >> ignore; // from
	stream >> instruction.from;
	stream >> ignore; // to
	stream >> instruction.to;

	return instruction;
}

static void run(std::ifstream& file) {
	std::string result_p1;
	std::string result_p2;

	std::vector<Stack> stacks;
	std::vector<Instruction> instructions;

	bool stack_reading_ended = false;

	std::string line;
	while (std::getline(file, line)) {
		if (line.empty()) {
			stack_reading_ended = true;
			continue;
		}

		std::istringstream stream(line);

		if (!stack_reading_ended) {
			read_stacks(stream, stacks);
		}
		else {
			Instruction instruction = read_instruction(stream);
			instructions.push_back(instruction);
		}
	}

	// Part One
	{
		std::vector<Stack> stacks_p1 = stacks;

		for (Instruction& instruction : instructions) {
			instruction.run_p1(stacks_p1);
		}

		for (const Stack& stack : stacks_p1) {
 			result_p1 += stack.top();
		}
	}

	// Part Two
	{
		std::vector<Stack> stacks_p2 = stacks;

		for (Instruction& instruction : instructions) {
			instruction.run_p2(stacks_p2);
		}

		for (const Stack& stack : stacks_p2) {
			result_p2 += stack.top();
		}
	}

	print_p1_result(result_p1);
	print_p2_result(result_p2);
}

static Day day(5, run);
