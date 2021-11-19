#include <iostream>
#include "linked_list.hpp"
#include "tests.hpp"

using std::cout, std::endl;

bool test_constructor() {
  INIT_TEST;

  {
    linked_list<int> list;
    const linked_list<int>::node* head = list.get_head();
    EXPECT_NULL(head);
    EXPECT_EQ(list.size(), 0);
  }

  RESULT(pass);
  return pass;
}

bool test_size() {
    INIT_TEST;

  {
    linked_list<int> list;
    EXPECT_EQ(list.size(), 0);
    
    EXPECT_NO_THROW(list.insert(0, 1));
    EXPECT_EQ(list.size(), 1);
    
    EXPECT_NO_THROW(list.erase(0));
    EXPECT_EQ(list.size(), 0);
  }

  RESULT(pass);
  return pass;
}

bool test_at() {
    INIT_TEST;

  {
    linked_list<int> list;
    EXPECT_THROW(list.at(0), std::out_of_range);
    
    EXPECT_NO_THROW(list.insert(0, 1));
    EXPECT_EQ(list.at(0), 1);
    
    EXPECT_THROW(list.at(1), std::out_of_range);
  }

  RESULT(pass);
  return pass;
}

bool test_insert() {
  INIT_TEST;

  {
    linked_list<int> list;
    EXPECT_EQ(list.size(), 0);
    
    EXPECT_NO_THROW(list.insert(0, 1));
    EXPECT_EQ(list.at(0), 1);
    EXPECT_EQ(list.size(), 1);
    
    EXPECT_NO_THROW(list.insert(0, 2));
    EXPECT_EQ(list.at(0), 2);
    EXPECT_EQ(list.at(1), 1);
    EXPECT_EQ(list.size(), 2);
    
    EXPECT_NO_THROW(list.insert(2, 3));
    EXPECT_EQ(list.at(0), 2);
    EXPECT_EQ(list.at(1), 1);
    EXPECT_EQ(list.at(2), 3);
    EXPECT_EQ(list.size(), 3);
    
    EXPECT_NO_THROW(list.insert(1, 4));
    EXPECT_EQ(list.at(0), 2);
    EXPECT_EQ(list.at(1), 4);
    EXPECT_EQ(list.at(2), 1);
    EXPECT_EQ(list.at(3), 3);
    EXPECT_EQ(list.size(), 4);
    
    const linked_list<int>::node* curr = list.get_head();
    ASSERT_NOT_NULL(curr);
    EXPECT_EQ(curr->value, 2);
    curr = curr->next;
    ASSERT_NOT_NULL(curr);
    EXPECT_EQ(curr->value, 4);
    curr = curr->next;
    ASSERT_NOT_NULL(curr);
    EXPECT_EQ(curr->value, 1);
    curr = curr->next;
    ASSERT_NOT_NULL(curr);
    EXPECT_EQ(curr->value, 3);
    curr = curr->next;
    EXPECT_NULL(curr);
  }
  
  {
    linked_list<int> list;
    
    for (int n = 1; n <= 10; n++) {
        EXPECT_NO_THROW(list.insert(list.size(), n));
        EXPECT_EQ(list.size(), size_t(n));
    }
    
    const linked_list<int>::node* curr = list.get_head();
    for (int n = 1; n <= 10; n++) {
        ASSERT_NOT_NULL(curr);
        EXPECT_EQ(curr->value, n);
        curr = curr->next;
    }
    EXPECT_NULL(curr);
  }

  RESULT(pass);
  return pass;
}

bool test_erase() {
  INIT_TEST;

  {
    linked_list<int> list;
    
    for (int n = 1; n <= 10; n++) {
        EXPECT_NO_THROW(list.insert(list.size(), n));
    }
    
    EXPECT_EQ(list.size(), 10);
    EXPECT_NO_THROW(list.erase(0));
    EXPECT_EQ(list.at(0), 2);
    EXPECT_EQ(list.size(), 9);
    const linked_list<int>::node* curr = list.get_head();
    for (int n = 2; n <= 10; n++) {
        ASSERT_NOT_NULL(curr);
        EXPECT_EQ(curr->value, n);
        curr = curr->next;
    }
    EXPECT_NULL(curr);
    
    EXPECT_NO_THROW(list.erase(8));
    EXPECT_EQ(list.size(), 8);
    EXPECT_EQ(list.at(7), 9);
    curr = list.get_head();
    for (int n = 2; n <= 9; n++) {
        ASSERT_NOT_NULL(curr);
        EXPECT_EQ(curr->value, n);
        curr = curr->next;
    }
    EXPECT_NULL(curr);
    
    EXPECT_NO_THROW(list.erase(4));
    EXPECT_EQ(list.size(), 7);
    EXPECT_EQ(list.at(4), 7);
    curr = list.get_head();
    for (int n = 2; n <= 5; n++) {
        ASSERT_NOT_NULL(curr);
        EXPECT_EQ(curr->value, n);
        curr = curr->next;
    }
    for (int n = 7; n <= 9; n++) {
        ASSERT_NOT_NULL(curr);
        EXPECT_EQ(curr->value, n);
        curr = curr->next;
    }
    EXPECT_NULL(curr);
    
    for (int n = 1; n <= 7; n++) {
        EXPECT_NO_THROW(list.erase(0));
        EXPECT_EQ(list.size(), (size_t(7-n)));
    }
    EXPECT_NULL(list.get_head());
    
  }

  RESULT(pass);
  return pass;
}

