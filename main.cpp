#include <iostream>
#include "tests.hpp"

using std::cout, std::endl;

int main() {
    unsigned pass_cnt = 0, fail_cnt = 0, skip_cnt = 0;
    
    TEST(constructor);
    TEST(size);
    TEST(at);
    TEST(insert);
    TEST(erase);
    TEST(rule_of_three);
    TEST(insert_and_erase);
    TEST(templated);

    cout << "passing " << pass_cnt << "/" << (pass_cnt + fail_cnt) << " tests" << endl;
    if (skip_cnt > 0) {
        cout << "skipped " << skip_cnt << " tests" << endl;
    } else if (fail_cnt == 0) {
        cout << "ALL TESTS PASSING" << endl;
    }

    return 0;
} 