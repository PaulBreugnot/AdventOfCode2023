add_executable(day5 day5.cpp main.cpp)

enable_testing()

add_executable(
  day5_test
  day5.cpp
  test.cpp
)
target_link_libraries(
  day5_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(day5_test)
