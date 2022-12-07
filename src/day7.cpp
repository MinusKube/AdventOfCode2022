#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <deque>
#include <stdexcept>
#include <string>
#include <unordered_set>

#include "day.h"

struct Content {
	bool dir;
	int size;
	std::string name;
};

static int get_folder_size(const std::unordered_map<std::string, std::vector<Content>>& folder_contents, std::string folder) {
	int size = 0;

	if (folder_contents.find(folder) == folder_contents.end()) {
		return 0;
	}

	for (Content content : folder_contents.at(folder)) {
		if (content.dir) {
			size += get_folder_size(folder_contents, content.name);
		}
		else {
			size += content.size;
		}
	}

	return size;
}

static void run(std::ifstream& file) {
	int result_p1 = 0;
	int result_p2 = 0;

	std::unordered_map<std::string, std::vector<Content>> folder_contents;

	std::vector<std::string> current_dir;

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream stream(line);

		if (stream.peek() == '$') {
			stream.ignore();

			std::string cmd;
			stream >> cmd;

			if (cmd == "cd") {
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
			std::string cur = "/";
			for (auto dir : current_dir) {
				cur += dir;
				cur += "/";
			}

			std::string type;
			stream >> type;

			if (type == "dir") {
				Content content;
				content.dir = true;
				std::string name;
				stream >> name;
				content.name = cur + name + "/";

				if (folder_contents.find(cur) == folder_contents.end()) {
					folder_contents.emplace(cur, std::vector<Content>());
				}

				folder_contents[cur].push_back(content);
			}
			else {
				Content content;
				content.dir = false;
				content.size = std::stoi(type);
				stream >> content.name;

				if (folder_contents.find(cur) == folder_contents.end()) {
					folder_contents.emplace(cur, std::vector<Content>());
				}

				folder_contents[cur].push_back(content);
			}
		}
	}

	int total_size = 70000000;
	int used_size = get_folder_size(folder_contents, "/");
	int needed_size = 30000000;
	std::vector<int> ok;
	for (auto iter : folder_contents) {
		std::string folder = iter.first;
		int size = get_folder_size(folder_contents, folder);

		if (size <= 100000) {
			result_p1 += size;
		}

		if (total_size - used_size + size >= needed_size) {
			ok.push_back(size);
		}
	}

	std::sort(ok.begin(), ok.end());
	result_p2 = ok[0];

	print_p1_result(result_p1);
	print_p2_result(result_p2);
}

static Day day(7, run);
