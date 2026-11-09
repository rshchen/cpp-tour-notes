#include <cstddef>
#include <cassert>
#include <exception>
#include <iostream>
#include <array>
template<typename T, std::size_t N>
class StaticBuffer
{
    std::array<T, N> data_{};
public:

    std::size_t size() const
    {
        return N;
    }

    T& at(std::size_t idx)
    {
        return data_.at(idx);
    }

    const T& at(std::size_t idx) const
    {
        return data_.at(idx);
    }
    
    void fill(const T& val)
    {
        for (T& x : data_)
        {
            x = val;
        }
    }

};
template<std::size_t N>
using IntBuffer = StaticBuffer<int, N>;

int main()
{
    StaticBuffer<int, 3> buffer1;
    assert(buffer1.size() == 3);
    for (int i = 0; i < 3; ++i)
    {
        assert(buffer1.at(i) == 0);
    }
    buffer1.fill(5);
    buffer1.at(1) = 9;
    assert(buffer1.at(0) == 5 && buffer1.at(1) == 9
     && buffer1.at(2) == 5);

    StaticBuffer<double, 2> buffer2;
    buffer2.fill(1.5);
    assert(buffer2.at(0) == 1.5 && buffer2.at(1) == 1.5);

    try
    {
        buffer2.at(2);
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }

    IntBuffer<0> buffer3;
    assert(buffer3.size() == 0);
    try
    {
        buffer3.at(0);
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
}