#include <cstddef>
#include <string>
#define CATCH_CONFIG_MAIN
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "catch_amalgamated.hpp"

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
 public:
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    if (head == nullptr || head->next == nullptr) {
      return nullptr;
    }
    ListNode* leftEraseNode = head;
    ListNode* rightEraseNode = leftEraseNode;
    // give spacing equal to n; want both nodes on either side of the
    for (int i = 0; i < n; i++) {
      if (rightEraseNode->next != nullptr) {
        rightEraseNode = rightEraseNode->next;
      } else {
        return head->next;
      }
    }
    // increment both pointers along list until the end
    while (rightEraseNode->next != nullptr) {
      leftEraseNode = leftEraseNode->next;
      rightEraseNode = rightEraseNode->next;
    }

    if (n > 1) {
      leftEraseNode->next = leftEraseNode->next->next;
    } else {
      leftEraseNode->next = nullptr;
    }
    return head;
  }
};

void delete_list(ListNode* head) {
  while (head != nullptr) {
    ListNode* next = head->next;
    delete head;
    head = next;
  }
};

std::vector<int> parse_list(ListNode* head) {
  std::vector<int> result = {};
  ListNode* currNode = head;
  while (currNode != nullptr) {
    result.push_back(currNode->val);
    currNode = currNode->next;
  }
  return result;
};

TEST_CASE("Nth Node Examples") {
  Solution s;

  ListNode* head1 = new ListNode(
      1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
  std::vector<int> expected = {1, 2, 3, 5};
  std::vector<int> r1 = parse_list(s.removeNthFromEnd(head1, 2));
  CHECK(r1 == expected);
  delete_list(head1);

  ListNode* head2 = new ListNode(1);
  std::vector<int> r2 = parse_list(s.removeNthFromEnd(head2, 1));
  CHECK(r2 == std::vector<int>{});
  delete_list(head2);

  ListNode* head3 = new ListNode(1, new ListNode(2));
  expected = {1};
  std::vector<int> r3 = parse_list(s.removeNthFromEnd(head3, 1));
  CHECK(r3 == expected);
  delete_list(head3);

  ListNode* head4 = new ListNode(1, new ListNode(2));
  expected = {2};
  std::vector<int> r4 = parse_list(s.removeNthFromEnd(head4, 2));
  CHECK(r4 == expected);
  delete_list(head4);
}