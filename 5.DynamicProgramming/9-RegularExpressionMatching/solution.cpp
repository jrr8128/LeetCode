#define CATCH_CONFIG_MAIN
// #define DEBUG
// #define RESULT
#include <iostream>

#include "catch_amalgamated.hpp"

void print_debug(const std::string& statement) {
  std::cout << statement << '\n';
}

void print_matrix(const std::string& s, const std::string& p,
                  const std::vector<std::vector<uint8_t>>& sp) {
  const int rows = static_cast<int>(p.size());
  const int cols = static_cast<int>(s.size());

  auto s_prefix = [&](int c) -> std::string {
    return (c == 0) ? "ε" : s.substr(0, c);
  };
  auto p_prefix = [&](int r) -> std::string {
    return (r == 0) ? "ε" : p.substr(0, r);
  };

  const int cell_w = 3;  // width for 0/1 cell
  const int hdr_w =
      std::max(3, cols + 1);  // minimum header width for row labels

  // Top header: column prefixes of s
  std::cout << std::setw(hdr_w) << "" << "  ";
  for (int c = 0; c <= cols; ++c) {
    std::cout << std::setw(cell_w) << (c == 0 ? "ε" : std::to_string(c));
  }
  std::cout << "\n";

  std::cout << std::setw(hdr_w) << "" << "  ";
  for (int c = 0; c <= cols; ++c) {
    std::cout << std::setw(cell_w) << (sp[0].size() ? "" : "");
  }
  std::cout << "\n";

  // Second header: actual prefix strings (may get wide; keep it readable)
  std::cout << std::setw(hdr_w) << "" << "  ";
  for (int c = 0; c <= cols; ++c) {
    // show only last 1 char of the prefix (or ε) to avoid huge columns
    std::string label = (c == 0) ? "ε" : std::string(1, s[c - 1]);
    std::cout << std::setw(cell_w) << label;
  }
  std::cout << "\n";

  // Rows: prefix of p on the left, dp values across
  for (int r = 0; r <= rows; ++r) {
    // Row label: show prefix length + last char (or ε)
    std::string label;
    if (r == 0) {
      label = "ε";
    } else {
      label = std::to_string(r) + ":" + std::string(1, p[r - 1]);
    }
    std::cout << std::setw(hdr_w) << label << "  ";

    for (int c = 0; c <= cols; ++c) {
      std::cout << std::setw(cell_w) << static_cast<int>(sp[r][c]);
    }
    std::cout << "\n";
  }
}

