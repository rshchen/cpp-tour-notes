#include "grade.h"

namespace Grade
{

    auto average(const std::vector<int>& scores) -> double
    {
        if (scores.empty()) return 0.0;
        int sum{0};
        for (int score : scores)
        {
            sum += score;
        }
        double result = (double) sum/scores.size();
        return result;

    }
    auto count_passed(
        const std::vector<int>& scores,
        int passing_score) -> int
    {
        if (scores.empty()) return 0;
        int pass{0};
        for (int score: scores)
        {
            pass += (score >= passing_score);
        }
        return pass;
    }

}



