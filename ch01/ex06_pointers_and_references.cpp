#include <iostream>
#include <cassert>

// 函式實作：雙指標就地翻轉陣列
auto reverse_in_place(int* begin, int* end) -> bool {
    // TODO: 驗證指標有效性，透過首尾指標移動進行原地交換
    if (begin == nullptr || end == nullptr || begin >= end)
    {
        return false;
    }
    int* left = begin;
    int* right = end - 1;
    while(left < right)
    {
        int temp = *left;
        *left = *right;
        *right = temp;

        ++left;
        --right;
    }
    return true;
}

int main() {
    int buffer[]{10, 20, 30, 40, 50};
    int* begin_ptr = buffer;
    int* end_ptr = buffer + 5; // 開區間右端點

    bool success = reverse_in_place(begin_ptr, end_ptr);
    assert(success == true);

    // 驗證元素倒序排列
    assert(buffer[0] == 50);
    assert(buffer[1] == 40);
    assert(buffer[2] == 30);
    assert(buffer[3] == 20);
    assert(buffer[4] == 10);

    // 異常指標輸入防禦
    assert(reverse_in_place(nullptr, end_ptr) == false);
    assert(reverse_in_place(end_ptr, begin_ptr) == false);

    std::cout << "All tests passed for ex06_pointers_and_references.\n";
    return 0;
}

