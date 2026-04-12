#include <cstddef>
#include <string>
#define CATCH_CONFIG_MAIN
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "catch_amalgamated.hpp"

class Solution {
 public:
  std::vector<std::string> letterCombinations(std::string digits) {
    if (digits.empty()) {
      return {};
    }
    std::unordered_map<int, std::vector<char>> phone_letters{
        {'2', {'a', 'b', 'c'}}, {'3', {'d', 'e', 'f'}},
        {'4', {'g', 'h', 'i'}}, {'5', {'j', 'k', 'l'}},
        {'6', {'m', 'n', 'o'}}, {'7', {'p', 'q', 'r', 's'}},
        {'8', {'t', 'u', 'v'}}, {'9', {'w', 'x', 'y', 'z'}},
    };
    std::vector<std::string> curr_layer{""};
    std::vector<std::string> next_layer;
    for (char c : digits) {
      const std::vector<char>& letters = phone_letters[c];
      const int letters_size = letters.size();
      next_layer.resize(curr_layer.size() * letters_size);
      for (int j = 0; j < curr_layer.size(); j++) {
        for (int i = 0; i < letters_size; i++) {
          next_layer[i + (letters_size * j)] = curr_layer[j] + letters[i];
        }
      }
      curr_layer.swap(next_layer);
      next_layer.clear();
    }
    return curr_layer;
  }
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