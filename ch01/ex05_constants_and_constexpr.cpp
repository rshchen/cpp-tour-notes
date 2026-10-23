#include <iostream>
#include <cassert>

// 函式宣告與定義：計算縮放後的記憶體容量
constexpr auto compute_scaled_capacity(int base_capacity, int multiplier) -> int {
    // TODO: 實作可於編譯期求值的容量運算
    return base_capacity * multiplier;
}

int main() {
    // 編譯期常數求值
    constexpr int compile_base{16};
    constexpr int compile_mult{4};
    constexpr int buffer_size = compute_scaled_capacity(compile_base, compile_mult);

    // 靜態斷言檢驗編譯期結果
    static_assert(buffer_size == 64, "Compile-time capacity calculation mismatch");

    // 執行期退化驗證
    int runtime_base{8};
    int runtime_mult{3};
    int dynamic_size = compute_scaled_capacity(runtime_base, runtime_mult);
    assert(dynamic_size == 24);

    std::cout << "All tests passed for ex05_constants_and_constexpr.\n";
    return 0;
}

