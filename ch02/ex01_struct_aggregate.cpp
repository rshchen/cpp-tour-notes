#include <cassert>
#include <iostream>

struct Point2D {
    int x;
    int y;
};

// TODO: 實作使用三元運算子的 constexpr 絕對值差輔助函式
constexpr auto abs_diff(int a, int b) noexcept -> int {
    return ((a >=b ) ? (a-b) : (b-a));
}

constexpr auto calculate_manhattan_distance(Point2D a, Point2D b) noexcept -> int {
    // TODO: 使用 abs_diff 計算並回傳兩點間之曼哈頓距離 |a.x - b.x| + |a.y - b.y|
    return (abs_diff(a.x, b.x) + abs_diff(a.y, b.y));
}

int main() {
    // C++20 指定初始化器
    constexpr Point2D p1{.x = 10, .y = 20};
    constexpr Point2D p2{.x = 4, .y = 12};

    // 編譯期斷言驗證
    static_assert(calculate_manhattan_distance(p1, p2) == 14);
    std::cout << "All tests passed.\n";
    return 0;
}

