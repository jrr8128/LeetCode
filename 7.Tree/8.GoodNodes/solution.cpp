#define CATCH_CONFIG_MAIN
#include <iostream>

#include "catch_amalgamated.hpp"

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

void deallocate(TreeNode* node) {
  if (node == nullptr) {
    return;
  }
  if (node->left != nullptr) {
    deallocate(node->left);
  }
  if (node->right != nullptr) {
    deallocate(node->right);
  }
  delete node;
}

class Solution {
 public:
  int goodNodes(TreeNode* root) {
    if (root == nullptr) {
      return 0;
    }
    std::vector<std::pair<TreeNode*, int>> dfs;
    std::pair<TreeNode*, int> pair = {root, root->val};
    TreeNode* child;
    TreeNode* current_node;
    dfs.push_back(pair);
    int current_max;
    int good_count = 0;

    while (!dfs.empty()) {
      pair = dfs.back();
      current_node = pair.first;
      current_max = pair.second;
      dfs.pop_back();
      if (current_node->val >= current_max) {
        good_count++;
      }

      int val;
      if ((child = current_node->right) != nullptr) {
        val = child->val;
        if (val > current_max) {
          pair = {child, val};

        } else {
          pair = {child, current_max};
        }
        dfs.push_back(pair);
      }
      if ((child = current_node->left) != nullptr) {
        val = child->val;
        if (val > current_max) {
          pair = {child, val};
        } else {
          pair = {child, current_max};
        }
        dfs.push_back(pair);
      }
    }

    return good_count;
  }
};

TEST_CASE("Examples") {
  Solution s;

  // Test Case 1
  TreeNode* root_a = new TreeNode(3);
  TreeNode* root_left = new TreeNode(3);
  TreeNode* root_left_left = new TreeNode(4);
  TreeNode* root_left_right = new TreeNode(2);

  root_a->left = root_left;
  root_left->left = root_left_left;
  root_left->right = root_left_right;

  int r1 = s.goodNodes(root_a);
  CHECK(r1 == 3);
  deallocate(root_a);

  // Test Case 2
  TreeNode* root_b = new TreeNode(1);

  int r2 = s.goodNodes(root_b);
  CHECK(r2 == 1);
  deallocate(root_b);

  // Test Case 3
  // Input: root = [3,1,4,3,null,1,5]
  TreeNode* root_c = new TreeNode(3);
  TreeNode* root_l = new TreeNode(1);
  TreeNode* root_r = new TreeNode(4);
  TreeNode* root_l_l = new TreeNode(3);
  TreeNode* root_r_l = new TreeNode(1);
  TreeNode* root_r_r = new TreeNode(5);
  root_c->left = root_l;
  root_c->right = root_r;
  root_l->left = root_l_l;
  root_r->left = root_r_l;
  root_r->right = root_r_r;

  int r3 = s.goodNodes(root_c);
  CHECK(r3 == 4);
  deallocate(root_c);
}