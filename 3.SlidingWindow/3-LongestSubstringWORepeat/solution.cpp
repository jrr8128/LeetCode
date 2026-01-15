#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>

#include "catch_amalgamated.hpp"

class Solution {
 public:
  int lengthOfLongestSubstring(const std::string& string) {
    int longest = 0;
    int left_index = 0;
    std::array<int, 256> array;
    array.fill(-1);
    for (int index = 0; index < string.size(); index++) {
      unsigned char unsigned_char = static_cast<unsigned char>(string[index]);
      if (array[unsigned_char] != -1) {
        if (array[unsigned_char] >= left_index) {
          left_index = array[unsigned_char] + 1;
        }
      }
      array[unsigned_char] = index;
      if (longest < (index - left_index) + 1) {
        longest = (index - left_index) + 1;
      }
    }
    return int(longest);
  }
};

TEST_CASE("String examples") {
  Solution solution;

  std::string a = "abcabcbb";
  int r1 = solution.lengthOfLongestSubstring(a);
  CHECK(r1 == 3);

  std::string b = "bbbbb";
  int r2 = solution.lengthOfLongestSubstring(b);
  CHECK(r2 == 1);

  std::string c = "pwwkew";
  int r3 = solution.lengthOfLongestSubstring(c);
  CHECK(r3 == 3);

  std::string d = "cbaabc";
  int r4 = solution.lengthOfLongestSubstring(d);
  CHECK(r4 == 3);

  std::string e = "1ac2er3";
  int r5 = solution.lengthOfLongestSubstring(e);
  CHECK(r5 == 7);

  std::string f = "";
  int r6 = solution.lengthOfLongestSubstring(f);
  CHECK(r6 == 0);

  std::string g = " ";
  int r7 = solution.lengthOfLongestSubstring(g);
  CHECK(r7 == 1);

  std::string h = "12 4 5";
  int r8 = solution.lengthOfLongestSubstring(h);
  CHECK(r8 == 4);

  std::string i = "  ";
  int r9 = solution.lengthOfLongestSubstring(i);
  CHECK(r9 == 1);

  std::string j = "eeydgwdykpv";
  int r10 = solution.lengthOfLongestSubstring(j);
  CHECK(r10 == 7);

  std::string k = "aabaab!bb";
  int r11 = solution.lengthOfLongestSubstring(k);
  CHECK(r11 == 3);
}