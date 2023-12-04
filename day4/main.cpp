#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include <numeric>

struct Card {
	std::unordered_set<int> winning_numbers;
	std::vector<int> numbers_you_have;
};

std::vector<Card> parse_cards(char* input_file) {
	std::ifstream input(input_file);
	std::vector<Card> cards;
	for(std::string line ; std::getline(input, line);) {
		Card card;
		auto it = line.begin();
		while(*it != ':') {
			++it;
		}
		// Skips ':'
		++it;
		while(*it == ' ') {
			++it;
		}
		while(*it != '|') {
			std::string number;
			while(std::isdigit(*it)) {
				number+=*it;
				++it;
			}
			card.winning_numbers.insert(std::stoi(number));
			// Skips ' '
			while(*it == ' ')
				++it;
		}
		// Skips '|'
		++it;
		while(it != line.end()) {
			// Skips ' '
			while(*it == ' ')
				++it;
			std::string number;
			while(std::isdigit(*it)) {
				number+=*it;
				++it;
			}
			card.numbers_you_have.push_back(std::stoi(number));
		}
		cards.push_back(card);
	}
	return cards;
}

void part1(char* input_file) {
	auto cards = parse_cards(input_file);
	int result = 0;
	for(const auto& card : cards) {
		int match = 0;
		for(int i : card.numbers_you_have) {
			if(card.winning_numbers.count(i) > 0)
				match++;
		}
		if(match > 0)
			result += std::pow(2, match-1);
	}
	std::cout << "Part 1: " << result << std::endl;
}

void part2(char* input_file) {
	auto cards = parse_cards(input_file);

	std::vector<std::size_t> cards_score(cards.size());
	for(std::size_t i = 0; i < cards.size(); i++) {
		for(int n : cards[i].numbers_you_have) {
			if(cards[i].winning_numbers.count(n) > 0)
				++cards_score[i];
		}
	}

	std::vector<int> cards_count(cards.size());
	for(auto& item : cards_count)
		item = 1;
	std::size_t card = 0;
	while(card < cards.size()) {
		for(
				std::size_t j = 0;
				j < std::min(cards_score[card], cards.size() - card - 1);
				j++) {
			cards_count[card+j+1]+=cards_count[card];
		}
		++card;
	}
	int total_cards_count = std::accumulate(cards_count.begin(), cards_count.end(), 0);
	std::cout << "Part 2: " << total_cards_count << std::endl;
}

int main(int, char *argv[])
{
	part1(argv[1]);
	part2(argv[1]);
}
