#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>

#include "catch_amalgamated.hpp"

std::string manacher_preprocess(const std::string& input) {
  // Sentinel characters @ and $ for start and end to help with boundary checks
  // Adding in #'s makes the string length odd (so we don't have to worry about
  // even/odd case) i.e. "aba" -> "@#a#b#a#$" (length: 3 -> 9); or "bb" ->
  // "@#b#b#$" (length 2 -> 7)
  std::string manacher_string;
  manacher_string.reserve(
      2 * input.size() +
      3);  // one # for each char, and then one # in the beginning + @ and $
  manacher_string.push_back('@');  // start sentinel
  manacher_string.push_back('#');  // first #
  for (char character : input) {
    manacher_string.push_back(character);
    manacher_string.push_back('#');
  }
  manacher_string.push_back('$');

  // std::cout << "Manacher String constructed: " << manacher_string <<
  // std::endl;
  return manacher_string;
}

std::vector<std::string> build_result_strings(const std::string& manacher_input,
                                              const std::vector<int>& radii,
                                              const int size) {
  // DEBUG Checking build result strings entry
  // std::cout << "Build result strings helper called" << std::endl;
  std::vector<std::string> results;

  for (int index = 2; index < static_cast<int>(radii.size()); index++) {
    if (manacher_input[index] == '$' ||
        radii[index] + index > static_cast<int>(manacher_input.size())) {
      break;
    }
    // DEBUG checking in for loop
    // std::cout << "radii[" << index << "] == " << size << "?" << std::endl;
    if (radii[index] == size) {
      std::string result;
      result.reserve(2 * radii[index] + 1);
      for (int char_index = index - radii[index];
           char_index <= index + radii[index]; char_index++) {
        result.push_back(manacher_input[char_index]);
      }
      // std::cout << "Result string before removal of #: " << result <<
      // std::endl; std::erase(result, '#');
      results.push_back(result);
      // std::cout << "Added " << result << " to results vector" << std::endl;
    }
  }
  return results;
}

std::vector<std::string> manacher_algorithm(const std::string& manacher_input) {
  int left_bound = 0;
  int right_bound = 0;
  int input_size = static_cast<int>(manacher_input.size());
  std::vector<int> manacher_radii(input_size, 0);
  int largest_size = 0;

  // DEBUG Manacher Algorithm
  // std::cout << "Manacher string: " << manacher_input << ", size: " <<
  // input_size
  //           << std::endl;

  // @#...#$ <- no reason to check these for palindromes
  for (int index = 2; index <= input_size - 2; index++) {
    // Mirror calculation
    int mirror_index = left_bound + right_bound - index;
    // Mirror optimization first; initialize manacher_radii with this line
    if (index < right_bound) {
      manacher_radii[index] =
          std::min(right_bound - index, manacher_radii[mirror_index]);
    } else {
      manacher_radii[index] = 0;
    }

    // DEBUG For loop 1
    // std::cout << "Index: " << index << ", mirror index: " << mirror_index
    //           << std::endl;
    // std::cout << "Manacher radius @index: " << manacher_radii[index]
    //           << std::endl;

    // Expand the palindrome centered at index - if we get same letters then we
    // can increase the radius
    while (manacher_input[index + 1 + manacher_radii[index]] ==
           manacher_input[index - 1 - manacher_radii[index]]) {
      // # DEBUG While loop
      // std::cout << "Comparing: "
      //           << manacher_input[index + 1 + manacher_radii[index]] << " to
      //           "
      //           << manacher_input[index - 1 - manacher_radii[index]];
      ++manacher_radii[index];
      // std::cout << " ; manacher_radii[" << index << "] now -> "
      //           << manacher_radii[index] << std::endl;
    }

    // Need to update bounds if we expanded
    if (index + manacher_radii[index] > right_bound) {
      left_bound = index - manacher_radii[index];
      right_bound = index + manacher_radii[index];
      // DEBUG Update bounds
      // std::cout << "Need to expand bounds, new left_bound: " << left_bound
      //           << ", new right_bound: " << right_bound << std::endl;
    }

    if (manacher_radii[index] > largest_size) {
      // DEBUG Update Largest Size
      // std::cout << "Update Largest size from: " << largest_size << " to "
      //           << manacher_radii[index] << std::endl;
      largest_size = manacher_radii[index];
    }

    if (right_bound == input_size - 2) {
      // // DEBUG Whole string is palindrome check
      // std::cout << "right_bound == input_size - 2 = " << input_size - 2
      //           << std::endl;
      break;
    }
    std::cout << std::endl;
  }

  std::vector<std::string> results;
  results = build_result_strings(manacher_input, manacher_radii, largest_size);
  return results;
}

class Solution {
 public:
  std::string longestPalindrome(std::string input) {
    // Using Manacher's Algorithm for O(n) complexity
    // Need to create new string s.t. there is a # (or any other non-character)
    // between each character and before/after
    if (input.empty()) {
      return "";
    }
    // std::cout << "Constructing manacher string..." << std::endl;
    std::string manacher_string = manacher_preprocess(input);
    // std::cout << "Starting Manacher algorithm" << std::endl;
    std::vector<std::string> result = manacher_algorithm(manacher_string);
    // std::cout << "Returning first result: " << result[0] << std::endl
    //           << std::endl;
    return result[0];
  }
};

TEST_CASE("String Examples") {
  Solution solution;

  struct Case {
    std::string input;
    std::vector<std::string> expected_out;
  };

  std::vector<Case> cases = {
      {"babad", {"bab", "aba"}},
      {"cbbd", {"bb"}},
      {"", {""}},
      {"1abccba1", {"1abccba1"}},
      {"cbbdefflmnopponml", {"lmnopponml"}},
  };

  for (const Case& test_case : cases) {
    const std::string result = solution.longestPalindrome(test_case.input);
    CAPTURE(test_case.input, result);
    const std::vector<std::string>& expected = test_case.expected_out;
    const bool is_expected =
        (std::find(test_case.expected_out.begin(), test_case.expected_out.end(),
                   result) != expected.end());
    CHECK(is_expected);
  }
}