bool test_rule_of_three() {
    INIT_TEST;

    linked_list<int> list;
    for (int n = 1; n <= 10; n++) {
        EXPECT_NO_THROW(list.insert(list.size(), n));
    }
    // [1]->[2]->[3]->[4]->[5]->[6]->[7]->[8]->[9]->[10]
    {
        linked_list copy = list;
        EXPECT_EQ(list.size(), copy.size());
        EXPECT_EQ(copy.size(), 10);
        EXPECT_NE(list.get_head(), copy.get_head());
        for (int n = 1; n <= 10; n++) {
            EXPECT_EQ(list.at(n-1), n);
            EXPECT_EQ(copy.at(n-1), n);
        }
        
        EXPECT_NO_THROW(list.insert(10, 11));
        // [1]->[2]->[3]->[4]->[5]->[6]->[7]->[8]->[9]->[10]->[11]
        EXPECT_EQ(list.size(), 11);
        EXPECT_EQ(copy.size(), 10);
        
        EXPECT_NO_THROW(copy.erase(0));
        // [2]->[3]->[4]->[5]->[6]->[7]->[8]->[9]->[10]
        EXPECT_EQ(list.size(), 11);
        EXPECT_EQ(copy.size(), 9);
        EXPECT_EQ(list.at(0), 1);
        EXPECT_EQ(copy.at(0), 2);
        
        EXPECT_NO_THROW(list = copy);
        // [2]->[3]->[4]->[5]->[6]->[7]->[8]->[9]->[10]
        EXPECT_EQ(list.size(), copy.size());
        EXPECT_EQ(copy.size(), 9);
        EXPECT_NE(list.get_head(), copy.get_head());
        for (int n = 2; n <= 10; n++) {
            EXPECT_EQ(list.at(n-2), n);
            EXPECT_EQ(copy.at(n-2), n);
        }
        
        EXPECT_NO_THROW(list.insert(9, 12));
        // [2]->[3]->[4]->[5]->[6]->[7]->[8]->[9]->[10]->[12]
        EXPECT_EQ(list.size(), 10);
        EXPECT_EQ(copy.size(), 9);
        
        EXPECT_NO_THROW(copy.erase(0));
        // [3]->[4]->[5]->[6]->[7]->[8]->[9]->[10]
        EXPECT_EQ(list.size(), 10);
        EXPECT_EQ(copy.size(), 8);
        EXPECT_EQ(list.at(0), 2);
        EXPECT_EQ(copy.at(0), 3);
    }
    EXPECT_EQ(list.size(), 10);
    for (int n = 2; n <= 10; n++) {
        EXPECT_EQ(list.at(n-2), n);
    }
    EXPECT_EQ(list.at(9), 12);
    
    EXPECT_NO_THROW(list = list);
    // [2]->[3]->[4]->[5]->[6]->[7]->[8]->[9]->[10]->[12]
    EXPECT_NO_THROW(list.insert(10, 13));
    // [2]->[3]->[4]->[5]->[6]->[7]->[8]->[9]->[10]->[12]->[13]
    EXPECT_EQ(list.size(), 11);
    EXPECT_NO_THROW(list.erase(5));
    // [2]->[3]->[4]->[5]->[6]->[8]->[9]->[10]->[12]->[13]
    EXPECT_EQ(list.size(), 10);
    EXPECT_EQ(list.at(0), 2);
    EXPECT_EQ(list.at(1), 3);
    EXPECT_EQ(list.at(2), 4);
    EXPECT_EQ(list.at(3), 5);
    EXPECT_EQ(list.at(4), 6);
    EXPECT_EQ(list.at(5), 8);
    EXPECT_EQ(list.at(6), 9);
    EXPECT_EQ(list.at(7), 10);
    EXPECT_EQ(list.at(8), 12);
    EXPECT_EQ(list.at(9), 13);
    
    RESULT(pass);
    return pass;
}

