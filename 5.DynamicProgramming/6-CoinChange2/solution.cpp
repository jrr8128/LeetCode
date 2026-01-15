#define CATCH_CONFIG_MAIN
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>

#include "catch_amalgamated.hpp"

class Solution {
 public:
  int change(int amount, const std::vector<int>& coins) {
    // By convention: only 1 way to get amount 0, by not using any coins
    if (amount == 0) {
      return 1;
    }
    if (coins.empty()) {
      return 0;
    }

    if (amount < coins[0]) {
      return 0;
    }
    if (amount == coins[0]) {
      return 1;
    }

    // Check: GCD for edge cases, checking all coins < amount
    int g = 0;
    bool has_amount = false;
    for (int coin : coins) {
      if (coin == amount) {
        has_amount = true;
        continue;
      }
      if (coin < amount) {
        g = std::gcd(g, coin);
      }
    }
    // By previous checks g != 0, so if gcd gives a remainder then no
    // coin combo can add to the amount except for if the amount itself is a
    // coin
    if (g != 0 && amount % g != 0) {
      if (has_amount) {
        return 1;
      }
      return 0;
    }

    // dp[a] = # combinations to make sum a using only coins processed so far.
    // Base: dp[0]=1 (one empty way).
    //
    // Processing coin c:
    // We sweep a upward (a=c..amount). At update time, dp[a-c] already equals
    // “# ways to make (a-c) using processed coins” (including any number of c,
    // because dp[a-c] may have been updated earlier in this same coin pass).
    // Each way counted in dp[a-c] yields a distinct way to make a by appending
    // one c. Conversely, every way to make a that uses at least one c maps
    // uniquely back to a way to make (a-c) by removing one c. So dp[a] +=
    // dp[a-c] counts exactly the new combinations that use c at least once,
    // without missing or double-counting.
    //
    // Order-independence: coins are processed outermost, so combinations are
    // built in nondecreasing coin order; permutations aren’t created because
    // earlier coins never run again to “reorder” a combination.
    std::vector<int> count_by_amount(amount + 1, 0);
    count_by_amount[0] = 1;
    for (int coin_index = 0; coin_index < static_cast<int>(coins.size());
         coin_index++) {
      if (coins[coin_index] > amount) {
        // DEBUG
        continue;
      }
      for (int count_index = coins[coin_index]; count_index <= amount;
           count_index++) {
        count_by_amount[count_index] +=
            count_by_amount[count_index - coins[coin_index]];
      }
    }
    return count_by_amount[amount];
  }
};

TEST_CASE("Input Examples") {
  Solution solution;

  struct Case {
    int amount;
    std::vector<int> coins;
    int expected;
  };

  std::vector<Case> cases = {
      {5, {1, 2, 5}, 4},
      {3, {2}, 0},
      {10, {10}, 1},
      {0, {7}, 1},
      {4681,
       {2,   4,   6,    8,    10,   12,  14,  16,  18,  20,  22,  24,  26,  28,
        30,  32,  34,   36,   38,   40,  42,  44,  46,  48,  50,  52,  54,  56,
        58,  60,  62,   64,   66,   68,  70,  72,  74,  76,  78,  80,  82,  84,
        86,  88,  90,   92,   94,   96,  98,  100, 102, 104, 106, 108, 110, 112,
        114, 116, 118,  120,  122,  124, 126, 128, 130, 132, 134, 136, 138, 140,
        142, 144, 146,  148,  150,  152, 154, 156, 158, 160, 162, 164, 166, 168,
        170, 172, 174,  176,  178,  180, 182, 184, 186, 188, 190, 192, 194, 196,
        198, 200, 202,  204,  206,  208, 210, 212, 214, 216, 218, 220, 222, 224,
        226, 228, 230,  232,  234,  236, 238, 240, 242, 244, 246, 248, 250, 252,
        254, 256, 258,  260,  262,  264, 266, 268, 270, 272, 274, 276, 278, 280,
        282, 284, 286,  288,  290,  292, 294, 296, 298, 300, 302, 304, 306, 308,
        310, 312, 314,  316,  318,  320, 322, 324, 326, 328, 330, 332, 334, 336,
        338, 340, 342,  344,  346,  348, 350, 352, 354, 356, 358, 360, 362, 364,
        366, 368, 370,  372,  374,  376, 378, 380, 382, 384, 386, 388, 390, 392,
        394, 396, 398,  400,  402,  404, 406, 408, 410, 412, 414, 416, 418, 420,
        422, 424, 426,  428,  430,  432, 434, 436, 438, 440, 442, 444, 446, 448,
        450, 452, 454,  456,  458,  460, 462, 464, 466, 468, 470, 472, 474, 476,
        478, 480, 482,  484,  486,  488, 490, 492, 494, 496, 498, 500, 502, 504,
        506, 508, 510,  512,  514,  516, 518, 520, 522, 524, 526, 528, 530, 532,
        534, 536, 538,  540,  542,  544, 546, 548, 550, 552, 554, 556, 558, 560,
        562, 564, 566,  568,  570,  572, 574, 576, 578, 580, 582, 584, 586, 588,
        780, 936, 1170, 1560, 2340, 4680},
       0},
      {4999,
       {2,   4,   6,   8,   10,  12,  14,  16,  18,  20,  22,  24,  26,  28,
        30,  32,  34,  36,  38,  40,  42,  44,  46,  48,  50,  52,  54,  56,
        58,  60,  62,  64,  66,  68,  70,  72,  74,  76,  78,  80,  82,  84,
        86,  88,  90,  92,  94,  96,  98,  100, 102, 104, 106, 108, 110, 112,
        114, 116, 118, 120, 122, 124, 126, 128, 130, 132, 134, 136, 138, 140,
        142, 144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 166, 168,
        170, 172, 174, 176, 178, 180, 182, 184, 186, 188, 190, 192, 194, 196,
        198, 200, 202, 204, 206, 208, 210, 212, 214, 216, 218, 220, 222, 224,
        226, 228, 230, 232, 234, 236, 238, 240, 242, 244, 246, 248, 250, 252,
        254, 256, 258, 260, 262, 264, 266, 268, 270, 272, 274, 276, 278, 280,
        282, 284, 286, 288, 290, 292, 294, 296, 298, 300, 302, 304, 306, 308,
        310, 312, 314, 316, 318, 320, 322, 324, 326, 328, 330, 332, 334, 336,
        338, 340, 342, 344, 346, 348, 350, 352, 354, 356, 358, 360, 362, 364,
        366, 368, 370, 372, 374, 376, 378, 380, 382, 384, 386, 388, 390, 392,
        394, 396, 398, 400, 402, 404, 406, 408, 410, 412, 414, 416, 418, 420,
        422, 424, 426, 428, 430, 432, 434, 436, 438, 440, 442, 444, 446, 448,
        450, 452, 454, 456, 458, 460, 462, 464, 466, 468, 470, 472, 474, 476,
        478, 480, 482, 484, 486, 488, 490, 492, 494, 496, 498, 500, 502, 504,
        506, 508, 510, 512, 514, 516, 518, 520, 522, 524, 526, 528, 530, 532,
        534, 536, 538, 540, 542, 544, 546, 548, 550, 552, 554, 556, 558, 560,
        562, 564, 566, 568, 570, 572, 574, 576, 578, 580, 582, 584, 586, 588,
        590, 592, 594, 596, 598, 4999},
       1},
  };

  for (const Case& test_case : cases) {
    const int result = solution.change(test_case.amount, test_case.coins);
    CAPTURE(test_case.amount, test_case.coins, result);
    CHECK(result == test_case.expected);
  }
}