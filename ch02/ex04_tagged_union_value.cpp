#include <cassert>
#include <iostream>

// TODO: 定義列舉類別 Tag，包含 number 與 text 兩種狀態
enum class Tag {
    // 實作列舉值
    number,
    text
};

// TODO: 定義標記聯集 Entry 結構體
// 1. 宣告聯合體以共享記憶體（包含 int 與 char 兩種成員）
// 2. 宣告 Tag 成員以記錄當前有效型別
// 3. 實作 is_number() 與 is_text() 狀態查詢函式
// 4. 實作 print() 函式，依據 Tag 印出對應成員內容
struct Entry {
    // 請在此處宣告成員變數與成員函式
    union Value
    {
        int i;
        char c;
    };
    Tag t;
    Value v;
    auto is_number() const noexcept -> bool
    {
        return (t == Tag::number);
    }
    auto is_text() const noexcept -> bool
    {
        return (t == Tag::text);
    }
    auto print() const -> void
    {
        switch (t)
        {
        case Tag::number:
            printf("%d\n", v.i);
            break;
        case Tag::text:
            printf("%c\n", v.c);
            break;
        }
    }
};

int main() {
    // 測試數值型態的標記聯集
    Entry e1;
    e1.t = Tag::number;
    e1.v.i = 1024;

    assert(e1.is_number());
    assert(!e1.is_text());
    assert(e1.v.i == 1024);

    // 測試文字型態的標記聯集
    Entry e2;
    e2.t = Tag::text;
    e2.v.c = 'K';

    assert(!e2.is_number());
    assert(e2.is_text());
    assert(e2.v.c == 'K');
    printf("All tests passed.\n");
    return 0;
}

