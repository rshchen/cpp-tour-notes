#include <iostream>
#include <cassert>

// 函式宣告與定義
auto update_and_scale(int input_val, const int& factor, int& output_val) -> void {
    // TODO: 將整數 input_val 乘上 factor 後寫入 output_val
    output_val = input_val * factor;
}

auto update_and_scale(double input_val, const double& factor, double& output_val) -> void {
    // TODO: 將浮點數 input_val 乘上 factor 後寫入 output_val
    output_val = input_val * factor;
}

int main() {
    int int_out{0};
    int int_factor{3};
    update_and_scale(10, int_factor, int_out);
    assert(int_out == 30);

    double double_out{0.0};
    double double_factor{2.5};
    update_and_scale(4.0, double_factor, double_out);
    assert(double_out == 10.0);

    std::cout << "All tests passed for ex02_functions_and_interfaces.\n";
    return 0;
}

