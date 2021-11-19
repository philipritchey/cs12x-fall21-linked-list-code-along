#include <iostream>
#include "linked_list.hpp"
#include "tests.hpp"
#include "cs12x_test.hpp"

using std::cout, std::endl;

bool test_constructor() {
  INIT_TEST;

  {
    linked_list<int> list;
    const linked_list<int>::node* head = list.get_head()
    EXPECT_EQ(head, nullptr);
  }

  RESULT(pass);
  return pass;
}