#include <utility>
#include <map>
#include <iostream>
#include <vector>

typedef std::pair<unsigned long, unsigned long> Range;

struct Compare {
	bool operator()(
			const Range& p1,
			const Range& p2) const {
		return p1.first < p2.first;
	}
};

class Map {
	public:
		std::map<Range, Range, Compare> map;
	private:
		typename std::map<Range, Range, Compare>::const_iterator contains(
				unsigned long key) const {
			auto it = map.begin();
			if(it->first.first > key)
				return map.end();

			auto next = it;
			++next;
			while(next != map.end() && next->first.first <= key) {
				++it;
				++next;
			}
			if(it != map.end()) {
				if(key >= it->first.second) {
					it = map.end();
				}
			}
			return it;
		}

	public:
		void insert(
				unsigned long destination_range_start,
				unsigned long source_range_start,
				unsigned long range_length) {
			map.insert({
					{source_range_start, source_range_start+range_length},
					{destination_range_start, destination_range_start+range_length}
					});
		}

		unsigned long value(unsigned long key) const {
			auto it = contains(key);
			if(it != map.end()) {
				return it->second.first + key - it->first.first;
			}
			return key;
		}
};

struct Almanac {
	std::vector<unsigned long> seeds;
	Map seed_to_soil;
	Map soil_to_fertilizer;
	Map fertilizer_to_water;
	Map water_to_light;
	Map light_to_temperature;
	Map temperature_to_humidity;
	Map humidity_to_location;
};

Almanac parse(const char* input_file);
