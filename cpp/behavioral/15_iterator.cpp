/**
 * 设计模式: 迭代器模式 (Iterator)
 * 分类: 行为型
 *
 * 意图: 提供顺序访问聚合对象元素的方法，而不暴露其内部表示。
 * 核心思想: 迭代器封装遍历逻辑，聚合对象负责创建迭代器。
 * 编程范式: OOP — 迭代器协议；C++ 自定义迭代器与 STL 兼容。
 */

#include <iostream>
#include <vector>
#include <stdexcept>

// ── 聚合：数字范围（懒计算）──────────────────────────────────────────────
class NumberRange {
    int start_, end_, step_;
public:
    NumberRange(int start, int end, int step = 1)
        : start_(start), end_(end), step_(step) {}

    // ── 内嵌迭代器（符合 STL 输入迭代器概念）────────────────────────────
    struct Iterator {
        using value_type        = int;
        using difference_type   = int;
        using iterator_category = std::input_iterator_tag;
        using pointer           = const int*;
        using reference         = const int&;

        int current, step;
        int  operator*()  const { return current; }
        Iterator& operator++()  { current += step; return *this; }
        bool operator!=(const Iterator& o) const { return current < o.current; }
    };

    Iterator begin() const { return {start_, step_}; }
    Iterator end()   const { return {end_,   step_}; }
};

int main() {
    NumberRange r(0, 20, 3);

    // 范围 for（依赖 begin/end）
    for (int v : r) std::cout << v << " ";
    std::cout << "\n";

    // STL 算法兼容
    long sum = 0;
    for (int v : r) sum += v;
    std::cout << "sum = " << sum << "\n";
    return 0;
}
