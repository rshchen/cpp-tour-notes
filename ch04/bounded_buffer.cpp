#include <stdexcept>
#include <vector>
#include <cassert>
#include <iostream>
class BoundedBuffer
{
    std::vector<int> data_;
    int capacity_;
public:
    BoundedBuffer(int capacity): capacity_{capacity}
    {
        if (capacity <= 0)
            throw std::invalid_argument{"invalid capacity"};
        data_.reserve(capacity);
    }

    auto size() const noexcept -> int
    {
        return data_.size();
    }

    auto capacity() const noexcept -> int
    {
        return capacity_;
    }

    auto empty() const noexcept -> bool
    {
        return (data_.size() == 0);
    }

    auto full() const noexcept -> bool
    {
        return (data_.size() == capacity_);
    }

    void push(int val)
    {
        if (full())
            throw std::overflow_error{"buffer full"};
        data_.push_back(val);
    }

    auto at(int idx) const -> int
    {
        if (idx < 0 || idx >= size())
            throw std::out_of_range{"index out of range"};
        return data_[idx];
    }

};

int main()
{
    BoundedBuffer buffer1{3};
    assert(buffer1.size() == 0 && buffer1.empty());

    buffer1.push(10);
    buffer1.push(20);
    buffer1.push(30);
    assert(buffer1.size() == 3 && buffer1.full());
    assert(buffer1.at(0) == 10 && buffer1.at(2) == 30);
    
    bool caught = false;
    try
    {
        buffer1.push(40);
    }
    catch(const std::overflow_error& e)
    {
        caught = true;
        std::cerr << e.what() << '\n';
    }
    assert(caught);

    caught = false;
    try
    {
        buffer1.at(-1);
    }
    catch(const std::out_of_range& e)
    {
        caught = true;
        std::cerr << e.what() << '\n';
    }
    assert(caught);

    caught = false;
    try
    {
        buffer1.at(3);
    }
    catch(const std::out_of_range& e)
    {
        caught = true;
        std::cerr << e.what() << '\n';
    }
    assert(caught);

    caught = false;
    try
    {
        BoundedBuffer{-1};
    }
    catch(const std::invalid_argument& e)
    {
        caught = true;
        std::cerr << e.what() << '\n';
    }
    assert(caught);
    std::cout<<"All tests passed.\n";
    return 0;
}