#include "grade.h"
#include <assert.h>
#include <iostream>
using Grade::average;
using Grade::count_passed;
int main()
{
    std::vector<int> scores1{80, 90, 70};
    std::vector<int> scores2{50, 60, 70};
    std::vector<int> scores3{100, 95};
    std::vector<int> scores4{};
    assert(average(scores1)==80.0);
    assert(count_passed(scores1, 60)==3);

    assert(average(scores2)==60.0);
    assert(count_passed(scores2, 60)==2);

    assert(average(scores3)==97.5);
    assert(count_passed(scores3, 100)==1);

    assert(average(scores4)==0.0);
    assert(count_passed(scores4, 60)==0);

    std::cout<<"All tests passed.\n";

    return 0;
}