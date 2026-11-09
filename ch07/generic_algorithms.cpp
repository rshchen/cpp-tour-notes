#include <cstddef>
#include <optional>
#include <array>
#include <cassert>
#include <vector>
template<typename Container, typename Predicate>
std::size_t count_if_custom(const Container& c, Predicate pre)
{
    std::size_t count = 0;
    for (const auto& x : c)
    {
        if (pre(x)) ++count;
    }
    return count;
}
template<typename Container, typename Predicate>
std::optional<typename Container::value_type>
find_first_if(const Container& c, Predicate pre)
{
    for (const auto& x: c)
    {
        if (pre(x)) return x;
    }
    return std::nullopt;
}

class GreaterThan
{
    int threshold_;
public:
    GreaterThan(int threshold) : threshold_{threshold}{}
    bool operator()(int val) const
    {
        return (val > threshold_);
    }
};

int main()
{

    std::array<int, 5> array1{1,5,8,12,3};
    assert(count_if_custom(array1, GreaterThan{5}) == 2);
    assert(find_first_if(array1, GreaterThan{5}) == 8);
    
    auto if_even = [](int x)
    {
        return x % 2 == 0;
    };
    std::array<int, 5> array2{2,4,6,7,9};
    assert(count_if_custom(array2, if_even) == 3);
    assert(find_first_if(array2, if_even) == 2);

    std::array<int, 3> array3{1,3,5};
    assert(count_if_custom(array3, GreaterThan{10}) == 0);
    assert(find_first_if(array3, GreaterThan{10}) == std::nullopt);

    std::vector<int> empty;
    assert(count_if_custom(empty, GreaterThan{10}) == 0);
    assert(find_first_if(empty, GreaterThan{10}) == std::nullopt);

    return 0;
}