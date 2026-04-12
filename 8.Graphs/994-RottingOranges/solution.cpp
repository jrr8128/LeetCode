#define CATCH_CONFIG_MAIN
#define DEBUG
// #define RESULT
#include <iostream>
#include <queue>
#include <vector>

#include "catch_amalgamated.hpp"

void print_debug(const std::string& statement) {
  std::cout << statement << '\n';
}

void print_grid(std::vector<std::vector<int>>& grid) {
  for (const auto& row : grid) {
    for (std::size_t j = 0; j < row.size(); ++j) {
      if (j) std::cout << ' ';
      std::cout << row[j];
    }
    std::cout << '\n';
  }
}

class Solution {
 public:
  int orangesRotting(std::vector<std::vector<int>>& grid) {
    std::vector<std::pair<size_t, size_t>> frontier;
    std::vector<std::pair<size_t, size_t>> next_frontier;
    size_t i_size = grid.size();
    size_t j_size = grid.at(0).size();  // m x n grid (square grid)

    if (i_size == 0 && j_size == 0) {
      return 0;
    }
    if (i_size == 1 && j_size == 1) {
      if (grid.at(0).at(0) == 1) {
        return -1;
      } else {
        return 0;
      }
    }

    int fresh_count = 0;
    // Need to create initial frontier
    for (size_t i = 0; i < i_size; i++) {
      for (size_t j = 0; j < j_size; j++) {
        int ij_val = grid.at(i).at(j);
        if (ij_val == 2) {
          next_frontier.push_back(std::make_pair(i, j));
        }
        if (ij_val == 1) {
          fresh_count++;
        }
      }
    }

    if (fresh_count == 0) {
      return 0;
    }
    if (next_frontier.size() == 0) {
      return -1;
    }

#ifdef DEBUG
    print_debug("Before Run: ");
    print_grid(grid);
    print_debug("Next Frontier: " + std::to_string(next_frontier.size()) +
                "\nFresh: " + std::to_string(fresh_count) + "\n");
#endif

    int iter_count = 0;

    while (!next_frontier.empty()) {
      frontier.swap(next_frontier);
      next_frontier.clear();

#ifdef DEBUG
      print_debug("Current Run: ");
      print_grid(grid);
      print_debug("Frontier: " + std::to_string(frontier.size()) +
                  "\nFresh: " + std::to_string(fresh_count) + "\n");
#endif

      while (!frontier.empty() && fresh_count > 0) {
        std::pair<size_t, size_t> curr_ij = frontier.back();
        size_t curr_i = curr_ij.first;
        size_t curr_j = curr_ij.second;
#ifdef DEBUG
        print_debug("Curr ij: " + std::to_string(curr_i) + ", " +
                    std::to_string(curr_j) + "\n");
#endif

        frontier.pop_back();
        // check adjacencies
        // up -> i-1 (guard against i-1 < 0)
        if (curr_i > 0) {
          const size_t up = curr_i - 1;
          if (grid.at(up).at(curr_j) == 1) {
            next_frontier.push_back(std::make_pair(up, curr_j));
            grid.at(up).at(curr_j) = 2;
            fresh_count--;
#ifdef DEBUG
            print_debug("Setting up: " + std::to_string(up) + ", " +
                        std::to_string(curr_j) + " to 2");
#endif
          }
        }

        if (curr_i < i_size - 1) {
          size_t down = curr_i + 1;
          if (grid.at(down).at(curr_j) == 1) {
            next_frontier.push_back(std::make_pair(down, curr_j));
            grid.at(down).at(curr_j) = 2;
            fresh_count--;
#ifdef DEBUG
            print_debug("Setting down: " + std::to_string(down) + ", " +
                        std::to_string(curr_j) + " to 2");
#endif
          }
        }

        if (curr_j > 0) {
          size_t left = curr_ij.second - 1;
          if (grid.at(curr_i).at(left) == 1) {
            next_frontier.push_back(std::make_pair(curr_i, left));
            grid.at(curr_i).at(left) = 2;
            fresh_count--;
#ifdef DEBUG
            print_debug("Setting left: " + std::to_string(curr_i) + ", " +
                        std::to_string(left) + " to 2");
#endif
          }
        }

        if (curr_j < j_size - 1) {
          size_t right = curr_ij.second + 1;
          if (grid.at(curr_i).at(right) == 1) {
            next_frontier.push_back(std::make_pair(curr_i, right));
            grid.at(curr_i).at(right) = 2;
            fresh_count--;
#ifdef DEBUG
            print_debug("Setting right: " + std::to_string(curr_i) + ", " +
                        std::to_string(right) + " to 2");
#endif
          }
        }
      }

      if (next_frontier.size() > 0) {
        iter_count++;
      }
    }

#ifdef DEBUG
    print_debug("After Run: ");
    print_grid(grid);
    print_debug("Fresh: " + std::to_string(fresh_count) +
                "\nIterations: " + std::to_string(iter_count) + "\n" + "\n");
#endif

    if (fresh_count != 0) {
      return -1;
    }
    return iter_count;
  }
};

TEST_CASE("Input examples") {
  Solution s;

  std::vector<std::vector<int>> a = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
  int r1 = s.orangesRotting(a);
  CHECK(r1 == 4);

  std::vector<std::vector<int>> b = {{2, 1, 1}, {0, 1, 1}, {1, 0, 1}};
  int r2 = s.orangesRotting(b);
  CHECK(r2 == -1);

  std::vector<std::vector<int>> c = {{0, 2}};
  int r3 = s.orangesRotting(c);
  CHECK(r3 == 0);

  std::vector<std::vector<int>> d = {{2, 1, 0, 1, 0, 1}, {1, 0, 1, 0, 1, 0},
                                     {0, 1, 0, 1, 0, 1}, {1, 0, 1, 0, 1, 0},
                                     {0, 1, 0, 1, 0, 1}, {1, 0, 1, 0, 1, 0}};
  int r4 = s.orangesRotting(d);
  CHECK(r4 == -1);

  std::vector<std::vector<int>> e = {{2, 1, 0, 1, 0, 1}, {1, 1, 1, 0, 1, 0},
                                     {0, 1, 0, 1, 0, 1}, {1, 0, 1, 1, 1, 0},
                                     {0, 1, 0, 1, 0, 1}, {1, 0, 1, 0, 1, 1}};
  int r5 = s.orangesRotting(e);
  CHECK(r5 == -1);
}