int check_zeros(const std::string& s, const std::string& p) {
  int columns = static_cast<int>(s.size());
  int rows = static_cast<int>(p.size());
  if (columns == 0 && rows == 0) {
#ifdef DEBUG
    print_debug("S and P sizes both == 0; returning true.");
#endif
    return 1;
  }
  if (rows == 0 && columns > 0) {
#ifdef DEBUG
    print_debug("P empty, S not; returning false.");
#endif
    return 0;
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
  std::string debug = "P: " + p + " min_length: " + std::to_string(min_length) +
                      " S: " + std::to_string(columns);
  print_debug(debug);
#endif
  if (columns < min_length) {
    return 0;
  }
  return -1;
}

class Solution {
 public:
  bool isMatch(std::string s, std::string p) {
    int zero_check = check_zeros(s, p);
    if (zero_check == 1) {
      return true;
    }
    if (zero_check == 0) {
      return false;
    }
    size_t first_star = p.find('*');
    int erase_count = 0;
    if (first_star != std::string::npos && first_star > 1) {
#ifdef DEBUG
      print_debug("First star at pos: " + std::to_string(first_star));
#endif
      for (size_t index = 0; index < first_star - 1; index++) {
        if (index < s.size()) {
#ifdef DEBUG
          print_debug("Comparing p[" + std::to_string(index) +
                      "]: " + std::string(1, p[index]) + " to s[" +
                      std::to_string(index) + "]: " + std::string(1, s[index]));
#endif
          if (p[index] == '.' || p[index] == s[index]) {
            erase_count++;
          }
          if (p[index] != '.' && p[index] != s[index]) {
            return false;
          }
        }
      }
      s.erase(0, erase_count);
      p.erase(0, erase_count);
      while (p.back() != '*') {
        if (p.back() != '.' && p.back() != s.back()) {
          return false;
        }
        if (p.back() == '.' || p.back() == s.back()) {
          s.pop_back();
          p.pop_back();
        }
      }
#ifdef DEBUG
      print_debug("New s: " + s + ", New p: " + p);
#endif
    }
    assert(p[0] != '*');
    zero_check = check_zeros(s, p);
    if (zero_check == 1) {
      return true;
    }
    if (zero_check == 0) {
      return false;
    }

    size_t rows = p.size();
    size_t columns = s.size();

    std::vector<std::vector<uint8_t>> sp_matrix(
        rows + 1, std::vector<uint8_t>(columns + 1, 0));

#ifdef DEBUG
    print_debug("Entering For Loop");
#endif

    for (int row_index = 0; row_index <= rows; row_index++) {
      for (int col_index = 0; col_index <= columns; col_index++) {
#ifdef DEBUG
        print_debug("Row Index: " + std::to_string(row_index) +
                    ", Column Index: " + std::to_string(col_index));
#endif
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
        // for sp_matrix[row][col] if p[row-1] == '*': (remember that
        // sp_matrix has + 1 row/col so have to -1 to offset when looking at
        // the strings) 2 cases: Zero occurences or One or More occurences 1st
        // case: Zero occurences: pretend x* matches nothing, so need to
        // ignore both x and * -> look at sp_matrix[row-2][col] ex: p = "a.*b"
        // so we would just look at "a" here, if sp_matrix[row-2][col] == true
        // then we can accept that and move on Otherwise we look at 2nd case:
        // One or more occurences: curr string char c matches p[row-2] (x or
        // .) then x* can treat this char as one of the x*'s so look at the
        // previous string char c in the same row and take that value

        // ex: p = "a.*b" s = "aab" -> get to * at col = 0 -> empty -> can't
        // look back on earlier char's in the p string, so check p-2 to see if
        // its empty we already did that calculation earlier so we just check
        // if its true, if it is when we set this cell to true and are done
        // col = 1
        // -> "a"; well here we know p-2 is "a" and "a" vs "a" is true; done
        // col = 2 -> s= "aa"; sp_matric[row-2][col] is false p = "a" vs s=
        // "aa" is false; so need to check 2nd case: look back in the previous
        // col (prefix string) so "a" which is true so now since we just need
        // to make sure that the previous string char = "a" matches up with
        // either . or x in p in this case the previous a was consumed by a in
        // p, this a is free to be used by the .* and so we set it to be true
        // but if p = ab* instead of a.* then a would mismatch with b and this
        // would be false

#ifdef DEBUG
        print_debug("P[row_index - 1]: " + p[row_index - 1]);
#endif

        assert(row_index > 0);
        if (p[row_index - 1] == '*') {
          assert(row_index - 2 >= 0);
          if (col_index == 0 && sp_matrix[row_index - 2][col_index] == 0) {
            sp_matrix[row_index][col_index] =
                sp_matrix[row_index - 2][col_index];
#ifdef DEBUG
            print_debug("Case 1: Skip triggered, but in col_index == 0");
#endif
            continue;
          }
          if (sp_matrix[row_index - 2][col_index] == 1) {
            sp_matrix[row_index][col_index] = 1;
#ifdef DEBUG
            print_debug("Case 1: Skip triggered");
#endif
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

#ifdef DEBUG
          print_debug("Case 2: Consume triggered; p[r-2]: " +
                      std::string(1, p[row_index - 2]) +
                      "s[c-1]: " + std::string(1, s[col_index - 1]));
#endif
          continue;
        }

        // If current p char is . or x just check against the current s char

        assert(col_index > 0);
        if (sp_matrix[row_index - 1][col_index - 1] == 1) {
          if (p[row_index - 1] == '.') {
            sp_matrix[row_index][col_index] = 1;
#ifdef DEBUG
            print_debug("p[r-1]: " + std::string(1, p[row_index - 1]) +
                        " , prev sp[r-1][c-1] == 1");
#endif
            continue;
          }
          if (p[row_index - 1] != '.') {
            if (p[row_index - 1] == s[col_index - 1]) {
              sp_matrix[row_index][col_index] = 1;
            } else {
              sp_matrix[row_index][col_index] = 0;
            }
#ifdef DEBUG
            print_debug("p[r-1]: != '.', checking p[r-1]: " +
                        std::string(1, p[row_index - 1]) +
                        " == " + std::string(1, s[col_index - 1]));
#endif
            continue;
          }
        } else {
#ifdef DEBUG
          print_debug("All cases failed; setting sp[r][c] = 0");
#endif
          sp_matrix[row_index][col_index] = 0;
        }
      }
    }
#ifdef RESULT
    print_matrix(s, p, sp_matrix);
    print_debug("sp_matrix[r][c]: " + std::to_string(sp_matrix[rows][columns]));
#endif
    if (sp_matrix[rows][columns] == 1) {
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

  SP leet1 = {"mississippi", "mis*is*p*."};
  bool l1 = s.isMatch(leet1.s, leet1.p);
  CHECK(l1 == false);

  SP leet2 = {"aaba", "ab*c"};
  bool l2 = s.isMatch(leet2.s, leet2.p);
  CHECK(l2 == false);

  SP leet3 = {"mississippi", "mis*is*ip*."};
  bool l3 = s.isMatch(leet3.s, leet3.p);
  CHECK(l3 == true);

  SP a = {"aaaaaab", ".*b"};
  bool r1 = s.isMatch(a.s, a.p);
  CHECK(r1 == true);

  SP b = {"aa", "a"};
  bool r2 = s.isMatch(b.s, b.p);
  CHECK(r2 == false);

  SP c = {"aa", "a*"};
  bool r3 = s.isMatch(c.s, c.p);
  CHECK(r3 == true);

  SP d = {"ab", ".*"};
  bool r4 = s.isMatch(d.s, d.p);
  CHECK(r4 == true);

  SP e1 = {"", ".*"};
  bool r5 = s.isMatch(e1.s, e1.p);
  CHECK(r5 == true);

  SP e2 = {"", "a*"};
  bool r6 = s.isMatch(e2.s, e2.p);
  CHECK(r6 == true);

  SP f = {"", ""};
  bool r7 = s.isMatch(f.s, f.p);
  CHECK(r7 == true);

  SP g = {"abbbbab", "ab*"};
  bool r8 = s.isMatch(g.s, g.p);
  CHECK(r8 == false);
}
