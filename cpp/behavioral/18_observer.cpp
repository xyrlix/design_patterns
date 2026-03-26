/**
 * 设计模式: 观察者模式 (Observer)
 * 分类: 行为型
 *
 * 意图: 定义对象间一对多的依赖关系，当一个对象状态改变时，所有依赖者自动收到通知。
 * 核心思想: 主题维护观察者列表，状态变化时广播通知，实现发布-订阅。
 * 编程范式: OOP — 事件驱动 + 依赖倒置（主题不依赖具体观察者）。
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>

// ── 观察者接口 ────────────────────────────────────────────────────────────
struct Observer {
    virtual void update(const std::string& event, int value) = 0;
    virtual ~Observer() = default;
};

// ── 主题接口 ──────────────────────────────────────────────────────────────
struct Subject {
    virtual void subscribe(std::shared_ptr<Observer> o)   = 0;
    virtual void unsubscribe(std::shared_ptr<Observer> o) = 0;
    virtual void notify(const std::string& event, int v)  = 0;
    virtual ~Subject() = default;
};

// ── 具体主题 ──────────────────────────────────────────────────────────────
class StockMarket : public Subject {
    std::vector<std::shared_ptr<Observer>> observers_;
    int price_ = 100;
public:
    void setPrice(int p) {
        price_ = p;
        notify("price_changed", p);
    }

    void subscribe(std::shared_ptr<Observer> o)   override { observers_.push_back(o); }
    void unsubscribe(std::shared_ptr<Observer> o) override {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), o), observers_.end());
    }
    void notify(const std::string& event, int v)  override {
        for (auto& o : observers_) o->update(event, v);
    }
};

// ── 具体观察者 ────────────────────────────────────────────────────────────
struct Logger : Observer {
    void update(const std::string& event, int v) override {
        std::cout << "[Logger] " << event << " = " << v << "\n";
    }
};

struct AlertSystem : Observer {
    int threshold;
    explicit AlertSystem(int t) : threshold(t) {}
    void update(const std::string&, int v) override {
        if (v > threshold)
            std::cout << "[Alert!] Price " << v << " > threshold " << threshold << "\n";
    }
};

int main() {
    StockMarket market;
    auto logger = std::make_shared<Logger>();
    auto alert  = std::make_shared<AlertSystem>(120);

    market.subscribe(logger);
    market.subscribe(alert);

    market.setPrice(110);
    market.setPrice(130);

    market.unsubscribe(logger);
    market.setPrice(90);  // logger 不再收到
    return 0;
}
