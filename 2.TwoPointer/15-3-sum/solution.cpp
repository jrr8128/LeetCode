#include <cstddef>
#include <string>
#define CATCH_CONFIG_MAIN
#include <algorithm>
#include <iostream>
#include <vector>

#include "catch_amalgamated.hpp"

class Solution {
 public:
  std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    int num_size = (int)nums.size();
    if (num_size < 3) {
      return {};
    }

    std::sort(nums.begin(), nums.end());
    std::vector<std::vector<int>> results;
    results.reserve(num_size);
    for (int i = 0; i < num_size; i++) {
      if (nums[i] > 0) {
        break;
      }
      if (i + 2 < num_size && nums[i] + nums[i + 1] + nums[i + 2] > 0) {
        break;
      }
      if (i < num_size - 2 &&
          nums[i] + nums[num_size - 2] + nums[num_size - 1] < 0) {
        continue;
      }
      if (i > 0 && nums[i] == nums[i - 1]) {
        continue;
      }

      int left_index = i + 1;
      int right_index = num_size - 1;
      while (left_index < right_index) {
        int sum = nums[i] + nums[left_index] + nums[right_index];
        if (sum == 0) {
          results.push_back({nums[i], nums[left_index], nums[right_index]});
          left_index++;
          right_index--;
          while (left_index < right_index &&
                 nums[left_index] == nums[left_index - 1]) {
            left_index++;
          }
          while (left_index < right_index &&
                 nums[right_index] == nums[right_index + 1]) {
            right_index--;
          }
        } else if (sum < 0) {
          left_index++;
        } else if (sum > 0) {
          right_index--;
        }
      }
    }
    return results;
  }
};

TEST_CASE("Three Sum examples") {
  auto norm = [](std::vector<std::vector<int>> v) {
    for (auto& t : v) std::sort(t.begin(), t.end());
    std::sort(v.begin(), v.end());
    return v;
  };

  Solution s;
  std::vector<int> input;
  std::vector<std::vector<int>> expected;

  input = {-1, 0, 1, 2, -1, -4};
  auto r1 = norm(s.threeSum(input));
  expected = norm(std::vector<std::vector<int>>{std::vector<int>{-1, -1, 2},
                                                std::vector<int>{-1, 0, 1}});
  CHECK(r1 == expected);

  input = {0, 1, 1};
  auto r2 = norm(s.threeSum(input));
  CHECK(r2.empty());

  input = {0, 0, 0};
  auto r3 = norm(s.threeSum(input));
  expected = norm(std::vector<std::vector<int>>{std::vector<int>{0, 0, 0}});
  CHECK(r3 == expected);

  input = {-100, -70, -60, 110, 120, 130, 160};
  auto r4 = norm(s.threeSum(input));
  expected = norm(std::vector<std::vector<int>>{
      std::vector<int>{-100, -60, 160}, std::vector<int>{-70, -60, 130}});
  CHECK(r4 == expected);

  input = {1, 2, 0, 1, 0, 0, 0, 0};
  auto r5 = norm(s.threeSum(input));
  expected = norm(std::vector<std::vector<int>>{std::vector<int>{0, 0, 0}});
  CHECK(r5 == expected);
}