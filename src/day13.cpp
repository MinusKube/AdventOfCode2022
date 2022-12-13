#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "day.h"

struct Node {
	bool array;

	union {
		int value;
		std::vector<Node*> children;
	};

	Node() : array(true), children({}) {}
	Node(int value) : array(false), value(value) {}

	~Node() {
		if (array) {
			children.~vector();
		}
	}

	void add_child(Node* child) {
		this->children.push_back(child);
	}

    friend std::ostream& operator<<(std::ostream& stream, const Node& node) {
    	if (node.array) {
    		stream << "[";
    		for (size_t i = 0; i < node.children.size(); i++) {
    			if (i != 0) {
    				stream << ", ";
    			}

    			stream << *node.children[i];
    		}
    		stream << "]";
    	}
    	else {
    		stream << node.value;
    	}

    	return stream;
    }
};

static Node* parse_node(std::istringstream& stream) {
	stream.get(); // [

	Node* node = new Node();

	do {
		if (stream.peek() == '[') {
			node->add_child(parse_node(stream));
		}
		else if (stream.peek() != ']') {
			int value;
			stream >> value;

			node->add_child(new Node(value));
		}
	}
	while (stream.get() != ']');

	return node;
}

// -1 : Wrong order, 0 : Same order, 1 : Correct order
static int are_nodes_in_right_order(Node* a, Node* b) {
	if (!a->array && !b->array) {
		if (a->value < b->value) {
			return 1;
		}
		else if (a->value == b->value) {
			return 0;
		}
		else {
			return -1;
		}
	}

	Node* real_a = a;
	Node* real_b = b;

	if (!a->array) {
		real_a = new Node();
		real_a->add_child(a);
	}
	if (!b->array) {
		real_b = new Node();
		real_b->add_child(b);
	}

	int right_order = 0;

	for (size_t i = 0; i < real_a->children.size(); i++) {
		if (real_b->children.size() <= i) {
			right_order = -1;
			break;
		}

		right_order = are_nodes_in_right_order(real_a->children[i], real_b->children[i]);
		if (right_order != 0) {
			break;
		}
	}

	if (right_order == 0 && (real_a->children.size() < real_b->children.size())) {
		right_order = 1;
	}

	if (!a->array) {
		delete real_a;
	}

	if (!b->array) {
		delete real_b;
	}

	return right_order;
}

static void run(std::ifstream& file) {
	int correct_order_sum = 0;

	std::vector<Node*> nodes;
	int pair_index = 1;
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream stream(line);
		
		Node* a = parse_node(stream);
		nodes.push_back(a);

		std::getline(file, line);
		stream = std::istringstream(line);

		Node* b = parse_node(stream);
		nodes.push_back(b);

		std::getline(file, line);

		if (are_nodes_in_right_order(a, b) == 0) {
			break;
		}

		if (are_nodes_in_right_order(a, b) == 1) {
			correct_order_sum += pair_index;
		}

		pair_index += 1;
	}

	std::istringstream decoder1_stream = std::istringstream("[[2]]");
	Node* decoder1 = parse_node(decoder1_stream);
	nodes.push_back(decoder1);

	std::istringstream decoder2_stream = std::istringstream("[[6]]");
	Node* decoder2 = parse_node(decoder2_stream);
	nodes.push_back(decoder2);

	std::sort(nodes.begin(), nodes.end(), [](Node* a, Node* b) {
		return are_nodes_in_right_order(a, b) == 1;
	});

	int decoder1_pos = std::find(nodes.begin(), nodes.end(), decoder1) - nodes.begin();
	int decoder2_pos = std::find(nodes.begin(), nodes.end(), decoder2) - nodes.begin();

	print_p1_result(correct_order_sum);
	print_p2_result((decoder1_pos + 1) * (decoder2_pos + 1));
}

static Day day(13, run);