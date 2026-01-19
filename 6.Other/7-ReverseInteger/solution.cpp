#define CATCH_CONFIG_MAIN
#include <cstdint>
#include <iostream>
#include <string>

#include "catch_amalgamated.hpp"

class Solution {
 public:
  int reverse(int x) {
    if (x == 0) {
      return 0;
    }
    int solution = 0;
    int quotient = x;
    int digit = 0;
    // 2^31 = -2147483648 <= x <= 2147483647 = 2^31 -1
    bool is_negative = false;
    if (x < 0) {
      is_negative = true;
    }

    bool check_digits = false;
    if (x < -999999999 || x > 999999999) {
      check_digits = true;
    }

    int max_digits[9] = {2, 1, 4, 7, 4, 8, 3, 6, 4};
    int index = 0;
    while (quotient != 0) {
      digit = quotient % 10;
      quotient /= 10;
      if (is_negative) {
        digit *= -1;
      }

      if (check_digits) {
        if (index >= 9) {
          if (is_negative && digit > 8) {
            return 0;
          }
          if (!is_negative && digit > 7) {
            return 0;
          }
        }

        if (index < 9) {
          if (digit > max_digits[index]) {
            return 0;
          }
          if (digit < max_digits[index]) {
            check_digits = false;
          }
        }
      }

      solution = (solution * 10) + digit;
      index++;
    }

    if (is_negative) {
      solution *= -1;
    }
    return solution;
  }
};

// class Solution {
//  public:
//   int reverse(int x) {
//     if (x == 0) {
//       return 0;
//     }
//     int x32_t = x;
//     std::vector<int> digits;
//     int remainder = 0;
//     bool is_negative = false;
//     if (x32_t < 0) {
//       is_negative = true;
//     }

//     std::cout << "entering while" << std::endl;
//     bool trailing_zero = true;
//     while (x32_t != 0) {
//       remainder = x32_t % 10;
//       std::cout << "x32: " << x32_t << ", rem: " << int(remainder) <<
//       std::endl; x32_t /= 10; std::cout << "x32 / 10 = " << x32_t <<
//       std::endl;

//       if (remainder == 0 && trailing_zero) {
//         continue;
//       }
//       if (remainder != 0) {
//         trailing_zero = false;
//       }
//       if (is_negative) {
//         remainder *= -1;
//       }
//       digits.push_back(remainder);
//     }
//     std::cout << "exited while" << std::endl << std::endl;
//     // 2^31 = -2147483648 <= x <= 2147483647 = 2^31 -1
//     bool check_digit = false;
//     int max_digits[10] = {2, 1, 4, 7, 4, 8, 3, 6, 4, 7};
//     //                    7, 4, 6, 3, 8, 4, 7, 4, 1, 2
//     if (digits.size() > 9) {
//       check_digit = true;
//     }
//     int digit;
//     int solution = 0;

//     std::cout << "entering for, x = " << x << std::endl;
//     std::cout << "size digits: " << digits.size() << std::endl;

//     for (int i = static_cast<int>(digits.size()) - 1; i >= 0; i--) {
//       std::cout << "iteration: " << i << std::endl;
//       digit =
//           digits.at(digits.size() - 1 - i);  // 123 -> start at i = 2, digit
//           = 3
//       std::cout << "digit: " << int(digit) << std::endl;
//       if (check_digit) {
//         if (i == 0) {
//           if (is_negative && digit == 9) {
//             std::cout << "return 0: is_negative = T, digit == 9" << std::endl
//                       << std::endl;
//             return 0;
//           } else if (!is_negative && digit > 7) {
//             std::cout << "return 0: is_negative = F, digit > 7" << std::endl
//                       << std::endl;
//             return 0;
//           }
//         }
//         if (i > 0) {
//           if (digit > max_digits[9 - i]) {
//             std::cout << "return 0:  i > 0 && digit: " << digit << " > "
//                       << max_digits[9 - i] << std::endl
//                       << std::endl;
//             return 0;
//           }
//           if (digit < max_digits[9 - i]) {
//             check_digit = false;
//           }
//         }
//       }
//       int digit_power = digit * int(std::pow(10, i));
//       std::cout << "digit_power + sol: " << digit_power << " + " << solution
//                 << std::endl;
//       solution += digit_power;
//       std::cout << "sol: " << solution << std::endl;
//     }
//     std::cout << "exited for" << std::endl << std::endl;
//     if (is_negative) {
//       solution *= -1;
//     }
//     return solution;
//   }
// };

TEST_CASE("Integer examples") {
  Solution s;

  std::int32_t a = 123;
  std::int32_t r1 = s.reverse(a);
  CHECK(r1 == 321);

  std::int32_t b = -123;
  std::int32_t r2 = s.reverse(b);
  CHECK(r2 == -321);

  std::int32_t c = 120;
  std::int32_t r3 = s.reverse(c);
  CHECK(r3 == 21);

  std::int32_t d = 0;
  std::int32_t r4 = s.reverse(d);
  CHECK(r4 == 0);

  std::int32_t e = 1111111119;
  std::int32_t r5 = s.reverse(e);
  CHECK(r5 == 0);

  std::int32_t f = -1111111119;
  std::int32_t r6 = s.reverse(f);
  CHECK(r6 == 0);

  std::int32_t g = -2147483412;
  std::int32_t r7 = s.reverse(g);
  CHECK(r7 == -2143847412);

  std::int32_t h = 2147483647;
  std::int32_t r8 = s.reverse(h);
  CHECK(r8 == 0);

  std::int32_t i = 1534236469;
  std::int32_t r9 = s.reverse(i);
  CHECK(r9 == 0);

  std::int32_t j = 1463847412;
  std::int32_t r10 = s.reverse(j);
  CHECK(r10 == 2147483641);

  std::int32_t k = -2147483648;
  std::int32_t r11 = s.reverse(k);
  CHECK(r11 == 0);

  std::int32_t l = -1463847412;
  std::int32_t r12 = s.reverse(l);
  CHECK(r12 == -2147483641);
}