#include "day5.h"
#include <algorithm>
#include <set>

void part1(char* input_file) {
	Almanac almanac = parse(input_file);
	std::set<unsigned long> locations;
	//almanac.seeds = {1224711373};
	for(auto seed : almanac.seeds) {
		std::cout << "Seed " << seed << std::endl;
		unsigned long soil = almanac.seed_to_soil.value(seed);
		std::cout << "  Soil: " <<  soil << std::endl;
		unsigned long fertilizer = almanac.soil_to_fertilizer.value(soil);
		std::cout << "  Fertilizer: " << fertilizer << std::endl;
		unsigned long water = almanac.fertilizer_to_water.value(fertilizer);
		std::cout << "  Water: " << water << std::endl;
		unsigned long light = almanac.water_to_light.value(water);
		std::cout << "  Light: " << light << std::endl;
		unsigned long temp = almanac.light_to_temperature.value(light);
		std::cout << "  Temperature: " << temp << std::endl;
		unsigned long humidity = almanac.temperature_to_humidity.value(temp);
		std::cout << "  Humidity: " << humidity << std::endl;
		unsigned long location = almanac.humidity_to_location.value(humidity);
		std::cout << "  Location: " << location << std::endl;
		locations.insert(location);
	}
	for(auto& item : locations)
		std::cout << item << std::endl;
	std::cout << "Part 1: " << *std::min_element(locations.begin(), locations.end()) << std::endl;
}

int main(int, char *argv[])
{
	part1(argv[1]);
	
	return 0;
}
