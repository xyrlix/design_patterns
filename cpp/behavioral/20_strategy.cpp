/**
 * 设计模式: 策略模式 (Strategy)
 * 分类: 行为型
 *
 * 意图: 定义一系列算法，将每个算法封装起来，使它们可以互换。
 * 核心思想: 策略接口 + 具体策略类，Context 在运行时切换算法。
 * 编程范式: OOP — 依赖注入 + 开闭原则（扩展新策略无需修改 Context）。
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

// ── 策略接口 ──────────────────────────────────────────────────────────────
struct SortStrategy {
    virtual void sort(std::vector<int>& data) const = 0;
    virtual std::string name() const = 0;
    virtual ~SortStrategy() = default;
};

// ── 具体策略 ──────────────────────────────────────────────────────────────
struct BubbleSort : SortStrategy {
    void sort(std::vector<int>& v) const override {
        for (size_t i = 0; i < v.size(); ++i)
            for (size_t j = 0; j + 1 < v.size() - i; ++j)
                if (v[j] > v[j+1]) std::swap(v[j], v[j+1]);
    }
    std::string name() const override { return "BubbleSort"; }
};

struct StdSort : SortStrategy {
    void sort(std::vector<int>& v) const override { std::sort(v.begin(), v.end()); }
    std::string name() const override { return "StdSort"; }
};

// ── Context ───────────────────────────────────────────────────────────────
class Sorter {
    std::unique_ptr<SortStrategy> strategy_;
public:
    explicit Sorter(std::unique_ptr<SortStrategy> s) : strategy_(std::move(s)) {}

    void setStrategy(std::unique_ptr<SortStrategy> s) { strategy_ = std::move(s); }

    void execute(std::vector<int> data) const {
        strategy_->sort(data);
        std::cout << strategy_->name() << ": ";
        for (int v : data) std::cout << v << " ";
        std::cout << "\n";
    }
};

int main() {
    std::vector<int> data = {5, 3, 1, 4, 2};

    Sorter sorter(std::make_unique<BubbleSort>());
    sorter.execute(data);

    sorter.setStrategy(std::make_unique<StdSort>());
    sorter.execute(data);
    return 0;
}
