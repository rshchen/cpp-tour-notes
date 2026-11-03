#include <stdexcept>
#include <cassert>
#include <string>
#include <iostream>
class Range
{

    int low_;
    int high_;
public:
    Range(int low, int high):low_{low}, high_{high}
    {
        if (low > high) throw std::invalid_argument{"invalid range"};
    }

    auto low() const -> int
    {
        return low_;
    }

    auto high() const -> int
    {
        return high_;
    }

    auto contains(int val) const -> bool
    {
        return (val >= low_ && val <= high_);
    }

    void set_range(int low, int high)
    {
        if (low > high) throw std::invalid_argument{"invalid range"};
        low_ = low;
        high_ = high;
    }
};


int main()
{
    Range range1{2,8};
    assert(range1.low() == 2 && range1.high() == 8);
    assert(range1.contains(2) && range1.contains(8) && !range1.contains(9));
    
    Range range2{5,5};
    assert(range2.contains(5));

    bool caught = false;
    try
    {
        Range{8,2};
    }
    catch(const std::invalid_argument& e)
    {
        caught = true;
        assert(std::string{e.what()} == "invalid range");
    }
    assert(caught);

    caught = false;
    try
    {
        range1.set_range(10,3);
    }
    catch(const std::invalid_argument& e)
    {
        caught = true;
        std::cerr << e.what() << '\n';
    }
    assert(caught);
    assert(range1.low() == 2 && range1.high() == 8);

    range1.set_range(3,6);
    assert(range1.low() == 3 && range1.high() == 6);

    std::cout<< "All tests passed.\n";
    


    return 0;
}