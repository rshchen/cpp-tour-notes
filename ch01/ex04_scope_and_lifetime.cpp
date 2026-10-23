#include <iostream>
#include <cassert>

namespace
{
    int cur_id = 0;
}

// 函式實作：遞增並回傳唯一序號
auto generate_sequence_id() -> int {
    // TODO: 回傳並累加受限於模組範疇的內部靜態儲存變數
    return ++cur_id;
}

// 函式實作：重設內部序號起始值
auto reset_sequence(int start_val) -> void {
    // TODO: 重設內部計數器狀態
    cur_id = start_val;
}

int main() {
    reset_sequence(100);

    assert(generate_sequence_id() == 101);
    assert(generate_sequence_id() == 102);
    assert(generate_sequence_id() == 103);

    reset_sequence(0);
    assert(generate_sequence_id() == 1);

    std::cout << "All tests passed for ex04_scope_and_lifetime.\n";
    return 0;
}

