#include <list>
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>

struct Record {
	double time;
	double distance;
};

std::list<unsigned long> parse_numbers(const std::string& str) {
	std::list<unsigned long> numbers;
	auto it = str.begin();
	while(it != str.end()) {
		while(!std::isdigit(*it))
			++it;
		std::string number;
		while(std::isdigit(*it))
			number.push_back(*it++);
		numbers.push_back(std::stoul(number));
	}
	return numbers;
}

std::list<Record> parse(const char* input_file) {
	std::ifstream input(input_file);

	std::string time_line;
	std::getline(input, time_line);

	std::string distance_line;
	std::getline(input, distance_line);

	std::list<unsigned long> times = parse_numbers(time_line);
	std::list<unsigned long> distances = parse_numbers(distance_line);

	auto tit = times.begin();
	auto dit = distances.begin();

	std::list<Record> records;
	while(tit != times.end()) {
		Record record;
		record.time = *tit++;
		record.distance = *dit++;
		records.emplace_back(record);
	}
	return records;
}

unsigned long solution(const Record& record) {
	std::cout << "T: " << record.time << ", D: " << record.distance << std::endl;
	unsigned long x1 = std::min(std::ceil(
				(record.time - std::sqrt(
										 std::pow(record.time, 2.0) - 4.0 * record.distance))
				/ 2.0), record.time);
	unsigned long x2 = std::max(std::floor(
				(record.time + std::sqrt(
										 std::pow(record.time, 2.0) - 4.0 * record.distance))
				/ 2.0), 0.0);
	if(x1 * (record.time - x1) <= record.distance) {
		++x1;
	}
	if(x2 * (record.time - x2) <= record.distance) {
		--x2;
	}
	std::cout << x1 * (record.time - x1) << std::endl;
	std::cout << x2 * (record.time - x2) << std::endl;
	std::cout << "x1:" << x1 << ", x2:" << x2 << std::endl;
	return (x2 - x1 + 1);
}

void part1(const char* input_file) {
	std::list<Record> records = parse(input_file);

	double result = 1.0f;
	for(const auto& record : records) {
		result *= solution(record);
	}
	std::cout << "Part 1: " << result << std::endl;
}

void part2(const char* input_file) {
	std::list<Record> records = parse(input_file);
	Record record;
	std::string time = "";
	std::string distance = "";
	for(const auto& r : records) {
		time += std::to_string((unsigned long) r.time);
		distance += std::to_string((unsigned long) r.distance);
	}
	record.time = std::stoul(time);
	record.distance = std::stoul(distance);

	auto result = solution(record);
	std::cout << "Part 2: " << result << std::endl;
}

int main(int, char *argv[])
{
	part1(argv[1]);
	part2(argv[1]);
	return 0;
}
