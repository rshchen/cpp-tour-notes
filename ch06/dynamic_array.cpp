#include <cstddef>
#include <algorithm>
#include <cassert>
#include <utility>
class DynamicArray
{
    std::size_t size_;
    int* data_;
    
public:
    DynamicArray(std::size_t size) : size_{size}, data_{new int[size]{}}
    {}
    ~DynamicArray()
    {
        delete[] data_;
    }
    // Copy constructor
    DynamicArray(const DynamicArray& other):
    size_{other.size_}, data_{new int[size_]{}}
    {
        std::copy_n(other.data_, size_, data_);
    }
    // Copy assignment
    DynamicArray& operator=(const DynamicArray& other)
    {
        if (this == &other) return *this; 
        int* new_data = new int[other.size_]{};
        std::copy_n(other.data_, other.size_, new_data);
        delete[] data_;
        size_ = other.size_;
        data_ = new_data;
        return *this;
    }
    // Move constructor
    DynamicArray(DynamicArray&& other) noexcept:
    size_{other.size_}, data_{other.data_}
    {
        other.size_ = 0;
        other.data_ = nullptr;
    }
    // Move assignment
    DynamicArray& operator=(DynamicArray&& other) noexcept
    {
        if (this == &other)
            return *this;
        delete[] data_;
        size_ = other.size_;
        data_ = other.data_;
        other.size_ = 0;
        other.data_ = nullptr;
        return *this;
    }
    std::size_t size() const noexcept 
    {
        return size_;
    }
    bool empty() const noexcept 
    {
        return size_ == 0;
    }
    int& operator[](std::size_t idx) 
    {
        return data_[idx];
    } 
    const int& operator[](std::size_t idx) const
    {
        return data_[idx];
    } 



};

int main()
{
    DynamicArray array1{3};
    assert(array1.size() == 3);
    for (int i = 0; i < 3; i++)
    {
        assert(array1[i] == 0);
    }

    array1[0] = 10;
    array1[1] = 20;
    array1[2] = 30;
    DynamicArray array2{array1};
    array2 = array1;
    array2[0] = 20;
    assert(array1[0] == 10);

    DynamicArray array3{2};
    array3 = array1;
    assert(array3.size() == 3);
    assert(array3[0] == 10 && array3[1] == 20 
        && array3[2] == 30 && &array1[0] != &array3[0]);

    DynamicArray array4{std::move(array1)};
    assert(array1.empty());
    assert(array4[0] == 10 && array4[1] == 20 
        && array4[2] == 30);

    DynamicArray array5{3};
    array5 = std::move(array2);
    assert(array5[0] == 20 && array5[1] == 20 
        && array5[2] == 30 && array2.empty());

    array5 = array5;
    assert(array5[0] == 20 && array5[1] == 20 
        && array5[2] == 30);
    array5 = std::move(array5);
    assert(array5[0] == 20 && array5[1] == 20 
        && array5[2] == 30);

}