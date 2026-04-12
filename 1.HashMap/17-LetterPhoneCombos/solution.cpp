#include <cstddef>
#include <string>
#define CATCH_CONFIG_MAIN
#include <algorithm>
#include <iostream>
#include <vector>

#include "catch_amalgamated.hpp"

class Solution {
 public:
  std::vector<std::string> letterCombinations(std::string digits) {}
};

TEST_CASE("Letter Combo Examples") {
  auto norm = [](std::vector<std::string> v) {
    for (auto& t : v) std::sort(t.begin(), t.end());
    std::sort(v.begin(), v.end());
    return v;
  };

  Solution s;
  std::string input;
  std::vector<std::string> expected;

  input = {"23"};
  auto r1 = norm(s.letterCombinations(input));
  expected = norm(std::vector<std::string>{"ad", "ae", "af", "bd", "be", "bf",
                                           "cd", "ce", "cf"});
  CHECK(r1 == expected);

  input = {"2"};
  auto r2 = norm(s.letterCombinations(input));
  expected = norm(std::vector<std::string>{"a", "b", "c"});
  CHECK(r2 == expected);

  input = "";
  auto r3 = norm(s.letterCombinations(input));
  CHECK(r3.empty());
}