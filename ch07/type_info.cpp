#include <string_view>
template<typename T>
struct TypeInfo
{

    static constexpr bool is_pointer = false;
    static constexpr std::string_view name()
    {
        return "value";
    }
};

template<typename T>
struct TypeInfo<T*>
{

    static constexpr bool is_pointer = true;
    static constexpr std::string_view name()
    {
        return "pointer";
    }
    

};

int main()
{
    static_assert(!TypeInfo<int>::is_pointer 
        && TypeInfo<int>::name() == "value");
    static_assert(!TypeInfo<double>::is_pointer 
        && TypeInfo<double>::name() == "value");
    static_assert(TypeInfo<int*>::is_pointer 
        && TypeInfo<int*>::name() == "pointer");
    static_assert(TypeInfo<const int*>::is_pointer 
        && TypeInfo<const int*>::name() == "pointer");
    static_assert(TypeInfo<int**>::is_pointer 
        && TypeInfo<int**>::name() == "pointer");
    return 0;
}