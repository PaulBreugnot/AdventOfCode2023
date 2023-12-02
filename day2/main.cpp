#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

enum Color {red, green, blue};

struct Game {
	int id;
	std::vector<std::array<int, 3>> sets;
};

Game parse_game(const std::string& game_str) {
	auto it = game_str.begin();
	for(int i = 0; i < 5; i++)
		// Skips "Game "
		++it;
	std::string id_str;
	while(std::isdigit(*it)) {
		id_str += *it;
		++it;
	}
	// Skips ": "
	++it;++it;
	Game game;
	game.id = std::stoi(id_str);
	while(it != game_str.end()) {
		std::string set_str;
		while(*it != ';' && it != game_str.end()) {
			std::array<int, 3> set = {0, 0, 0};
			while(*it != ',' && *it != ';' && it != game_str.end()) {
				std::string count_str;
				while(std::isdigit(*it)) {
					count_str += *it;
					++it;
				}
				int count = std::stoi(count_str);
				// Skips " " after
				++it;
				std::string color_str;
				while(*it != ',' && *it != ';' && it != game_str.end()) {
					color_str += *it;
					++it;
				}
				switch(color_str[0]) {
					case 'r':
						set[red] = count;
						break;
					case 'g':
						set[green] = count;
						break;
					case 'b':
						set[blue] = count;
						break;
				}

				if(it != game_str.end() && *it != ';') {
					// Skips ", "
					++it;++it;
				}
			}
			game.sets.push_back(set);
			if(it != game_str.end()) {
				// Skips "; "
				++it;++it;
			}
		}
	}
	return game;
}

bool is_possible(const Game& game, int bag[3]) {
	for(const auto& set : game.sets) {
		if(set[red] > bag[red] || set[green] > bag[green] || set[blue] > bag[blue])
			return false;
	}
	return true;
}

void part1(char* input_file) {
	int bag[3];
	bag[red] = 12;
	bag[green] = 13;
	bag[blue] = 14;

	int result = 0;
	std::ifstream input(input_file);
	for(std::string line ; std::getline(input, line);) {
		Game game = parse_game(line);
		if(is_possible(game, bag)) {
			result += game.id;
		}
	}
	std::cout << "Part 1: " << result << std::endl;
}

int power(const Game& game) {
	std::array<std::vector<int>, 3> cubes_by_color;
	for(const auto& set : game.sets) {
		for(const Color& color : {red, green, blue}) {
			cubes_by_color[color].push_back(set[color]);
		}
	}
	int result = 1;
	for(const Color& color : {red, green, blue}) {
		result *= *std::max_element(
				cubes_by_color[color].begin(),
				cubes_by_color[color].end());
	}
	return result;
}

void part2(char* input_file) {
	int result = 0;
	std::ifstream input(input_file);
	for(std::string line ; std::getline(input, line);) {
		result += power(parse_game(line));
	}
	std::cout << "Part 2: " << result << std::endl;
}

int main(int, char *argv[])
{
	part1(argv[1]);
	part2(argv[1]);
	return 0;
}
