#include <stdexcept>
#include <cassert>
#include <string>
#include <iostream>

auto divide_or_throw(double a, double b) -> double
{
    if (b == 0.0) throw std::invalid_argument{"division by zero"};
    return a / b;
}

auto try_divide(double a, double b, double& result) -> bool
{
    if (b == 0.0) return false;
    result = a / b;
    return true;
}

int main()
{
    assert(divide_or_throw(10, 2) == 5.0);
    assert(divide_or_throw(7, 2) == 3.5);
    assert(divide_or_throw(-9, 3) == -3.0);
    assert(divide_or_throw(0, 5) == 0.0);
    bool caught = false;
    try
    {
        divide_or_throw(10, 0);
    }
    catch (const std::invalid_argument& e)
    {
        caught = true;
        assert(std::string{e.what()} == "division by zero");
    }
    assert(caught == true);

    double result = 0.0;
    assert(try_divide(10, 2, result) && result == 5.0);
    assert(try_divide(7, 2, result) && result == 3.5);
    assert(try_divide(-9, 3, result) && result == -3);
    assert(try_divide(0, 5, result) && result == 0.0);
    result = 3.14;
    assert(try_divide(10, 0, result)==false && result == 3.14);
   
    std::cout<<"All tests passed.\n";
    return 0;
    
}