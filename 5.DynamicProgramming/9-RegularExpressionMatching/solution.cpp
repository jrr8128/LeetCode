#define CATCH_CONFIG_MAIN
#include <iostream>

#include "catch_amalgamated.hpp"

class Solution {
 public:
  bool isMatch(std::string s, std::string p) {
    int columns = static_cast<int>(s.size());
    int rows = static_cast<int>(p.size());
    if (columns == 0 && rows == 0) {
      return true;
    }
    if (rows == 0 && columns > 0) {
      return false;
    }
    int min_length = 0;
    for (int index = 0; index < rows; index++) {
      if (p[index] == '*') {
        continue;
      }
      if (index < rows - 1 && p[index + 1] == '*') {
        continue;
      }
      min_length++;
    }
    if (columns < min_length) {
      return false;
    }

    std::vector<std::vector<uint8_t>> sp_matrix(
        rows + 1, std::vector<uint8_t>(columns + 1, 0));

    for (int row_index = 0; row_index <= rows; row_index++) {
      for (int col_index = 0; col_index <= columns; col_index++) {
      }
    }
  }
};

TEST_CASE("Input examples") {
  Solution s;

  struct SP {
    std::string s;
    std::string p;
  };

  SP a = {"aaaaaab", ".*b"};
  bool r1 = s.isMatch(a.s, a.p);
  CHECK(r1 == true);
}

// s ="aaaaaab" p =".*b"
//           0  a  aa  aaa  aaaa  aaaaa  aaaaaa  aaaaaab
// dp ->  0: [t][f][f]  [f]  [f]    [f]    [f]      [f]
//  .: [f][t][f]  [f]  [f]    [f]    [f]      [f]
// .*: [t][f][f]  [f]  [f]    [f]    [f]      [f]
//.*b: [f][f][f]  [f]  [f]    [f]    [f]      [t]
