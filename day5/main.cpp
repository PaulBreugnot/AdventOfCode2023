#include "day5.h"
#include <algorithm>
#include <set>

void part1(char* input_file) {
	Almanac almanac = parse(input_file);
	std::set<unsigned long> locations;
	for(auto seed : almanac.seeds) {
		std::array<unsigned long, 8> values;
		values[0] = seed;
		for(std::size_t i = 0; i < 7; i++) {
			values[i+1] = almanac.maps[i].value(values[i]);
		}
		std::cout << "Seed " << values[0] << std::endl;
		std::cout << "  Soil: " <<  values[1] << std::endl;
		std::cout << "  Fertilizer: " << values[2] << std::endl;
		std::cout << "  Water: " << values[3] << std::endl;
		std::cout << "  Light: " << values[4] << std::endl;
		std::cout << "  Temperature: " << values[5] << std::endl;
		std::cout << "  Humidity: " << values[6] << std::endl;
		std::cout << "  Location: " << values[7] << std::endl;
		locations.insert(values[7]);
	}
	for(auto& item : locations)
		std::cout << item << std::endl;
	std::cout << "Part 1: " << *std::min_element(locations.begin(), locations.end()) << std::endl;
}

void part2(char* input_file) {
	Almanac almanac = parse(input_file);
	std::list<Range> location_ranges;
	std::cout << "Seed ranges: " << std::endl;
	for(const Range& range : almanac.seedRanges()) {
		std::cout << "  " << range << std::endl;
	}
	for(const Range& range : almanac.seedRanges()) {
		std::list<Range> current_values = {range};
		for(const Map& map : almanac.maps) {
			std::list<Range> values;
			for(const Range& input : current_values) {
				values.splice(values.end(), map.values(input)); 
			}
			current_values = values;
		}

		std::cout << "Location ranges: " << std::endl;
		for(const auto& range : current_values) {
			std::cout << "  " << range << std::endl;
		}
		location_ranges.splice(location_ranges.begin(), current_values);
	}
	unsigned long min_locations = std::min_element(
			location_ranges.begin(), location_ranges.end())->begin;

	std::cout << "Part 2: " << min_locations << std::endl;
}

int main(int, char *argv[])
{
	part1(argv[1]);
	part2(argv[1]);
	
	return 0;
}
