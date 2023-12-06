#include "day5.h"
#include <fstream>

Map parse_map(std::vector<std::string>::iterator& line_it) {
	// Skips header
	++line_it;

	Map map;
	while(*line_it != "") {
		auto it = line_it->begin();
		std::string destination;
		while(std::isdigit(*it)) {
			destination += *it;
			++it;
		}
		++it;

		std::string source;
		while(std::isdigit(*it)) {
			source += *it;
			++it;
		}
		++it;

		std::string range;
		while(it != line_it->end()) {
			range += *it;
			++it;
		}

		map.insert(std::stol(destination), std::stol(source), std::stol(range));
		++line_it;
	}
	return map;
}

Almanac parse(const char* input_file) {
	std::ifstream input(input_file);
	std::vector<std::string> lines;
	for(std::string line ; std::getline(input, line);) {
		lines.push_back(line);
	}
	Almanac almanac;

	auto line_it = lines.begin();
	std::string seeds_line = *line_it;
	auto it = line_it->begin();
	for(int i = 0; i < 6; i++)
		// Skips "seeds:"
		++it;
	while(it != line_it->end()) {
		// Skips ' '
		++it;
		std::string number;
		while(std::isdigit(*it) && it != line_it->end()) {
			number += *it;
			++it;
		}
		almanac.seeds.push_back(std::stol(number));
	}
	// Skips empty line
	++line_it;

	almanac.seed_to_soil = parse_map(++line_it);
	almanac.soil_to_fertilizer = parse_map(++line_it);
	almanac.fertilizer_to_water = parse_map(++line_it);
	almanac.water_to_light = parse_map(++line_it);
	almanac.light_to_temperature = parse_map(++line_it);
	almanac.temperature_to_humidity = parse_map(++line_it);
	almanac.humidity_to_location = parse_map(++line_it);

	return almanac;
}
