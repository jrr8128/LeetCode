#define CATCH_CONFIG_MAIN
#define DEBUG
#include <iostream>

#include "catch_amalgamated.hpp"

void print_debug(const std::string& statement) {
  std::cerr << statement << std::endl;
}

class Solution {
 public:
  bool isMatch(std::string s, std::string p) {
    int columns = static_cast<int>(s.size());
    int rows = static_cast<int>(p.size());
    if (columns == 0 && rows == 0) {
#ifdef DEBUG
      print_debug("S and P sizes both == 0; returning true.");
#endif
      return true;
    }
    if (rows == 0 && columns > 0) {
#ifdef DEBUG
      print_debug("P empty, S not; returning false.");
#endif
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
#ifdef DEBUG
    std::string debug = "P: " + p +
                        " min_length: " + std::to_string(min_length) +
                        " S: " + std::to_string(columns);
    print_debug(debug);
#endif
    if (columns < min_length) {
      return false;
    }

    std::vector<std::vector<uint8_t>> sp_matrix(
        rows + 1, std::vector<uint8_t>(columns + 1, 0));

    for (int row_index = 0; row_index <= rows; row_index++) {
      for (int col_index = 0; col_index <= columns; col_index++) {
        if (row_index == 0 && col_index == 0) {
          sp_matrix[row_index][col_index] = 1;
          // empty string vs empty string is always true
          continue;  // no need for any other checks
        }
        if (row_index == 0 && col_index > 0) {
          sp_matrix[row_index][col_index] = 0;
          continue;
        }
        if (row_index > 0 && col_index == 0) {
          if (p[row_index - 1] != '*') {
            sp_matrix[row_index][col_index] = 0;
          } else {
            sp_matrix[row_index][col_index] =
                sp_matrix[row_index - 2][col_index];
          }
          continue;
        }

        // * expands the preceding token x into x* ('zero or more x')
        // for sp_matrix[row][col] if p[row-1] == '*': (remember that sp_matrix
        // has + 1 row/col so have to -1 to offset when looking at the strings)
        // 2 cases: Zero occurences or One or More occurences
        // 1st case: Zero occurences: pretend x* matches nothing, so need to
        // ignore both x and * -> look at sp_matrix[row-2][col] ex: p = "a.*b"
        // so we would just look at "a" here, if sp_matrix[row-2][col] == true
        // then we can accept that and move on Otherwise we look at 2nd case:
        // One or more occurences: curr string char c matches p[row-2] (x or .)
        // then x* can treat this char as one of the x*'s so look at the
        // previous string char c in the same row and take that value

        // ex: p = "a.*b" s = "aab" -> get to * at col = 0 -> empty -> can't
        // look back on earlier char's in the p string, so check p-2 to see if
        // its empty we already did that calculation earlier so we just check if
        // its true, if it is when we set this cell to true and are done col = 1
        // -> "a"; well here we know p-2 is "a" and "a" vs "a" is true; done col
        // = 2 -> s= "aa"; sp_matric[row-2][col] is false p = "a" vs s= "aa" is
        // false; so need to check 2nd case: look back in the previous col
        // (prefix string) so "a" which is true so now since we just need to
        // make sure that the previous string char = "a" matches up with either
        // . or x in p in this case the previous a was consumed by a in p, this
        // a is free to be used by the .* and so we set it to be true but if p =
        // ab* instead of a.* then a would mismatch with b and this would be
        // false

        assert(row_index > 0);
        if (p[row_index - 1] == '*') {
          assert(row_index - 2 >= 0);
          if (col_index == 0 && sp_matrix[row_index - 2][col_index] == 0) {
            sp_matrix[row_index][col_index] =
                sp_matrix[row_index - 2][col_index];
            continue;
          }
          if (sp_matrix[row_index - 2][col_index] == 1) {
            sp_matrix[row_index][col_index] = 1;
            continue;
          }

          if (col_index > 0 && sp_matrix[row_index - 2][col_index] == 0 &&
              (sp_matrix[row_index][col_index - 1] == 1 &&
               (p[row_index - 2] == '.' ||
                p[row_index - 2] == s[col_index - 1]))) {
            sp_matrix[row_index][col_index] = 1;
          } else {
            sp_matrix[row_index][col_index] = 0;
          }
          continue;
        }

        // If current p char is . or x just check against the current s char

        assert(col_index > 0);
        if (sp_matrix[row_index - 1][col_index - 1] == 1) {
          if (p[row_index - 1] == '.') {
            sp_matrix[row_index][col_index] = 1;
            continue;
          }
          if (p[row_index - 1] != '.') {
            if (p[row_index - 1] == s[col_index - 1]) {
              sp_matrix[row_index][col_index] = 1;
              continue;
            } else {
              sp_matrix[row_index][col_index] = 0;
              continue;
            }
          }
        } else {
          sp_matrix[row_index][col_index] = 0;
        }
      }
    }
    if (sp_matrix[rows + 1][columns + 1] == 1) {
      return true;
    } else {
      return false;
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
//        .: [f][t][f]  [f]  [f]    [f]    [f]      [f]
//       .*: [t][f][f]  [f]  [f]    [f]    [f]      [f]
//      .*b: [f][f][f]  [f]  [f]    [f]    [f]      [t]
