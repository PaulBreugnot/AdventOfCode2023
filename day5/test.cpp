#include "gmock/gmock.h"
#include "day5.h"

using testing::Eq;
using testing::ElementsAre;

// Demonstrate some basic assertions.
TEST(Day5Test, seed_map) {
	Map map;
	map.insert(50, 98, 2);
	map.insert(52, 50, 48);
	map.fill();
	map.print();

	for(unsigned long i = 0; i < 50; i++)
		ASSERT_THAT(map.value(i), Eq(i));
	for(unsigned long i = 50; i < 98; i++)
		ASSERT_THAT(map.value(i), Eq(i+2));
	ASSERT_THAT(map.value(98), Eq(50));
	ASSERT_THAT(map.value(99), Eq(51));

	for(unsigned long i = 100; i < 150; i++) {
		ASSERT_THAT(map.value(i), Eq(i));
	}
}

TEST(Day5Test, soil_map) {
	Map map;
	map.insert(0, 15, 37);
	map.insert(37, 52, 2);
	map.insert(39, 0, 15);
	map.fill();

	for(unsigned long i = 0; i < 15; i++)
		ASSERT_THAT(map.value(i), Eq(39+i));
	for(unsigned long i = 15; i < 15+37; i++)
		ASSERT_THAT(map.value(i), Eq(0 + i - 15));
	ASSERT_THAT(map.value(52), Eq(37));
	ASSERT_THAT(map.value(53), Eq(38));

	for(unsigned long i = 54; i < 100; i++) {
		ASSERT_THAT(map.value(i), Eq(i));
	}
}

TEST(Day5Test, fertilizer_map) {
	Map map;
	map.insert(49, 53, 8);
	map.insert(0, 11, 42);
	map.insert(42, 0, 7);
	map.insert(57, 7, 4);
	map.fill();

	ASSERT_THAT(map.value(81), Eq(81));
	ASSERT_THAT(map.value(53), Eq(49));
	ASSERT_THAT(map.value(57), Eq(53));
	ASSERT_THAT(map.value(52), Eq(41));
}

TEST(Day5Test, water_map) {
	Map map;
	map.insert(88, 18, 7);
	map.insert(18, 25, 70);
	map.fill();
	map.print();

	for(int i = 0; i < 18; i++) {
		ASSERT_THAT(map.value(i), Eq(i));
	}
	for(int i = 18; i < 18+7; i++) {
		ASSERT_THAT(map.value(i), Eq(88 + i - 18));
	}
	for(int i = 25; i < 25+70; i++) {
		ASSERT_THAT(map.value(i), Eq(18 + i - 25));
	}
	for(int i = 25+70; i < 25+170; i++) {
		ASSERT_THAT(map.value(i), Eq(i));
	}
}

TEST(Day5Test, range_value_1) {
	Map map;
	map.insert(50, 98, 2);
	map.insert(52, 50, 48);
	map.fill();
	map.print();

	auto ranges = map.values({20, 30});
	ASSERT_THAT(ranges, ElementsAre(Range(20, 30)));

	ranges = map.values({100, 100});
	ASSERT_THAT(ranges, ElementsAre(Range(100, 100)));
}

TEST(Day5Test, range_value_2) {
	Map map;
	map.insert(50, 98, 2);
	map.insert(52, 50, 48);
	map.fill();
	map.print();

	auto ranges = map.values({20, 45});
	ASSERT_THAT(ranges, ElementsAre(
				Range(20, 30),
				Range(52, 15)
				));

	ranges = map.values({98, 100});
	ASSERT_THAT(ranges, ElementsAre(
				Range(50, 2),
				Range(100, 98)
				));
}

TEST(Day5Test, range_value_3) {
	Map map;
	map.insert(0, 15, 37);
	map.insert(37, 52, 2);
	map.insert(39, 0, 15);
	map.fill();
	
	auto ranges = map.values({10, 43});
	ASSERT_THAT(ranges, ElementsAre(
				Range(49, 5),
				Range(0, 37),
				Range(37, 1)
				));

	ranges = map.values({10, 50});
	ASSERT_THAT(ranges, ElementsAre(
				Range(49, 5),
				Range(0, 37),
				Range(37, 2),
				Range(54, 6)
				));
}
