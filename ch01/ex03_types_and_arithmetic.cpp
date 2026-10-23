#include <iostream>
#include <cassert>

// 函式實作：精確計算比率並顯式截斷轉型
auto calculate_ratio_and_cast(int numerator, int denominator, int& truncated_out) -> double {
    // TODO: 處理分母為 0 之邊界，以浮點運算求值，並以 static_cast 轉換寫入 truncated_out
    if (denominator == 0)
    {
        truncated_out = 0;
        return 0.0;
    }
    double ratio = static_cast<double> (numerator) / denominator;
    truncated_out = static_cast<int> (ratio);
    return ratio;
}

int main() {
    int truncated_val{0};
    
    // 7 / 2 = 3.5, 截斷整數為 3
    double precise_ratio = calculate_ratio_and_cast(7, 2, truncated_val);
    assert(precise_ratio == 3.5);
    assert(truncated_val == 3);

    // 除以零邊界保護
    double zero_ratio = calculate_ratio_and_cast(5, 0, truncated_val);
    assert(zero_ratio == 0.0);
    assert(truncated_val == 0);

    std::cout << "All tests passed for ex03_types_and_arithmetic.\n";
    return 0;
}

