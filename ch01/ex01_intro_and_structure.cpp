#include <iostream>
#include <cassert>

// 函式實作：解析命令列引數個數與內容
auto parse_exit_status(int argc, const char* const argv[]) -> int {
    // TODO: 檢查 argc 邊界，當包含有效引數時回傳字元長度累計，否則回傳 0
    if (argc <=1 || argv == nullptr) return 0;
    int total_chars = 0;
    for (int i = 1; i < argc; ++i)
    {
       const char* str = argv[i];
       if (str != nullptr)
       {
        while(*str != '\0')
        {
            ++total_chars;
            ++str;
        }
       }
    }
    return total_chars;
}

int main() {
    // 模擬無自訂引數情境 (僅有程式名稱)
    const char* dummy_args_1[] = {"./main"};
    assert(parse_exit_status(1, dummy_args_1) == 0);

    // 模擬傳入單一引數 "test" (4 bytes)
    const char* dummy_args_2[] = {"./main", "test"};
    assert(parse_exit_status(2, dummy_args_2) == 4);

    std::cout << "All tests passed for ex01_intro_and_structure.\n";
    return 0;
}

