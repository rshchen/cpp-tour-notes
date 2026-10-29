#include <cstdint>
#include <type_traits>
#include <cassert>
#include <iostream>

// TODO: 定義 enum class TaskState 底層型別為 std::uint8_t
// 包含狀態：
// Pending = 0
// Running = 1
// Completed = 2
// Failed = 3
enum class TaskState : std::uint8_t
{
    Pending = 0,
    Running = 1,
    Completed = 2,
    Failed = 3
};

constexpr auto to_raw_value(TaskState state) noexcept -> std::uint8_t {
    // TODO: 安全轉換回底層整數型別
    return static_cast<int> (state);
}

constexpr auto is_finished(TaskState state) noexcept -> bool {
    // TODO: 當狀態為 Completed 或 Failed 時判定為完成，回傳 true
    return (state == TaskState::Completed || state == TaskState::Failed);
}

int main() {
    static_assert(sizeof(TaskState) == sizeof(std::uint8_t));

    constexpr auto state_completed = TaskState::Completed;
    static_assert(to_raw_value(state_completed) == 2);
    static_assert(is_finished(state_completed));
    static_assert(!is_finished(TaskState::Running));
    std::cout << "All tests passed.\n";
    return 0;
}

