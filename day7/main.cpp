#include <array>
#include <algorithm>
#include <vector>
#include <fstream>
#include <set>
#include <iostream>

enum Type {
	FIVE_OF_A_KIND = 7,
	FOUR_OF_A_KIND = 6,
	FULL_HOUSE = 5,
	THREE_OF_A_KIND = 4,
	TWO_PAIR = 3,
	ONE_PAIR = 2,
	HIGH_CARD = 1
};
	
std::ostream& operator<<(std::ostream& s, const Type& type) {
	switch(type) {
		case FIVE_OF_A_KIND:
			s << "FIVE_OF_A_KIND";
			break;
		case FOUR_OF_A_KIND:
			s << "FOUR_OF_A_KIND";
			break;
		case FULL_HOUSE:
			s << "FULL_HOUSE";
			break;
		case THREE_OF_A_KIND:
			s << "THREE_OF_A_KIND";
			break;
		case TWO_PAIR:
			s << "TWO_PAIR";
			break;
		case ONE_PAIR:
			s << "ONE_PAIR";
			break;
		case HIGH_CARD:
			s << "HIGH_CARD";
			break;
	}
	return s;
}

struct Hand {
	std::array<int, 5> cards;
	unsigned long bid;

	Type type() const {
		std::array<int, 13> cards_by_value;
		std::fill(cards_by_value.begin(), cards_by_value.end(), 0);
		for(const auto& card : cards) {
			++cards_by_value[card-2];
		}

		int max = *std::max_element(cards_by_value.begin(), cards_by_value.end());
		if(max == 5)
			return FIVE_OF_A_KIND;
		if(max == 4)
			return FOUR_OF_A_KIND;
		if(max == 3) {
			if(std::count(cards_by_value.begin(), cards_by_value.end(), 2)
					== 1)
				return FULL_HOUSE;
			return THREE_OF_A_KIND;
		}
		if(max == 2) {
			if(std::count(cards_by_value.begin(), cards_by_value.end(), 2)
					== 2)
				return TWO_PAIR;
			return ONE_PAIR;
		}
		return HIGH_CARD;
	}
};

std::ostream& operator<<(std::ostream& s, const Hand& hand) {
	for(const auto& card : hand.cards) {
		if(card == 14)
			s << 'A';
		else if(card == 13)
			s << 'K';
		else if(card == 12)
			s << 'Q';
		else if(card == 11)
			s << 'J';
		else if(card == 10)
			s << 'T';
		else
			s << card;
	}
	s << ' ';
	s << hand.bid;
	s << " (" << hand.type() << ")";
	return s;
}

bool operator<(const Hand& hand1, const Hand& hand2) {
	Type type1 = hand1.type();
	Type type2 = hand2.type();
	if(type1 == type2) {
		auto it1 = hand1.cards.begin();
		auto it2 = hand2.cards.begin();
		while(it1 != hand1.cards.end()) {
			if(*it1 != *it2)
				return *it1 < *it2;
			++it1;
			++it2;
		}
		return false;
	}
	return type1 < type2;
}

std::set<Hand> parse(const char* input_file) {
	std::ifstream input(input_file);
	std::set<Hand> hands;
	for(std::string line ; std::getline(input, line);) {
		Hand hand;
		for(int i = 0; i < 5; i++) {
			char card = line[i];
			if(card == 'A')
				hand.cards[i] = 14;
			else if(card == 'T')
				hand.cards[i] = 10;
			else if(card == 'J')
				hand.cards[i] = 11;
			else if(card == 'Q')
				hand.cards[i] = 12;
			else if(card == 'K')
				hand.cards[i] = 13;
			else
				hand.cards[i] = std::stoi(std::string({line[i]}));
		}
		hand.bid = std::stoi(line.substr(6));
		hands.insert(hand);
	}
	return hands;
}

void part1(const char* input_file) {
	auto hands = parse(input_file);

	unsigned long result = 0;
	int i = 1;
	for(auto& hand : hands) {
		std::cout << hand << std::endl;
		result += hand.bid * i++;
	}
	std::cout << "Part 1: " << result << std::endl;
}

int main(int, char *argv[])
{
	part1(argv[1]);
	
	return 0;
}
