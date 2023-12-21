#include <utility>
#include <map>
#include <iostream>
#include <vector>
#include <cassert>
#include <list>

struct Range {
	unsigned long begin;
	unsigned long size;

	Range(const unsigned long& begin, const unsigned long& size)
		: begin(begin), size(size) {
		}
};

bool operator==(const Range& r1, const Range& r2);
std::ostream& operator<<(std::ostream& s, const Range& r);

struct Compare {
	bool operator()(
			const Range& p1,
			const Range& p2) const {
		return p1.begin < p2.begin;
	}
};

class Map {
	public:
		std::map<Range, unsigned long, Compare> map;
	private:
		typename std::map<Range, unsigned long, Compare>::const_iterator contains(
				unsigned long key) const {
			auto it = map.upper_bound({key, 0});
			if(it == map.begin())
				// Not in map (before min value)
				return map.end();
			if(it == map.end())
				// Not in map (past last range)
				return it;
			return --it;
		}

	public:
		void insert(
				unsigned long destination_range_start,
				unsigned long source_range_start,
				unsigned long range_length) {
			map.insert({
					{source_range_start, range_length},
					destination_range_start
					});
		}

		unsigned long value(unsigned long key) const {
			auto it = contains(key);
			if(it != map.end()) {
				return key - it->first.begin + it->second;
			}
			return key;
		}
		
		std::list<Range> values(const Range& range) const;

		void print() const {
			for(auto item : map) {
				std::cout << item.first.begin << " (" << item.first.size << "), ";
			}
			std::cout << std::endl;
			for(auto item : map) {
				std::cout << item.second << ", ";
			}
			std::cout << std::endl;
		}

		void fill() {
			{
				auto end = *map.rbegin();
				map.insert({
						{end.first.begin + end.first.size, (unsigned long) -1},
						end.first.begin + end.first.size
						});
			}

			auto it = map.begin();
			auto end = map.end();
			--end;--end;
			std::vector<std::pair<Range, unsigned long>> items_to_add;
			while(it != end) {
				unsigned long begin = it->first.begin;
				unsigned long size = it->first.size;
				unsigned long current = begin + size;
				unsigned long expected = (++it)->first.begin;
				if(current != expected) {
					items_to_add.push_back({{current, expected-current}, current});
				}
			}
			for(auto item : items_to_add) {
				insert(item.second, item.first.begin, item.first.begin);
			}
		}

		void check() const {
			auto it = map.begin();
			auto end = map.end();
			--end;--end;
			while(it != end) {
				auto begin = it->first.begin;
				auto size = it->first.size;
				auto current = begin + size;
				auto expected = (++it)->first.begin;
				if(current != expected) {
					std::cout << "Error at " << begin << "(" << size << ") -> " << expected << " error range = " << expected - current << std::endl;
					assert(expected > current);
				}
				assert(current == expected);
			}
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
