#include <fstream>
#include <iostream>

void part1(char* input_file) {
	std::ifstream input(input_file);
	int i = 0;
	for(std::string line ; std::getline(input, line);) {
		char count[2];
		auto it = line.begin();
		while(it != line.end() && !std::isdigit(*it)) {
			it++;
		}
		if(it != line.end())
			count[0] = *it;

		auto rit = line.rbegin();
		while(rit != line.rend() && !std::isdigit(*rit)) {
			rit++;
		}
		if(rit != line.rend())
			count[1] = *rit;
		//std::cout << line << " - " << count[0] << count[1] << std::endl;
		i += std::stoi(count);
	}
	std::cout << "Part 1: " << i << std::endl;
}

std::string digits[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int match(std::string line, std::string::const_iterator it) {
	int i = 0;
	for(std::string digit : digits) {
		++i;
		auto check = it;
		auto digit_it = digit.begin();
		while(check != line.end() && digit_it != digit.end() && *check == *digit_it) {
			++check;
			++digit_it;
		}
		if(digit_it == digit.end())
			return i;
	}
	return 0;
}

int rmatch(std::string line, std::string::const_reverse_iterator it) {
	int i = 0;
	for(std::string digit : digits) {
		++i;
		auto check = it;
		auto digit_it = digit.rbegin();
		while(check != line.rend() && digit_it != digit.rend() && *check == *digit_it) {
			++check;
			++digit_it;
		}
		if(digit_it == digit.rend())
			return i;
	}
	return 0;
}
void part2(char* input_file) {
	std::ifstream input(input_file);
	int i = 0;
	for(std::string line ; std::getline(input, line);) {
		char count[2];
		auto it = line.begin();
		int digit = match(line, it);
		while(it != line.end() && !std::isdigit(*it) && digit == 0) {
			it++;
			digit = match(line, it);
		}
		if(it != line.end()) {
			if(std::isdigit(*it))
				count[0] = *it;
			else
				count[0] = std::to_string(digit).c_str()[0];
		}

		auto rit = line.rbegin();
		digit = rmatch(line, rit);
		while(rit != line.rend() && !std::isdigit(*rit) && digit == 0) {
			rit++;
			digit = rmatch(line, rit);
		}
		if(rit != line.rend()) {
			if(std::isdigit(*rit))
				count[1] = *rit;
			else
				count[1] = std::to_string(digit).c_str()[0];
		}
		//std::cout << line << " - " << count[0] << count[1] << std::endl;
		i += std::stoi(count);
	}
	std::cout << "Part 2: " << i << std::endl;
}

int main(int argc, char *argv[])
{
	part1(argv[1]);
	part2(argv[1]);
}
