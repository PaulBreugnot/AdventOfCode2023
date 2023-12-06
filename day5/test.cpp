#include "gmock/gmock.h"
#include "day5.h"

using namespace testing;

// Demonstrate some basic assertions.
TEST(Day5Test, map) {
	Map map;
	map.insert(50, 98, 2);
	map.insert(52, 50, 48);

	for(unsigned long i = 0; i < 50; i++)
		ASSERT_THAT(map.value(i), Eq(i));
	for(unsigned long i = 51; i < 98; i++)
		ASSERT_THAT(map.value(i), Eq(i+2));
	ASSERT_THAT(map.value(98), Eq(50));
	ASSERT_THAT(map.value(99), Eq(51));
}

TEST(Day5Test, water) {
	Map map;
	map.insert(49, 53, 8);
	map.insert(0, 11, 42);
	map.insert(42, 0, 7);
	map.insert(57, 7, 4);

	ASSERT_THAT(map.value(81), Eq(81));
	ASSERT_THAT(map.value(53), Eq(49));
	ASSERT_THAT(map.value(57), Eq(53));
	ASSERT_THAT(map.value(52), Eq(41));
}
