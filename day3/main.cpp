#include <fstream>
#include <iostream>
#include <vector>

void part1(char* input_file) {
	std::vector<std::string> engine;
	std::vector<int> part_numbers;

	std::ifstream input(input_file);
	for(std::string line ; std::getline(input, line);) {
		engine.push_back(line);
	}
	for(std::size_t i = 0; i < engine.size(); i++) {
		std::string line = engine[i];
		std::size_t j = 0;
		while(j != line.size()) {
			while(!std::isdigit(line[j]) && j != line.size()) {
				// Skips points
				++j;
			}
			if(j != line.size()) {
				std::string part;
				std::size_t part_begin = j;
				while(std::isdigit(line[j])) {
					part += line[j];
					++j;
				}
				std::size_t part_end = j;
				bool is_part = false;
				// Top
				if(i > 0) {
					for(std::size_t k = part_begin; k < part_end; k++) {
						if(engine[i-1][k] != '.') {
							is_part = true;
							part_numbers.push_back(std::stoi(part));
						}
					}
				}
				// Bottom
				if(!is_part && i < line.size()-1) {
					for(std::size_t k = part_begin; k < part_end; k++) {
						if(engine[i+1][k] != '.') {
							is_part = true;
							part_numbers.push_back(std::stoi(part));
						}
					}
				}
				// Left
				if(!is_part && part_begin > 0) {
					if(engine[i][part_begin-1] != '.') {
						is_part = true;
						part_numbers.push_back(std::stoi(part));
					}
				}
				// Right
				if(!is_part && part_end < line.size()) {
					if(engine[i][part_end] != '.') {
						is_part = true;
						part_numbers.push_back(std::stoi(part));
					}
				}
				// Top left corner
				if(!is_part && i > 0 && part_begin > 0) {
					if(engine[i-1][part_begin-1] != '.') {
						is_part = true;
						part_numbers.push_back(std::stoi(part));
					}
				}
				// Bottom left corner
				if(!is_part && i < engine.size()-1 && part_begin > 0) {
					if(engine[i+1][part_begin-1] != '.') {
						is_part = true;
						part_numbers.push_back(std::stoi(part));
					}
				}
				// Top right corner
				if(!is_part && i > 0 && part_end < line.size()) {
					if(engine[i-1][part_end] != '.') {
						is_part = true;
						part_numbers.push_back(std::stoi(part));
					}
				}
				// Bottom right corner
				if(!is_part && i < engine.size()-1 && part_end < line.size()) {
					if(engine[i+1][part_end] != '.') {
						is_part = true;
						part_numbers.push_back(std::stoi(part));
					}
				}
			}
		}
	}
	std::size_t result = 0;
	for(const auto& item : part_numbers) {
		result += item;
	}
	std::cout << "Part 1: " << result << std::endl;
}

void part2(char* input_file) {
	std::vector<std::string> engine;
	std::vector<std::vector<std::vector<int>>> geers;

	std::ifstream input(input_file);
	for(std::string line ; std::getline(input, line);) {
		geers.resize(geers.size()+1);
		geers.back().resize(line.size());
		engine.push_back(line);
	}
	for(std::size_t i = 0; i < engine.size(); i++) {
		std::string line = engine[i];
		std::size_t j = 0;
		while(j != line.size()) {
			while(!std::isdigit(line[j]) && j != line.size()) {
				// Skips points
				++j;
			}
			if(j != line.size()) {
				std::string part;
				std::size_t part_begin = j;
				while(std::isdigit(line[j])) {
					part += line[j];
					++j;
				}
				std::size_t part_end = j;
				// Top
				if(i > 0) {
					for(std::size_t k = part_begin; k < part_end; k++) {
						if(engine[i-1][k] == '*') {
							geers[i-1][k].push_back(std::stoi(part));
						}
					}
				}
				// Bottom
				if(i < line.size()-1) {
					for(std::size_t k = part_begin; k < part_end; k++) {
						if(engine[i+1][k] == '*') {
							geers[i+1][k].push_back(std::stoi(part));
						}
					}
				}
				// Left
				if(part_begin > 0) {
					if(engine[i][part_begin-1] == '*') {
						geers[i][part_begin-1].push_back(std::stoi(part));
					}
				}
				// Right
				if(part_end < line.size()) {
					if(engine[i][part_end] == '*') {
						geers[i][part_end].push_back(std::stoi(part));
					}
				}
				// Top left corner
				if(i > 0 && part_begin > 0) {
					if(engine[i-1][part_begin-1] == '*') {
						geers[i-1][part_begin-1].push_back(std::stoi(part));
					}
				}
				// Bottom left corner
				if(i < engine.size()-1 && part_begin > 0) {
					if(engine[i+1][part_begin-1] == '*') {
						geers[i+1][part_begin-1].push_back(std::stoi(part));
					}
				}
				// Top right corner
				if(i > 0 && part_end < line.size()) {
					if(engine[i-1][part_end] == '*') {
						geers[i-1][part_end].push_back(std::stoi(part));
					}
				}
				// Bottom right corner
				if(i < engine.size()-1 && part_end < line.size()) {
					if(engine[i+1][part_end] == '*') {
						geers[i+1][part_end].push_back(std::stoi(part));
					}
				}
			}
		}
	}
	std::size_t result = 0;
	for(std::size_t i = 0; i < geers.size(); i++) {
		for(std::size_t j = 0; j < geers[i].size(); j++) {
			if(geers[i][j].size() == 2) {
				result += geers[i][j][0] * geers[i][j][1];
			}
		}
	}
	std::cout << "Part 2: " << result << std::endl;
}
int main(int, char *argv[])
{
	part1(argv[1]);
	part2(argv[1]);
	return 0;
}
