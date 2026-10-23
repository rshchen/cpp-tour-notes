#include <iostream>
#include <cassert>

// 函式實作：編譯期環境檢驗與安全區間拷貝
auto verify_platform_and_copy(const int* src_begin, const int* src_end, int* dst_begin) -> bool {
    // 靜態斷言檢驗 64 位元定址架構
    static_assert(sizeof(void*) == 8, "Platform must be 64-bit architecture");

    // TODO: 驗證指標有效性，逐一將元素拷貝至目標緩衝區
    if (src_begin == nullptr || src_end == nullptr || dst_begin == nullptr || src_begin>=src_end) return false;
    const int* read_ptr = src_begin;
    int* write_ptr = dst_begin;
    while(read_ptr < src_end)
    {
        *write_ptr = *read_ptr;
        ++read_ptr;
        ++write_ptr;
    }
    return true;
}

int main() {
    int src_data[]{1, 3, 5, 7};
    int dst_data[4]{0};

    bool status = verify_platform_and_copy(src_data, src_data + 4, dst_data);
    assert(status == true);

    // 驗證內容完整複製
    for (int i{0}; i < 4; ++i) {
        assert(dst_data[i] == src_data[i]);
    }

    // 邊界防禦
    assert(verify_platform_and_copy(nullptr, src_data + 4, dst_data) == false);

    std::cout << "All tests passed for ex08_guidelines_and_type_safety.\n";
    return 0;
}

