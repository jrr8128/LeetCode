#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>

#include "catch_amalgamated.hpp"

static double binary_recursion(const std::vector<int>& small_array,
                               const std::vector<int>& big_array, int low,
                               int high) {
  int i = 0;
  int j = 0;
  int m = int(small_array.size());
  int n = int(big_array.size());
  int NEGINF = std::numeric_limits<int>::min();
  int POSINF = std::numeric_limits<int>::max();

  if (high >= low) {
    i = low + (high - low) / 2;
    j = ((m + n + 1) / 2) - i;

    int small_left;
    if (i == 0) {
      small_left = NEGINF;
    } else {
      small_left = small_array[i - 1];
    }

    int small_right;
    if (i == m) {
      small_right = POSINF;
    } else {
      small_right = small_array[i];
    }

    int big_left;
    if (j == 0) {
      big_left = NEGINF;
    } else {
      big_left = big_array[j - 1];
    }

    int big_right;
    if (j == n) {
      big_right = POSINF;
    } else {
      big_right = big_array[j];
    }

    if (small_left <= big_right && big_left <= small_right) {
      int max_left;
      if (small_left >= big_left) {
        max_left = small_left;
      } else {
        max_left = big_left;
      }
      if (((m + n) & 1) == 0) {
        int min_right;
        if (small_right <= big_right) {
          min_right = small_right;
        } else {
          min_right = big_right;
        }
        return double((max_left + min_right) / 2.0);
      } else {
        return max_left;
      }
    }

    if (small_left > big_right) {
      return binary_recursion(small_array, big_array, low, i - 1);
    }
    return binary_recursion(small_array, big_array, i + 1, high);
  }
  return -1;
}

class Solution {
 public:
  double findMedianSortedArrays(const std::vector<int>& nums1,
                                const std::vector<int>& nums2) {
    // int middle = (m + n + 1) / 2;
    int low;
    int high;
    double result = -1;

    const std::vector<int>* small_array = &nums1;
    const std::vector<int>* big_array = &nums2;

    if (nums1.size() > nums2.size()) {
      small_array = &nums2;
      big_array = &nums1;
    }

    int small_size = (int)small_array->size();
    int big_size = (int)big_array->size();
    int middle = (small_size + big_size + 1) / 2;

    low = std::max(0, middle - big_size);
    high = std::min(small_size, middle);
    result = binary_recursion(*small_array, *big_array, low, high);
    return result;
  }
};

TEST_CASE("Array examples") {
  Solution solution;

  std::vector<int> a1 = {1, 3};
  std::vector<int> a2 = {2};
  double r1 = solution.findMedianSortedArrays(a1, a2);
  CHECK(r1 == 2.00000);

  std::vector<int> b1 = {1, 2};
  std::vector<int> b2 = {3, 4};
  double r2 = solution.findMedianSortedArrays(b1, b2);
  CHECK(r2 == 2.50000);
}