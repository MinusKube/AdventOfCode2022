#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "day.h"

struct Content {
	bool dir;
	int size;
	std::string full_name;
};

typedef std::unordered_map<std::string, std::vector<Content>> FolderContents;

static int get_folder_size(const FolderContents& folder_contents, const std::string& folder) {
	int size = 0;

	if (folder_contents.find(folder) == folder_contents.end()) {
		return 0;
	}

	for (Content content : folder_contents.at(folder)) {
		if (content.dir) {
			size += get_folder_size(folder_contents, content.full_name);
		}
		else {
			size += content.size;
		}
	}

	return size;
}

static void run(std::ifstream& file) {
	FolderContents folder_contents;
	std::vector<std::string> current_dir;

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream stream(line);

		if (stream.peek() == '$') {
			stream.ignore();

			std::string command;
			stream >> command;

			if (command == "cd") {
				std::string path;
				stream >> path;

				if (path == "..") {
					current_dir.pop_back();
				}
				else if (path == "/") {
					current_dir.clear();
				}
				else {
					current_dir.push_back(path);
				}
			}
		}
		else {
			std::string current_path = "/";
			for (auto dir : current_dir) {
				current_path += dir + "/";
			}

			std::string type;
			stream >> type;

			std::string name;
			stream >> name;

			Content content;

			if (type == "dir") {
				content.dir = true;
				content.size = 0;
				content.full_name = current_path + name + "/";
			}
			else {
				content.dir = false;
				content.size = std::stoi(type);
				content.full_name = current_path + name;
			}

			folder_contents[current_path].push_back(content);
		}
	}

	const int maximum_folder_size = 100000;
	const int total_size = 70000000;
	const int used_size = get_folder_size(folder_contents, "/");
	const int needed_size = 30000000;

	int folder_size_sum = 0;
	int min_removable_size = std::numeric_limits<int>::max();

	for (auto& pair : folder_contents) {
		const std::string& folder = pair.first;
		const int size = get_folder_size(folder_contents, folder);

		// Part One
		if (size <= maximum_folder_size) {
			folder_size_sum += size;
		}

		// Part Two
		if (total_size - used_size + size >= needed_size &&
			size < min_removable_size) {

			min_removable_size = size;
		}
	}

	print_p1_result(folder_size_sum);
	print_p2_result(min_removable_size);
}

static Day day(7, run);
