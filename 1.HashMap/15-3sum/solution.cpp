#define CATCH_CONFIG_MAIN
#define DEBUG
// #define RESULT
#include <iostream>
#include <queue>
#include <vector>

#include "catch_amalgamated.hpp"

void print_debug(const std::string& statement) {
  std::cout << statement << '\n';
}

class Solution {
 public:
  std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {}
};

TEST_CASE("Input examples") {
  Solution s;

  std::vector<int> a = {-1, 0, 1, 2, -1, -4};
  std::vector<std::vector<int>> r1 = s.threeSum(a);
  std::vector<std::vector<int>> expected{{-1, -1, 2}, {-1, 0, 1}};
  CHECK(r1 == expected);
}