bool test_insert_and_erase() {
    INIT_TEST;
    
    linked_list<int> list;
    for (int n = 1; n <= 10; n++) {
        EXPECT_NO_THROW(list.insert(list.size(), n));
    }
    // [1]->[2]->[3]->[4]->[5]->[6]->[7]->[8]->[9]->[10]
    for (size_t i = 0; i < 5; i++) {
        EXPECT_NO_THROW(list.erase(i));
    }
    // [2]->[4]->[6]->[8]->[10]
    EXPECT_EQ(list.size(), 5);
    for (size_t i = 0; i < 5; i++) {
        int expected = 2*(i+1);
        EXPECT_EQ(list.at(i), expected);
    }
    const linked_list<int>::node* curr = list.get_head();
    for (int i = 0; i < 5; i++) {
        ASSERT_NOT_NULL(curr);
        int expected = 2*(i+1);
        EXPECT_EQ(curr->value, expected);
        curr = curr->next;
    }
    EXPECT_NULL(curr);
    
    EXPECT_NO_THROW(list.insert(0, 0));
    // [0]->[2]->[4]->[6]->[8]->[10]
    EXPECT_EQ(list.size(), 6);
    EXPECT_EQ(list.at(0), 0);
    
    EXPECT_NO_THROW(list.erase(3));
    // [0]->[2]->[4]->[8]->[10]
    EXPECT_EQ(list.size(), 5);
    EXPECT_EQ(list.at(3), 8);
    
    EXPECT_NO_THROW(list.insert(3, 6));
    // [0]->[2]->[4]->[6]->[8]->[10]
    EXPECT_EQ(list.size(), 6);
    EXPECT_EQ(list.at(3), 6);
    
    EXPECT_NO_THROW(list.insert(6, 12));
    // [0]->[2]->[4]->[6]->[8]->[10]-[12]
    EXPECT_EQ(list.size(), 7);
    EXPECT_EQ(list.at(6), 12);
    
    curr = list.get_head();
    for (int i = 0; i < 7; i++) {
        ASSERT_NOT_NULL(curr);
        int expected = 2*i;
        EXPECT_EQ(curr->value, expected);
        curr = curr->next;
    }
    EXPECT_NULL(curr);
    
    RESULT(pass);
    return pass;
}

bool test_templated() {
    INIT_TEST;
    
    linked_list<int> int_list;
    EXPECT_EQ(int_list.size(), 0);
    EXPECT_NO_THROW(int_list.insert(0, 7));
    EXPECT_EQ(int_list.size(), 1);
    EXPECT_EQ(int_list.at(0), 7);
    
    linked_list<char> char_list;
    EXPECT_EQ(char_list.size(), 0);
    EXPECT_NO_THROW(char_list.insert(0, '7'));
    EXPECT_EQ(char_list.size(), 1);
    EXPECT_EQ(char_list.at(0), '7');
    
    linked_list<double> double_list;
    EXPECT_EQ(double_list.size(), 0);
    EXPECT_NO_THROW(double_list.insert(0, 7.13));
    EXPECT_EQ(double_list.size(), 1);
    EXPECT_EQ(double_list.at(0), 7.13);
    
    linked_list<std::string> string_list;
    EXPECT_EQ(string_list.size(), 0);
    EXPECT_NO_THROW(string_list.insert(0, "7.13"));
    EXPECT_EQ(string_list.size(), 1);
    EXPECT_EQ(string_list.at(0), "7.13");
    
    linked_list<linked_list<int>> int_list_list;
    EXPECT_EQ(int_list_list.size(), 0);
    EXPECT_NO_THROW(int_list_list.insert(0, int_list));
    EXPECT_EQ(int_list_list.size(), 1);
    EXPECT_EQ(int_list_list.at(0).size(), 1);
    EXPECT_EQ(int_list_list.at(0).at(0), 7);
    
    EXPECT_NO_THROW(int_list.erase(0));
    EXPECT_EQ(int_list.size(), 0);
    EXPECT_EQ(int_list_list.at(0).size(), 1);
    EXPECT_EQ(int_list_list.at(0).at(0), 7);

    RESULT(pass);
    return pass;
}