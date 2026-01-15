#define CATCH_CONFIG_MAIN
#include <iostream>
#include <unordered_map>
#include <vector>

#include "catch_amalgamated.hpp"

class Solution {
 public:
  std::vector<int> twoSum(std::vector<int>& nums, int target) {
    std::vector<int> results;

    std::unordered_map<int, int> u_map;

    for (int i = 0; i < nums.size(); i++) {
      int comp = target - nums[i];
      std::unordered_map<int, int>::iterator srx = u_map.find(comp);

      if (srx != u_map.end() && srx->second != i) {
        return {srx->second, i};
      }

      u_map.emplace(nums[i], i);
    }

    return {};
  }
};

TEST_CASE("Two Sum examples") {
  Solution s;

  std::vector<int> a{2, 7, 11, 15};
  auto r1 = s.twoSum(a, 9);
  REQUIRE((r1 == std::vector<int>{0, 1} || r1 == std::vector<int>{1, 0}));

  std::vector<int> b{3, 2, 4};
  auto r2 = s.twoSum(b, 6);
  REQUIRE((r2 == std::vector<int>{1, 2} || r2 == std::vector<int>{2, 1}));
}
