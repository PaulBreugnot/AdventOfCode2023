#include "day5.h"
#include <fstream>

bool operator==(const Range& r1, const Range& r2) {
	return r1.begin == r2.begin && r1.size == r2.size;
}
std::ostream& operator<<(std::ostream& s, const Range& r) {
	s << "(b:" << r.begin << ", s:" << r.size << ")";
	return s;
}

bool operator<(
		const Range& p1,
		const Range& p2) {
	return p1.begin < p2.begin;
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
	almanac.seedToSoil() = parse_map(++line_it);
	almanac.seedToSoil().fill();
	almanac.seedToSoil().check();
	almanac.seedToSoil().print();

	std::cout << std::endl << "Soil to fertilizer: ";
	almanac.soilToFertilizer() = parse_map(++line_it);
	almanac.soilToFertilizer().fill();
	almanac.soilToFertilizer().check();
	almanac.soilToFertilizer().print();

	std::cout << std::endl << "Fertilizer to water: ";
	almanac.fertilizerToWater() = parse_map(++line_it);
	almanac.fertilizerToWater().fill();
	almanac.fertilizerToWater().check();
	almanac.fertilizerToWater().print();

	std::cout << std::endl << "Water to light: ";
	almanac.waterToLight() = parse_map(++line_it);
	almanac.waterToLight().fill();
	almanac.waterToLight().check();
	almanac.waterToLight().print();

	std::cout << std::endl << "Light to temperature: ";
	almanac.lightToTemperature() = parse_map(++line_it);
	almanac.lightToTemperature().fill();
	almanac.lightToTemperature().check();
	almanac.lightToTemperature().print();

	std::cout << std::endl << "Temperature to humidity: ";
	almanac.temperaturToHumidity() = parse_map(++line_it);
	almanac.temperaturToHumidity().fill();
	almanac.temperaturToHumidity().check();
	almanac.temperaturToHumidity().print();

	std::cout << std::endl << "Humidity to location: ";
	almanac.humidityToLocation() = parse_map(++line_it);
	almanac.humidityToLocation().fill();
	almanac.humidityToLocation().check();
	almanac.humidityToLocation().print();

	return almanac;
}
