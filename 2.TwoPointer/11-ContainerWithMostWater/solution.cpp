#define CATCH_CONFIG_MAIN
#define DEBUG
// #define RESULT
#include <iostream>
#include <vector>

#include "catch_amalgamated.hpp"

void print_debug(const std::string& statement) {
  std::cout << statement << '\n';
}

class Solution {
 public:
  int maxArea(std::vector<int>& height) {
    int input_size = static_cast<int>(height.size());
#ifdef DEBUG
    print_debug("Input size: " + std::to_string(input_size));
#endif

    if (input_size == 0 || input_size == 1) {
      return 0;
    }
    if (input_size == 2) {
#ifdef DEBUG
      print_debug("Checking front vs back for input size == 2: " +
                  std::to_string(height.front()) + " vs " +
                  std::to_string(height.front()));
#endif
      if (height.front() < height.back()) {
        return height.front();
      } else {
        return height.back();
      }
    }

#ifdef DEBUG
    print_debug("Initial Checks passed; generating pointers");
#endif
    int max_water = 0;
    int curr_water = 0;
    size_t left_index = 0;
    size_t right_index = height.size() - 1;
    int left_height = 0;
    int right_height = 0;
    size_t index_diff = 0;
    while (left_index < right_index) {
      assert(left_index < height.size());
      assert(right_index >= 0);
      left_height = height.at(left_index);
      right_height = height.at(right_index);
      index_diff = right_index - left_index;
      if (height.at(left_index) <= height.at(right_index)) {
        curr_water = static_cast<int>(left_height * index_diff);
        left_index++;
      } else {
        curr_water = static_cast<int>(right_height * index_diff);
        right_index--;
      }
      if (curr_water > max_water) {
        max_water = curr_water;
      }
    }
    return max_water;
  }
};

// Constraints:
//     n == height.length
//     2 <= n <= 105
//     0 <= height[i] <= 104

TEST_CASE("Input examples") {
  Solution s;

  std::vector<int> a = {1, 8, 6, 2, 5, 4, 8, 3, 7};
  int r1 = s.maxArea(a);
  CHECK(r1 == 49);

  std::vector<int> b = {1, 1};
  int r2 = s.maxArea(b);
  CHECK(r2 == 1);
}
