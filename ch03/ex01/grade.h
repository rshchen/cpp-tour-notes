#ifndef GRADE_H
#define GRADE_H

#include <vector>
namespace Grade
{
    auto average(const std::vector<int>& scores) -> double;
    auto count_passed(
        const std::vector<int>& scores,
        int passing_score) -> int;
    
}
#endif