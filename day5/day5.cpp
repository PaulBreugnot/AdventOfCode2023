#include "day5.h"
#include <fstream>

bool operator==(const Range& r1, const Range& r2) {
	return r1.begin == r2.begin && r1.size == r2.size;
}
std::ostream& operator<<(std::ostream& s, const Range& r) {
	s << "(b:" << r.begin << ", s:" << r.size << ")";
	return s;
}

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

std::list<Range> Map::values(const Range& range) const {
	std::list<Range> result;
	Range current_range = range;
	do {
		std::cout << "b: " << current_range.begin << ", s: " << current_range.size << std::endl;
		auto map_it = contains(current_range.begin);
		if(map_it == map.end() && current_range.begin < map.begin()->first.begin) {
			// Value of range before first value of the map
			if(current_range.begin + current_range.size - 1 < map.begin()->first.begin) {
				// The range is included before the first value of the map
				result.push_back(current_range);
				current_range = {current_range.begin + current_range.size, 0};
			} else {
				// Only a part matches the region before the first value of the
				// map
				Range result_range = {
					value(current_range.begin),
					map.begin()->first.begin - current_range.begin
				};
				result.push_back(result_range);
				current_range = {map.begin()->first.begin, current_range.size - result_range.size};
			}
		} else if (map_it == map.end()) {
			// The range is included after the last value of the map
			result.push_back(current_range);
			current_range = {current_range.begin + current_range.size, 0};
		} else {
			if(current_range.begin + current_range.size  >=
					map_it->first.begin + map_it->first.size) {
					Range result_range = {
						value(current_range.begin),
						map_it->first.begin + map_it->first.size - current_range.begin
					};
					result.push_back(result_range);
					current_range = {
						map_it->first.begin+map_it->first.size,
						current_range.size - result_range.size
					};
			} else {
				result.push_back({
						value(current_range.begin),
						current_range.size
						});
				current_range = {current_range.begin + current_range.size, 0};
			}
		}
	} while(current_range.size != 0);
	return result;
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

	std::cout << std::endl << "Seed to soil: ";
	almanac.seed_to_soil = parse_map(++line_it);
	almanac.seed_to_soil.fill();
	almanac.seed_to_soil.check();
	almanac.seed_to_soil.print();

	std::cout << std::endl << "Soil to fertilizer: ";
	almanac.soil_to_fertilizer = parse_map(++line_it);
	almanac.soil_to_fertilizer.fill();
	almanac.soil_to_fertilizer.check();
	almanac.soil_to_fertilizer.print();

	std::cout << std::endl << "Fertilizer to water: ";
	almanac.fertilizer_to_water = parse_map(++line_it);
	almanac.fertilizer_to_water.fill();
	almanac.fertilizer_to_water.check();
	almanac.fertilizer_to_water.print();

	std::cout << std::endl << "Water to light: ";
	almanac.water_to_light = parse_map(++line_it);
	almanac.water_to_light.fill();
	almanac.water_to_light.check();
	almanac.water_to_light.print();

	std::cout << std::endl << "Light to temperature: ";
	almanac.light_to_temperature = parse_map(++line_it);
	almanac.light_to_temperature.fill();
	almanac.light_to_temperature.check();
	almanac.light_to_temperature.print();

	std::cout << std::endl << "Temperature to humidity: ";
	almanac.temperature_to_humidity = parse_map(++line_it);
	almanac.temperature_to_humidity.fill();
	almanac.temperature_to_humidity.check();
	almanac.temperature_to_humidity.print();

	std::cout << std::endl << "Humidity to location: ";
	almanac.humidity_to_location = parse_map(++line_it);
	almanac.humidity_to_location.fill();
	almanac.humidity_to_location.check();
	almanac.humidity_to_location.print();

	return almanac;
}
