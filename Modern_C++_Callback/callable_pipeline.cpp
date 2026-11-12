#include <vector>
#include <functional>
#include <cassert>
// Generic Pipeline
template<typename F>
std::vector<int> transform_values(const std::vector<int>& seq, F op)
{
    std::vector<int> result;
    result.reserve(seq.size());
    for (int x : seq)
    {
        result.push_back(std::invoke(op, x));
    }
    return result;
}

//Type-erased Pipeline
std::vector<int> transform_dynamic(
    const std::vector<int>& seq,
    const std::function<int(int)>& op )
{
    std::vector<int> result;
    result.reserve(seq.size());
    for (int x : seq)
    {
        result.push_back(std::invoke(op, x));
    }
    return result;
}

using Operation = int (*)(int);

int square(int val)
{
    return val * val;
}

class Multiplier
{
    int factor_;
public:
    Multiplier(int factor): factor_{factor}{}
    int operator()(int val) const
    {
        return factor_ * val;
    }
};

int main()
{
    Operation op = square;
    std::vector<int> test_input1{1,2,3};
    assert(transform_values(test_input1, op) 
        == std::vector<int>({1,4,9}));
    assert(transform_dynamic(test_input1, op)
        == std::vector<int>({1,4,9}));
    
    assert(transform_values(test_input1, Multiplier{3})
        == std::vector<int>({3,6,9}));
    assert(transform_dynamic(test_input1, Multiplier{3})
        == std::vector<int>({3,6,9}));
    
    int offset = 5;
    auto add = [offset](int val)
        {
            return val + offset;
        };
    assert(transform_values(test_input1, add)
        == std::vector<int>({6,7,8}));
    assert(transform_dynamic(test_input1, add)
        == std::vector<int>({6,7,8}));

    int factor = 2;
    std::vector<int> test_input2{2, 4};
    std::function<int(int)> multiply = [factor](int val)
        {
            return factor * val;
        };
    assert(transform_values(test_input2, multiply)
        == std::vector<int>({4, 8}));
    assert(transform_dynamic(test_input2, multiply)
        == std::vector<int>({4, 8}));
    
    std::vector<int> empty{};
    assert(transform_values(empty, multiply).empty());
    assert(transform_dynamic(empty, multiply).empty());
    return 0;
}