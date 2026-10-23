#include <iostream>
#include <cassert>

// 函式實作：帶初始化判斷之元素篩選與縮放累加
auto filter_threshold_sum(const int* src, int length, int threshold, int factor, int& output_sum) -> int {
    // TODO: 使用 if (init; condition) 篩選元素，完成條件累加並回傳計數
    if (src == nullptr || length <=  0) return 0;
    int count=0;
    for (int i = 0; i < length; ++i){
        if (int val = src[i]; val > threshold)
        {
            output_sum += val * factor;
            ++count;
        }
    }
    return count;
}

int main() {
    int dataset[]{15, 4, 30, 8, 25};
    int total_sum{0};

    // 門檻為 10，符合者為 15, 30, 25 (共 3 筆)
    // 乘上 factor 2 -> (15 + 30 + 25) * 2 = 140
    int matched_count = filter_threshold_sum(dataset, 5, 10, 2, total_sum);

    assert(matched_count == 3);
    assert(total_sum == 140);

    // 邊界異常檢查
    assert(filter_threshold_sum(nullptr, 5, 10, 2, total_sum) == 0);

    std::cout << "All tests passed for ex07_control_flow_and_assertions.\n";
    return 0;
}

