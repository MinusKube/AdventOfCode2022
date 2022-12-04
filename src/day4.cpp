#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <xstring>

#include "day.h"

class Range {
	int m_start;
	int m_end;

public:
	Range() {}
	Range(int start, int end) : m_start(start), m_end(end) {}

	bool contains(int value) {
		return value >= m_start && value <= m_end;
	}

	bool contains(Range range) {
		return range.m_start >= m_start && range.m_end <= m_end;
	}

	bool intersects(Range range) {
		return range.m_start <= m_end && range.m_end >= m_start;
	}

	friend std::istream& operator>> (std::istream& stream, Range& range) {
		stream >> range.m_start;
		stream.ignore();
		stream >> range.m_end;

		return stream;
	}
};

static void run(std::ifstream& file) {
	int contained_pairs = 0;
	int intersecting_pairs = 0;

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream stream(line);

		Range rangeA;
		stream >> rangeA;

		stream.ignore();

		Range rangeB;
		stream >> rangeB;

		if (rangeA.contains(rangeB) || rangeB.contains(rangeA)) {
			contained_pairs += 1;
		}

		if (rangeA.intersects(rangeB)) {
			intersecting_pairs += 1;
		}
	}

	print_p1_result(contained_pairs);
	print_p2_result(intersecting_pairs);
}

static Day day(4, run);
