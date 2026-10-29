#include <cstddef>
#include <cassert>
#include <iostream>

// TODO: 自行定義 class Vector 的完整宣告與實作
// 包含：
// 1. private 成員變數宣告（記錄大小、管理動態陣列原生指標）
// 2. public 建構函式（防止隱式轉換、落實值初始化）
// 3. public 解構函式（落實 RAII 正確釋放資源）
// 4. public size() 查詢函式
// 5. public operator[] 下標運算子的常數與非常數重載版本
class Vector
{
    public:
        explicit Vector(std::size_t s)
            : sz_{s}, elem_{(s > 0)? new int[s]() : nullptr}{}
        
        ~Vector()
        {
            delete[] elem_;
        }

        auto size() const noexcept -> std::size_t
        {
            return sz_;
        }
        auto operator[](std::size_t i) const -> int
        {
            return elem_[i];
        }
        auto operator[](std::size_t i) -> int&
        {
            return elem_[i];
        }
    private:
        std::size_t sz_{0};
        int* elem_{nullptr};
};

int main() {
    Vector v(5);
    assert(v.size() == 5);

    // 驗證預設值已清零，並透過非常數 operator[] 寫入數值
    for (std::size_t i = 0; i < v.size(); ++i) {
        assert(v[i] == 0);
        v[i] = static_cast<int>(i * 10);
    }

    // 透過常數參考驗證常數版本的 operator[]
    const Vector& v_ref = v;
    assert(v_ref.size() == 5);
    assert(v_ref[0] == 0);
    assert(v_ref[2] == 20);
    assert(v_ref[4] == 40);
    std::cout << "All tests passed.\n";

    return 0;
}

