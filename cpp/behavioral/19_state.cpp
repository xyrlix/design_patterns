/**
 * 设计模式: 状态模式 (State)
 * 分类: 行为型
 *
 * 意图: 允许对象在内部状态改变时改变它的行为，对象看起来似乎修改了它的类。
 * 核心思想: 将每个状态封装为独立类，Context 持有当前状态引用并委托行为。
 * 编程范式: OOP — 多态替换 if-else 状态机；状态自主转换。
 */

#include <iostream>
#include <memory>
#include <string>

struct TrafficLight;

// ── 状态接口 ──────────────────────────────────────────────────────────────
struct State {
    virtual void handle(TrafficLight& ctx) = 0;
    virtual std::string name() const = 0;
    virtual ~State() = default;
};

// ── Context ───────────────────────────────────────────────────────────────
struct TrafficLight {
    std::unique_ptr<State> state;
    explicit TrafficLight(std::unique_ptr<State> s) : state(std::move(s)) {}
    void next() {
        std::cout << "Current: " << state->name() << " → ";
        state->handle(*this);
        std::cout << state->name() << "\n";
    }
};

// ── 具体状态（前向声明处理循环依赖）────────────────────────────────────
struct GreenState;
struct YellowState;
struct RedState;

struct GreenState : State {
    void handle(TrafficLight& ctx) override;
    std::string name() const override { return "Green"; }
};
struct YellowState : State {
    void handle(TrafficLight& ctx) override;
    std::string name() const override { return "Yellow"; }
};
struct RedState : State {
    void handle(TrafficLight& ctx) override;
    std::string name() const override { return "Red"; }
};

void GreenState::handle(TrafficLight& ctx)  { ctx.state = std::make_unique<YellowState>(); }
void YellowState::handle(TrafficLight& ctx) { ctx.state = std::make_unique<RedState>(); }
void RedState::handle(TrafficLight& ctx)    { ctx.state = std::make_unique<GreenState>(); }

int main() {
    TrafficLight light(std::make_unique<GreenState>());
    for (int i = 0; i < 6; ++i) light.next();
    return 0;
}
