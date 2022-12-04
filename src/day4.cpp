#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "day.h"

struct Pair {
	std::vector<int> elements;
	
	Pair(int a, int b) {
		for (int i = a; i <= b; i++) {
			elements.push_back(i);
		}
	}
};

static void run(std::ifstream& file) {
	int t = 0;
	int t2 = 0;
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream stream(line);

		int a, b, c, d;
		char temp;
		stream >> a >> temp >> b >> temp >> c >> temp >> d;

		Pair pairA(a, b);
		Pair pairB(c, d);

		bool nop = true;
		for (int e : pairA.elements) {
			if (std::find(pairB.elements.begin(), pairB.elements.end(), e) == pairB.elements.end()) {
				nop = false;
			}
		}

		if (nop) {
			t += 1;
		}
		else {
		nop = true;
		for (int e : pairB.elements) {
			if (std::find(pairA.elements.begin(), pairA.elements.end(), e) == pairA.elements.end()) {
				nop = false;
			}
		}

		if (nop) {
			t += 1;
		}
		}

		bool found = false;
		for (int e : pairA.elements) {
			if (std::find(pairB.elements.begin(), pairB.elements.end(), e) != pairB.elements.end()) {
				found = true;
			}
		}

		if (found) {
			t2 += 1;
		}
	}

	print_p1_result(t);
	print_p2_result(t2);
}

static Day day(4, run);
