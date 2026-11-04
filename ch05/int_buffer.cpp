#include <stdexcept>
#include <cassert>
#include <iostream>
class IntBuffer
{
    int* data_;
    int size_;
public:
    explicit IntBuffer(int size) : data_{nullptr}, size_{size} 
    {
        if (size <= 0 ) throw std::invalid_argument{"Invalid size."};
        data_= new int[size]{};
    }
    IntBuffer(const IntBuffer& other) = delete;
    IntBuffer& operator=(const IntBuffer& other) = delete;
    
    ~IntBuffer()
    {
        delete[] data_;
    }

    auto size() const -> int
    {
        return size_;
    }

    auto operator[](int idx) -> int&
    {
        if (idx >= size_ || idx < 0) throw std::out_of_range{"Invalid index."};
        return data_[idx];
    }

    auto operator[](int idx) const -> const int&
    {
        if (idx >= size_ || idx < 0) throw std::out_of_range{"Invalid index."};
        return data_[idx];
    }

};

int main()
{
    IntBuffer buffer1{3};
    for (int i = 0; i < 3; ++i)
    {
        assert(buffer1[i] == 0);
    }
    buffer1[1] = 42;
    assert(buffer1[1] == 42);
    try
    {
        buffer1[3];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        buffer1[-1];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        IntBuffer{0};
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}